#include "packet_sniffer.hpp"
#include "packet_parser.hpp"

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

void PacketSniffer::signalHandler(int signal_num) {
    //Implement some form of recoverable start and start 
    std::cout << "Packet Collection Process was terminated" << std::endl;
    exit(signal_num);
}

bool PacketSniffer::sniffFunctor(const Packet& packet) {
    static bool initialized = false;
    if (!initialized) {
        signal(SIGINT, PacketSniffer::signalHandler);
        initialized = true;
    }

    PacketParser parser;
    std::string result = parser.parse(packet);
    std::cout << result << std::endl;
    //Figure out some sort of Sending mechanism (NOT SOCKETS)

    return true; 
}



