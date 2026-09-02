//
// Created by elbus on 2026-08-31.
//

#include "records_table.h"

#include <fstream>
#include <iostream>
#include <filesystem>

#include <vector>

namespace fs = std::filesystem;

namespace records_table {
    const std::string RECORDS_FILE_NAME{"high_scores.txt"};

    struct Record {
        std::string playerName;
        int score;
    };

    /**
     * Add a new record.
     * @param playerName name of the player with record.
     * @param triesNumber number of tries (attempts) of the player to find the guessed number.
     * @return result code: 0 - succeed, otherwise a code of the error.
     */
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

    static int findRecordByPlayerName(const std::string& playerName, const std::vector<Record> &records);

    /**
     * Print records table (high scores).
     */
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

            std::vector<Record> records;

            std::string currentRecord;

            while (std::getline(inFile, currentRecord)) {
                size_t lastPosition = currentRecord.find_last_of(' ');
                if (lastPosition != std::string::npos) {
                    std::string playerName = currentRecord.substr(0, lastPosition);
                    try {
                        std::string score_str = currentRecord.substr(lastPosition + 1);
                        int score = std::stoi(score_str);

                        int playerIdx = findRecordByPlayerName(playerName, records);
                        if (playerIdx != -1) {
                            if (records[playerIdx].score > score) {
                                records[playerIdx].score = score;
                            }
                        } else {
                            records.push_back(Record{.playerName = playerName, .score = score});
                        }
                    } catch (const std::exception&) {
                        std::cout << playerName << "No score" << std::endl;
                    }

                }

            }

            for (const auto& record : records) {
                std::cout << record.playerName << '\t' << record.score  << std::endl;
            }
        }
    }

    /**
     * Finds the record by player name.
     * Function is case-sensitive for player name. "Player1" and "player1" are different players.
     * @param playerName
     * @param records
     * @return the index of the found record. If the record is not found, -1 returns.
     */
    int findRecordByPlayerName(const std::string& playerName, const std::vector<Record> &records) {
        for (int i = 0; i < records.size(); ++i) {
            if (records[i].playerName == playerName) {
                return i;
            }
        }
        return -1;
    }
}
