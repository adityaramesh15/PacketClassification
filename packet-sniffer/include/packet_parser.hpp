    #ifndef PACKET_PARSER_HPP
    #define PACKET_PARSER_HPP

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
            Data - service: The Protocol that was used in the connection
            Data - flag: Status of the connection
            Data - src_bytes: Number of data bytes transferred from source to destination in single connection
            Data - land: if source and destination IP addresses and port numbers are equal then, this variable takes value 1, else 0
            Data - wrong_fragment: Total number of wrong fragments in this connection
            Data - urgent: Number of urgent packets in this connection. 
            Data - count: Number of connections to the same destination host as the current connection in the past two seconds
            Data - srv_count: Number of connections to the same service (port number) as the current connection in the past two seconds
            Data - same_srv_rate_: The percentage of connections that were to the same service
            Data - diff_srv_rate: The percentage of connections that were to different services
            Data - srv_diff_host_rate_: The percentage of connections that were to different destination machines

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
            int src_bytes_;
            bool land_ = false;
            bool wrong_fragment_ = false;
            bool urgent_;
            int count_;
            int srv_count_;
            double same_srv_rate_;
            double diff_srv_rate_;
            double srv_diff_host_rate_;
            std::unordered_map<std::string, int> connection_count_;
            std::unordered_map<std::string, int> service_count_;

            std::string service_name(int port);
    };

    #endif