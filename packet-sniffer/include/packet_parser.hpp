#ifndef PACKET_PARSER_HPP
#define PACKET_PARSER_HPP

#include <unordered_map>
#include <string> 
#include <tins/tins.h>
#include <nlohmann/json.hpp>

using namespace Tins;

class PacketParser {
    /*  
        Constructor - initialize member variables & does sniffer configuration
        Destructor - clean up resources if necessary
        
        Function - Parser to collect information from Packet object
        Function - Converting the string to a JSON Object
        Function - Helper to grab service name from port
    
        Setup: 
        Object - Parser object that'll be used for sniffing from Packet

        Data - duration: Length of time of the connection
        Data - protocol type: 
        Data - service: The Protocol that was used in the connection
        Data - flag: Status of the connection
        Data - src_bytes: Number of data bytes transferred from source to destination in single connection
        Data - count: Number of connections to the same destination host as the current connection in the past two seconds
        Data - srv_count: Number of connections to the same service (port number) as the current connection in the past two seconds
        Data - src_ip_: Source IP Address
        Data - dst_ip_: Destination IP Address
    */

    public:
        PacketParser();
        std::string parse(const Packet& packet);
        std::string toJSON();

    private:
        double duration_; 
        std::string protocol_type_; 
        std::string service_; 
        std::string flag_;
        std::string src_ip_;
        std::string dst_ip_; 
        int src_bytes_;
        int count_;
        int srv_count_;

        static std::unordered_map<std::string, int> connection_count_;
        static std::unordered_map<std::string, int> service_count_;

        std::string service_name(int port);
        std::string pdu_name(PDU::PDUType type);

        std::string parseIPv6(const IPv6& ipv6);
        std::string parseIPv4(const IP& ipv4);

        template<typename IPType>
        void parseTcpUdp(const IPType& ip);
        void calculateRates(const std::string& dst_ip);

};

template<typename IPType>
void PacketParser::parseTcpUdp(const IPType& ip) {
    if (const Tins::TCP* tcp = ip.template find_pdu<Tins::TCP>()) {
        protocol_type_ = "tcp";
        service_ = service_name(tcp->dport());
        flag_ = tcp->get_flag(TCP::SYN) ? "SYN" : 
                tcp->get_flag(TCP::FIN) ? "FIN" :
                tcp->get_flag(TCP::RST) ? "RST" : 
                tcp->get_flag(TCP::ACK) ? "ACK" : "NONE";
    } else if (const Tins::UDP* udp = ip.template find_pdu<Tins::UDP>()) {
        protocol_type_ = "udp"; 
        service_ = service_name(udp->dport());
        flag_ = "none"; 
    } else {
        service_ = "unknown";
        flag_ = "unknown";
    }
}

#endif