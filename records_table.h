//
// Created by elbus on 2026-08-31.
//

#pragma once

#include <string>

namespace records_table {
    constexpr int OPEN_RECORDS_TABLE_FAILED = -1;

    int updateRecordsTable(const std::string& playerName, int triesNumber);
    void printRecordsTable();
}
