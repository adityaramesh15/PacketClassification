#include "packet_parser.hpp"
#include <chrono> 

using namespace Tins; 
using json = nlohmann::json;

PacketParser::PacketParser() : duration_(0), protocol_type_(""), service_(""), flag_(""),
      src_bytes_(0), land_(false), wrong_fragment_(false), urgent_(false),
      count_(0), srv_count_(0), same_srv_rate_(0.0), diff_srv_rate_(0.0),
      srv_diff_host_rate_(0.0) {}

std::string PacketParser::parse(const Packet& packet) {
    auto timestamp = std::chrono::system_clock::now();
    static auto last_packet_time = timestamp;
    duration_ = std::chrono::duration<double>(timestamp - last_packet_time).count();
    last_packet_time = timestamp;

    if(const IP* ip = packet.pdu()->find_pdu<IP>()) {
        return parseIPv4(*ip);
    } else if(const IPv6* ipv6 = packet.pdu()->find_pdu<IPv6>()) {
        return parseIPv6(*ipv6);
    } else {
        return pdu_name(packet.pdu()->inner_pdu()->pdu_type());
    }
}

std::string PacketParser::parseIPv4(const IP& ip) {
    protocol_type_ = "ipv4";
    src_bytes_ = ip.tot_len();
    
    std::string src_ip = ip.src_addr().to_string();
    std::string dst_ip = ip.dst_addr().to_string();
    land_ = (src_ip == dst_ip);
    
    wrong_fragment_ = (ip.flags() & IP::MORE_FRAGMENTS);

    std::string connection_key = src_ip + "-" + dst_ip;
    count_ = ++connection_count_[connection_key];

    parseTcpUdp(ip);

    std::string service_key = dst_ip + "-" + service_;
    srv_count_ = ++service_count_[service_key];

    calculateRates(dst_ip);
    
    return toJSON();
}

std::string PacketParser::parseIPv6(const IPv6& ipv6) {
    protocol_type_ = "ipv6";
    src_bytes_ = ipv6.payload_length() + 40; 
    
    std::string src_ip = ipv6.src_addr().to_string();
    std::string dst_ip = ipv6.dst_addr().to_string();
    land_ = (src_ip == dst_ip);
    
    wrong_fragment_ = false;
    for (const auto& header : ipv6.headers()) {
        if (header.option() == IPv6::FRAGMENT) {
            wrong_fragment_ = true;
            break;
        }
    }

    std::string connection_key = src_ip + "-" + dst_ip;
    count_ = ++connection_count_[connection_key];

    parseTcpUdp(ipv6);

    std::string service_key = dst_ip + "-" + service_;
    srv_count_ = ++service_count_[service_key];

    calculateRates(dst_ip);
    
    return toJSON();
}

void PacketParser::calculateRates(const std::string& dst_ip) {
    int total_connections = 0;
    int same_srv_connections = 0;
    int diff_srv_connections = 0;
    int srv_diff_host_connections = 0;

    for (const auto& conn : connection_count_) {
        total_connections++;
        if (conn.first.find(dst_ip) != std::string::npos) {
            if (service_count_.find(dst_ip + "-" + service_) != service_count_.end()) {
                same_srv_connections++;
            } else {
                diff_srv_connections++;
            }
        }
        if (conn.first.find("-" + service_) != std::string::npos && conn.first.find(dst_ip) == std::string::npos) {
            srv_diff_host_connections++;
        }
    }

    if (total_connections > 0) {
        same_srv_rate_ = static_cast<double>(same_srv_connections) / total_connections;
        diff_srv_rate_ = static_cast<double>(diff_srv_connections) / total_connections;
        srv_diff_host_rate_ = static_cast<double>(srv_diff_host_connections) / total_connections;
    }
}


std::string PacketParser::toJSON() {
    json j;
    j["duration"] = duration_;
    j["protocol_type"] = protocol_type_;
    j["service"] = service_;
    j["flag"] = flag_;
    j["src_bytes"] = src_bytes_;
    j["land"] = land_;
    j["wrong_fragment"] = wrong_fragment_;
    j["urgent"] = urgent_;
    j["count"] = count_;
    j["srv_count"] = srv_count_;
    j["same_srv_rate"] = same_srv_rate_;
    j["diff_srv_rate"] = diff_srv_rate_;
    j["srv_diff_host_rate"] = srv_diff_host_rate_;  
    return j.dump();
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
        case 53: return "dns";
        case 67: return "bootstrap/dhcp";
        case 137: return "netbios";
        case 5353: return "multicast dns";
        default: 
            if(port >= 49152 && port <= 65535) {
                return "ephemeral";
            } else {
                return std::to_string(port);
            }
    }

}

std::string PacketParser::pdu_name(PDU::PDUType type) {
    static const std::unordered_map<PDU::PDUType, std::string> pdu_type_map = {
        { PDU::ETHERNET_II, "Ethernet II" },
        { PDU::IP, "IP" },
        { PDU::IPv6, "IPv6" },
        { PDU::ARP, "ARP" },
        { PDU::ICMP, "ICMP" },
        { PDU::ICMPv6, "ICMPv6" },
        { PDU::TCP, "TCP" },
        { PDU::UDP, "UDP" },
        { PDU::DNS, "DNS" },
        { PDU::DHCP, "DHCP" },
        { PDU::DHCPv6, "DHCPv6" },
        { PDU::EAPOL, "EAPOL" },
        { PDU::RAW, "RawPDU" }
    };

    auto it = pdu_type_map.find(type);
    if (it != pdu_type_map.end()) {
        return it->second;
    } else {
        return "Unknown";
    }

}