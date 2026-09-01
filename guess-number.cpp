//
// Created by elbus on 2026-08-25.
//

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "randomizer.h"
#include "records_table.h"
#include "settings.h"


void printGameHeader();
std::string getPlayerName();
void printUserGreeting(const std::string& playerName);
void parseArgumentsToSetting(int argc, char const *argv[], Settings& settings);


int main(int argc, char const *argv[]) {

    Settings settings;
    try {
        parseArgumentsToSetting(argc, argv, settings);
    } catch (std::invalid_argument& e) {
        std::cout << "Invalid command option: " << e.what() << std::endl;
        return -1;
    } catch (std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
        return -1;
    }

    printGameHeader();

    if (settings.playerName.empty()) {
        settings.playerName = getPlayerName();
    }
    printUserGreeting(settings.playerName);

    const int secretNumber{rnd::getRandomNumber(1, settings.maxGuessNumber)};

    std::cout << "\nGuess the number!" << std::endl;

    bool stopGame{false};
    int triesNumber{0};

    do {
        int guess;

        std::cout << std::endl;
        std::cout << "Your number:" << std::endl;
        std::cin >> guess;

        bool isInputGood = std::cin.good();
        if (!isInputGood || guess < 1 || guess > settings.maxGuessNumber) {
            std::cout << "Invalid  number!" << std::endl;
            std::cout << "Number should be from 1 to " << settings.maxGuessNumber << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear out the bad input from the stream
            continue;
        }

        triesNumber++;

        if (guess > secretNumber) {
            std::cout << "Greater than." << std::endl;
        } else if (guess < secretNumber) {
            std::cout << "Less than." << std::endl;
        } else {
            std::cout << "You win! Attempts:" << triesNumber << std::endl;
            stopGame = true;
        }

    } while (!stopGame);

    int updateResult = records_table::updateRecordsTable(settings.playerName, triesNumber);
    if (updateResult != 0) {
        std::cout << "Update high score table failed." << std::endl;
        return -1;
    }

    std::cout << std::endl;
    records_table::printRecordsTable();

    return 0;
}

void printGameHeader() {
    std::cout << "==================================\n" << std::endl;
    std::cout << "         GUESS THE NUMBER\n" << std::endl;
    std::cout << "==================================\n" << std::endl;
}

std::string getPlayerName() {
    std::string playerName;

    std::cout << "Enter your name, please:" << std::endl;
    std::getline(std::cin, playerName);
    return playerName;
}

void printUserGreeting(const std::string& playerName) {
    std::cout << std::endl;
    std::cout << "Welcome, " << playerName << "!" << std::endl;
}


// Command line options parsing functions.
int getIntArgValue(int argi, int argc, char const *argv[], const std::string &argName);
std::string getStringArgValue(int argi, int argc, char const *argv[], const std::string &argName);

void parseArgumentsToSetting(int argc, char const *argv[], Settings& settings) {
    if (argc < 2) return;

    int i = 1;
    while (i < argc) {
        std::string paramName = std::string{argv[i]};
        if (paramName == "-max") {
            // Next arg in argv
            settings.maxGuessNumber = getIntArgValue(i, argc, argv, paramName);
            i+= 2;
        } else if (paramName == "-u") {
            settings.playerName = getStringArgValue(i, argc, argv, paramName);
            i+= 2;
        } else {
            i++;
        }
    }
}


int getIntArgValue(const int argi, const int argc, char const *argv[], const std::string &argName) {
    const int i = argi + 1;
    if (i < argc) {
        const std::string argValueStr = std::string{argv[i]};
        return std::stoi(argValueStr);
    }
    throw std::invalid_argument("Expected value for " + argName + " option.");
}

std::string getStringArgValue(const int argi, const int argc, char const *argv[], const std::string &argName) {
    int i = argi + 1;
    if (i < argc) {
       return std::string{argv[i]};
    }
    throw std::invalid_argument("Expected value for " + argName + " option.");
}
