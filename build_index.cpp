#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

void buildIndex(const string& logFile, const string& indexFile) {
    ifstream log(logFile);
    if (!log.is_open()) {
        cerr << "Error: Unable to open log file." << endl;
        return;
    }

    unordered_map<string, streampos> index;
    string line;
    streampos offset = log.tellg();

    while (getline(log, line)) {
        string date = line.substr(0, 10);
        if (index.find(date) == index.end()) {
            index[date] = offset;
        }
        offset = log.tellg();
    }

    ofstream idx(indexFile);
    if (!idx.is_open()) {
        cerr << "Error: Unable to create index file." << endl;
        return;
    }

    for (const auto& entry : index) {
        idx << entry.first << " " << entry.second << endl;
    }

    cout << "Index built successfully." << endl;
}

int main() {
    string logFile = "logs_2024.txt"; // Updated log file name
    string indexFile = "log_index.idx";
    buildIndex(logFile, indexFile);
    return 0;
}
