#include <iostream>
#include <tins/tins.h>
#include "packet_sniffer.hpp"
#include "packet_parser.hpp"

using namespace Tins;

int main() {   
    PacketSniffer my_sniffer;
    my_sniffer.sniff();
}