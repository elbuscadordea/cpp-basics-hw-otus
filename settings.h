//
// Created by elbus on 2026-08-31.
//

#pragma once


constexpr int DEFAULT_MAX_GUESS_NUMBER = 100;


struct Settings {
    int maxGuessNumber{DEFAULT_MAX_GUESS_NUMBER};
    std::string playerName;
    bool printRecordsTable{false};
};

