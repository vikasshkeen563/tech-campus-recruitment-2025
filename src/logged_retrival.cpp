#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <cstdlib>

using namespace std;

struct LogEntry {
    string date;
    string content;
};

bool isValidDate(const string& dateStr) {
    regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(dateStr, dateRegex);
}

vector<LogEntry> parseLogs(const string& filename) {
    vector<LogEntry> logs;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return logs;
    }

    string line;
    stringstream logBuffer;
    LogEntry currentLog;

    while (getline(file, line)) {
        regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
        smatch match;
        if (regex_search(line, match, dateRegex)) {
            if (!currentLog.date.empty()) {
                logs.push_back(currentLog);
            }
            currentLog.date = match.str(0);
            currentLog.content = line;
        } else {
            if (!currentLog.date.empty()) {
                currentLog.content += " " + line;
            }
        }
    }

    if (!currentLog.date.empty()) {
        logs.push_back(currentLog);
    }

    file.close();
    return logs;
}

void saveLogsToFile(const vector<LogEntry>& logs, const string& searchDate) {
    string outputFilename = "output/output_" + searchDate + ".txt";
    ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        cerr << "Error opening output file!" << endl;
        return;
    }

    bool found = false;
    for (const auto& log : logs) {
        if (log.date == searchDate) {
            outputFile << "Date: " << log.date << endl;
            outputFile << "Content: " << log.content << endl << endl;
            found = true;
        }
    }

    if (!found) {
        outputFile << "No logs found for the date: " << searchDate << endl;
    }

    outputFile.close();
}

int main(int argc, char* argv[]) {
    string searchDate;

    if (argc == 2) {
        searchDate = argv[1];
        if (!isValidDate(searchDate)) {
            cout << "Invalid date format!" << endl;
            return 1;
        }
    } else {
        cout << "Enter the date to search (YYYY-MM-DD): ";
        cin >> searchDate;

        if (!isValidDate(searchDate)) {
            cout << "Invalid date format!" << endl;
            return 1;
        }
    }

    string filename = "test_logs.log";
    vector<LogEntry> logs = parseLogs(filename);

    saveLogsToFile(logs, searchDate);

    cout << "Logs for " << searchDate << " have been saved to output/output_" << searchDate << ".txt" << endl;

    return 0;
}
