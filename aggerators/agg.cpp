#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>
#include <chrono>
#include <vector>

struct CityData {
    double minTemp = std::numeric_limits<double>::max();
    double maxTemp = std::numeric_limits<double>::lowest();
    double totalTemp = 0;
    int count = 0;

    void update(double temperature) {
        minTemp = std::min(minTemp, temperature);
        maxTemp = std::max(maxTemp, temperature);
        totalTemp += temperature;
        count++;
    }
    
    std::string toString() const {
        return "Min: " + std::to_string(minTemp) + 
               " / Mean: " + std::to_string(totalTemp / count) + 
               " / Max: " + std::to_string(maxTemp);
    }
};

void aggregate() {
    std::unordered_map<std::string, CityData> data;
    std::ifstream file("../measurements.txt", std::ios::binary);

    std::string line, name;
    double temperature;
    std::vector<char> buffer(100 * 1024 * 1024); // 200MB buffer
    file.rdbuf()->pubsetbuf(buffer.data(), buffer.size());

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        auto delimiterPos = line.find(';');
        name = line.substr(0, delimiterPos);
        temperature = std::stod(line.substr(delimiterPos + 1));

        data[name].update(temperature);
    }

    for(const auto& elem : data) {
        std::cout << elem.first << ":" << elem.second.toString() << ", ";
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    aggregate();
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout << "Aggregation took " << diff.count() << " seconds" << std::endl;

    return 0;
}
