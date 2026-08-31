//
// Created by elbus on 2026-08-25.
//

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "randomizer.h"
#include "records_table.h"


void printGameHeader();
std::string getPlayerName();
void printUserGreeting(const std::string& playerName);


int main(int argc, char const *argv[]) {

    printGameHeader();

    const std::string playerName = getPlayerName();
    printUserGreeting(playerName);


    const int secretNumber{rnd::getRandomNumber(1, 100)};

    std::cout << "\nGuess the number!" << std::endl;

    bool stopGame{false};
    int triesNumber{0};

    do {
        int guess;

        std::cout << std::endl;
        std::cout << "Your number:" << std::endl;
        std::cin >> guess;

        if (bool isInputGood = std::cin.good(); !isInputGood || guess < 1 || guess > 100) {
            std::cout << "Invalid  number!" << std::endl;
            std::cout << "Number should be from 1 to 100" << std::endl;
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

    int updateResult = records_table::updateRecordsTable(playerName, triesNumber);
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
