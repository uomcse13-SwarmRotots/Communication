#ifndef WIRELESS_STRENGTH_INCLUDE
#define WIRELESS_STRENGTH_INCLUDE

#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;

class Wireless_Strength
{         
    string SSID,BARS,SECURITY,RATE;
    string MODE;
    string CHAN,SIGNAL;
    string network;
    int signal_strength;
    std::size_t signal_index,mode_index,ssid_index,ssid_len;
    std::string signal_str,ssid;  
    vector<string> columns;

public:
    string GetStdoutFromCommand(string cmd);
    void ScanNetworks(string data);
    void ConnectToNetwork(string ssid);
       
};
