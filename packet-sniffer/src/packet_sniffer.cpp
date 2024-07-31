#include "packet_sniffer.hpp"
#include "packet_parser.hpp"
#include <cpp_redis/cpp_redis>

cpp_redis::client client;
const std::string REDIS_KEY = "packet_list";
const int BUFFER_SIZE = 100;

PacketSniffer::PacketSniffer() : interface_("en0"), promiscuous_(true), snapshot_length_(65535) {}

PacketSniffer::PacketSniffer(const std::string& interface, const std::string& address, const std::string& port, bool promiscuous, int snap) :
    interface_(interface), filter_address_(address), filter_port_(port), promiscuous_(promiscuous), snapshot_length_(snap) {}

PacketSniffer::~PacketSniffer() {}


void PacketSniffer::sniff() {
    SnifferConfiguration config = configureSniffer();
    Sniffer sniffer(interface_, config);
    sniffer.sniff_loop(sniffFunctor);
}

SnifferConfiguration PacketSniffer::configureSniffer() const {
    SnifferConfiguration config;
    config.set_promisc_mode(promiscuous_);
    config.set_snap_len(snapshot_length_);

    if (!filter_address_.empty()) {
        config.set_filter(filter_address_);
    }
    if (!filter_port_.empty()) {
        config.set_filter(filter_port_);
    }
    return config;
}

bool PacketSniffer::sniffFunctor(const Packet& packet) {
    static bool initialized = false;
    if (!initialized) {
        signal(SIGINT, PacketSniffer::signalHandler);
        client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
            if (status == cpp_redis::connect_state::dropped) {
                std::cout << "Client disconnected from " << host << ":" << port << std::endl;
            }
        });
        initialized = true;
    }

    PacketParser parser;
    std::string result = parser.parse(packet); 
    // writeData("../../data/cafe-data.json", result);
    client.rpush(REDIS_KEY, std::vector{result}, [](cpp_redis::reply& reply) {
        // std::cout << "SET: " << reply << std::endl;
    });
    client.sync_commit();
    client.ltrim(REDIS_KEY, -BUFFER_SIZE, -1);
    client.sync_commit();
    return true; 
}

void PacketSniffer::writeData(std::string location, std::string data) {
    std::ofstream outfile(location, std::ios::app);
    if(outfile.is_open()) {
        if(data != "") {
            outfile << data << ","<< std::endl;
        }
        outfile.close();
    } else {
        std::cerr << "Cannot open file" << std::endl;
    }
}

void PacketSniffer::signalHandler(int signal_num) {
    std::cout << "\nPacket Collection Process was terminated\n" << std::endl;
    client.disconnect(); 
    exit(signal_num);
}

