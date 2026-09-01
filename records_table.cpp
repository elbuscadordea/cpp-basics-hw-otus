//
// Created by elbus on 2026-08-31.
//

#include "records_table.h"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace records_table {
    const std::string RECORDS_FILE_NAME{"high_scores.txt"};

    int updateRecordsTable(const std::string& playerName, const int triesNumber) {
        {
            std::ofstream outFile = std::ofstream{RECORDS_FILE_NAME, std::ios::app};
            if (!outFile.is_open()) {
                std::cout << "Unable to open file for writing!" << std::endl;
                return OPEN_RECORDS_TABLE_FAILED;
            }

            outFile << playerName << ' ' << triesNumber << std::endl;
        }
        return 0;
    }

    void printRecordsTable() {
        {
            if (!fs::exists(RECORDS_FILE_NAME)) {
                std::cout << "No records in table." << std::endl;
                return;
            }

            std::ifstream inFile{RECORDS_FILE_NAME};
            if (!inFile.is_open()) {
                std::cout << "Failed to open records file";
                return;
            }

            std::cout << "High scores table:" << std::endl;

            int score{0};
            std::string currentRecord;
            while (std::getline(inFile, currentRecord)) {
                size_t lastPosition = currentRecord.find_last_of(' ');
                if (lastPosition != std::string::npos) {
                    std::string playerName = currentRecord.substr(0, lastPosition);
                    try {
                        std::string score_str = currentRecord.substr(lastPosition + 1);
                        score = std::stoi(score_str);
                        std::cout << playerName << '\t' << score  << std::endl;
                    } catch (const std::exception&) {
                        std::cout << playerName << "No score" << std::endl;
                    }

                }

            }
        }
    }
}
