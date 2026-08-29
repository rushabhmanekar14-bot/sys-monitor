#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

int main() {
    std::ifstream meminfo("/proc/meminfo");
    std::string line;
    
    long memTotal = 0;
    long memAvailable = 0;

    if (!meminfo.is_open()) {
        std::cerr << "Error: Could not read hardware metrics.\n";
        return 1;
    }

    // Parse key-value pairs from /proc/meminfo
    while (getline(meminfo, line)) {
        std::istringstream iss(line);
        std::string key;
        long value;
        std::string unit;
        
        iss >> key >> value >> unit;
        
        if (key == "MemTotal:") memTotal = value;
        else if (key == "MemAvailable:") memAvailable = value;
    }

    if (memTotal > 0 && memAvailable > 0) {
        double usedMem = memTotal - memAvailable;
        double percentUsed = (usedMem / memTotal) * 100.0;
        
        std::cout << "--- Memory Utilization ---\n";
        std::cout << "Total: " << memTotal / 1024 << " MB\n";
        std::cout << "Available: " << memAvailable / 1024 << " MB\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Usage: " << percentUsed << "%\n";
    } else {
        std::cerr << "Failed to parse memory stats.\n";
    }

    return 0;
}
