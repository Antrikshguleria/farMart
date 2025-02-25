#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

unordered_map<string, streampos> loadIndex(const string& indexFile) {
    unordered_map<string, streampos> index;
    ifstream idx(indexFile);
    if (!idx.is_open()) {
        cerr << "Error: Unable to open index file." << endl;
        return index;
    }

    string line;
    while (getline(idx, line)) {
        istringstream iss(line);
        string date;
        streampos offset;
        iss >> date >> offset;
        index[date] = offset;
    }

    return index;
}

void extractLogs(const string& logFile, const string& outputFile, const string& date, const unordered_map<string, streampos>& index) {
    if (index.find(date) == index.end()) {
        cerr << "Error: No logs found for date " << date << endl;
        return;
    }

    ifstream log(logFile);
    if (!log.is_open()) {
        cerr << "Error: Unable to open log file." << endl;
        return;
    }

    log.seekg(index.at(date));
    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Error: Unable to create output file." << endl;
        return;
    }

    string line;
    while (getline(log, line)) {
        if (line.substr(0, 10) != date) {
            break;
        }
        out << line << endl;
    }

    cout << "Logs extracted successfully to " << outputFile << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " YYYY-MM-DD" << endl;
        return 1;
    }

    string date = argv[1];
    string logFile = "logs_2024.txt";
    string indexFile = "log_index.idx";
    string outputFile = "output/output_" + date + ".txt";

    auto index = loadIndex(indexFile);
    extractLogs(logFile, outputFile, date, index);

    return 0;
}
