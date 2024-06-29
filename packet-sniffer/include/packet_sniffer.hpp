#ifndef PACKET_SNIFFER_H
#define PACKET_SNIFFER_H

#include <tins/tins.h>
#include <vector>
#include <string>
#include <csignal>
#include <iostream>

using namespace Tins; 

class PacketSniffer {
    /*  
        Constructor - Initialize member variables & does sniffer configuration
        Destructor - Clean up resources if necessary
        
        Function - Loop sniffing until condition is met, adds to packet vector
        Function - Helper to setup the sniffer
        Function - Helper to terminate packet reading when signal arrives
        Functor - Condition for when to stop sniffing
    
        Setup: 
        Object - Sniffer object that'll be used for sniffing from libtins

        Data - Network interface to sniff on (e.g., "eth0")
        Data - IP address to filter packets (e.g., "ip src 192.168.0.1")
        Data - Port number to sniff on (e.g., "port 80")
        Data - Promiscuous mode flag (true or false)
        Data - Snapshot length, bytes stored per packet

    */


    public:
        PacketSniffer();
        PacketSniffer(const std::string& interface, const std::string& address = "", 
                        const std::string& port =  "", bool promiscuous = true, int snap = 65535); 
        ~PacketSniffer();

        void sniff();
        static void signalHandler(int signal_num);
        static bool sniffFunctor(const Packet&);

    private:
        std::string interface_;
        std::string filter_address_;
        std::string filter_port_;
        bool promiscuous_;
        int snapshot_length_;

        SnifferConfiguration configureSniffer() const; 
};


#endif