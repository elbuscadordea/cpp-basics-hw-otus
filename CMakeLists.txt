# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.
cmake_minimum_required(VERSION 3.14)

project(GuessNumber CXX)

add_executable(guess_number guess-number.cpp
        randomizer.h
        randomizer.cpp
        records_table.cpp
        records_table.h
        settings.cpp
        settings.h)

set_target_properties(guess_number PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

