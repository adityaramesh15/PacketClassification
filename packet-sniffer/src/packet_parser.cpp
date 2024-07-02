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

    if(packet.pdu() -> find_pdu<IP>()) {
        const IP& ip = packet.pdu()->rfind_pdu<IP>();
        src_bytes_ = ip.tot_len();
        
        std::string src_ip = ip.src_addr().to_string();
        std::string dst_ip = ip.dst_addr().to_string();
        land_ = (src_ip == dst_ip);
        
        wrong_fragment_ = (ip.flags() & IP::MORE_FRAGMENTS);

        std::string connection_key = src_ip + "-" + dst_ip;
        count_ = ++connection_count_[connection_key];

        if (const TCP* tcp = packet.pdu()->find_pdu<TCP>()) {
            protocol_type_ = "tcp";
            service_ = service_name(tcp->dport());
            flag_ = tcp->flags();
            urgent_ = tcp->get_flag(TCP::URG);
        } else if (const UDP* udp = packet.pdu()->find_pdu<UDP>()) {
            protocol_type_ = "udp";
            service_ = service_name(udp->dport());
            flag_ = "none"; 
            urgent_ = false;
        } else {
            protocol_type_ = "other";
            service_ = "unknown";
            flag_ = "";
            urgent_ = false;
        }

        std::string service_key = dst_ip + "-" + service_;
        srv_count_ = ++service_count_[service_key];

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
        
        return "IP";//toJSON(); 
    }
    return pdu_name(packet.pdu()->inner_pdu()->pdu_type());
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