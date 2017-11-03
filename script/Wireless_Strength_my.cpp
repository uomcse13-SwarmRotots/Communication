
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

string GetStdoutFromCommand(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    // popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
                pclose(stream);
    }
    return data;
}

void ConnectToNetwork(string ssid)
{
    string con_est = GetStdoutFromCommand("nmcli c up "+ssid);
}

void DisconnectFromNetwork(string ssid)
{
    string con_dis = GetStdoutFromCommand("nmcli c down "+ssid);
}

void ScanNetworks(string data){
    // ifstream fin(data);
    string SSID,BARS,SECURITY,RATE;
    string MODE;
    string CHAN,SIGNAL;
    string network;
    int signal_strength;
    std::size_t signal_index,mode_index,ssid_index,ssid_len;
    std::string signal_str,ssid;  
    vector<string> columns;

    boost::split(columns, data, boost::is_any_of("\n"));
    cout << "size " << columns.size();
    for (size_t i=0; i<(columns.size()-1); i++) {
        network = columns[i];
        if(i==0){
            signal_index = network.find("SIGNAL");
            ssid_index = network.find("SSID");
            mode_index = network.find("MODE");
            ssid_len = mode_index - ssid_index;
            //cout<<"Signal Index "<<signal_index<<endl;
        }
        else{
            //cout<<"Signal Index "<<signal_index<<endl;
            signal_str = network.substr(signal_index,3);
            boost::trim_right(signal_str);
            //cout << signal_str << endl;
            signal_strength = std::atoi(signal_str.c_str());
            if(signal_strength>50){
                cout << columns[i] << endl;
                ssid = network.substr(ssid_index,ssid_len);
                ConnectToNetwork(ssid);
                sleep(10);
                DisconnectFromNetwork(ssid);
            }
        }        
    }
}



int main (){
    string ls = GetStdoutFromCommand("nmcli dev wifi");

    // cout << "LS: " << ls << endl;
    ScanNetworks(ls);
    return 0;
}
