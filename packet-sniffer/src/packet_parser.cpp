#include "packet_parser.hpp"
#include <chrono> 


std::string PacketParser::parse(const Packet& packet) {
    auto timestamp = std::chrono::system_clock::now();
    static auto last_packet_time = timestamp;

    duration_ = std::chrono::duration<double>(timestamp - last_packet_time).count();
    last_packet_time = timestamp;

    if(packet.pdu() -> find_pdu<IP>()) {
        const IP& ip = packet.pdu() -> rfind_pdu<IP>();
        protocol_type_ =  ip.protocol() == 6 ? "tcp" : (ip.protocol() == 17 ? "udp" : "other");
        src_bytes_ = ip.tot_len(); 

        std::string src_ip = ip.src_addr().to_string();
        std::string dst_ip = ip.dst_addr().to_string();
        land_ = (src_ip == dst_ip); 

        


    }

}


std::string PacketParser::toJSON(std::string input) {

}

std::string PacketParser::service_name(int port) {
    switch(port) {
        case 80: return "http";
        case 443: return "https";
        case 20: return "ftp";
        case 22: return "ssh";
        case 23: return "telnet";
        case 25: return "smtp";
        case 110: return "pop3";
        case 123: return "ntp";
        case 143: return "imap";
        case 161: return "snmp";

        default: return "unknown port: " + port;
    }

}