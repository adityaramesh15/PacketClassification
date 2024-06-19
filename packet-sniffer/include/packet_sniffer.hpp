#ifndef PACKET_SNIFF_H
#define PACKET_SNIFF_H

#include <tins/tins.h>

using namespace Tins; 

class PacketSniffer {
    /*  
        
        Constructor - initialize member variables & do SnifferConfiguration
        Destructor - Might be empty for now
        
        Function - Loop Sniffing until condition is met
        Function - Parse a packet and return a std::string, called while loop sniffing
        Function - getter for std::vector of strings 
    
        Data - libpcap string filter for where to sniff ("eth0")
        Data - IP address to grab Datagrams from ("ip src 192.168.0.1")
        Data - Port number to sniff on
        Data - Promiscuous mode on or off
        Data - Snapshot length, bytes stored per packet
        Data - Condition for when to stop sniffing
        Data - std::vector of strings of packet data
        
         
    
    */



};



#endif