#include<iostream>
#include<fstream>
#include<string>


int main(){
    std::ifstream meminfo("/proc/meminfo");
    std::string line;

    if(!meminfo.is_open()){
        std::cerr << "Error: Couldn't read hardware metrics.\n";
    }


    std::cout<< "--- System Memory Status ---\n";
    while (getline(meminfo,line))
    {
        /* code */
        if(line.find("MemTotal") == 0 || line.find("MemAvailable")==0){
            std::cout<< line <<std::endl;
        }
    }
    
    return 0;
}