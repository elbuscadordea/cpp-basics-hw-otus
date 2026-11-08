//
// Created by elbus on 2026-11-03.
//

#include <iostream>

#include "Sequence.h"


template <typename T>
static void print_sequence(const containers::Sequence<T>& seq);
template <typename T>
static void print_sequence_using_at( const containers::Sequence<T>& seq);
template <typename T>
static void present_out_of_range(containers::Sequence<T>& seq, size_t out_of_range_pos);
template <typename T>
static void print_sequence_size(const containers::Sequence<T>& seq);

static void println();


int main() {

    std::cout << "Containers app\n"
                 << "============================" << std::endl;

    std::cout << "Start test" << std::endl;

    // Test of sequence<int>.
    println();
    std::cout << "Sequence test\n"
             << "--------------------------"<< std::endl;
    // 1. Create sequence object.
    containers::Sequence<int> seq = containers::Sequence<int>();

    for (int i = 0; i < 10; i++) {
        seq.push_back(i);
    }

    print_sequence(seq);
    print_sequence_using_at(seq);
    print_sequence_size(seq);

    // Erase elements
    println();
    std::cout << "Erasing elements" << std::endl;
    seq.erase(6);
    seq.erase(4);
    seq.erase(2);
    print_sequence_using_at(seq);
    print_sequence_size(seq);

    println();
    std::cout << "Insert new elements" << std::endl;
    seq.insert(0, 10);
    print_sequence_using_at(seq);

    const size_t middle_pos = seq.size() / 2;
    seq.insert(middle_pos, 20);
    print_sequence_using_at(seq);

    println();
    std::cout << "Add 30 to the end of seq" << std::endl;
    seq.push_back(30);
    print_sequence_using_at(seq);



    println();
    std::cout << "Access to an element by index out of range" << std::endl;
    present_out_of_range(seq, 25);

    std::cout << std::endl;
    return 0;
}

template <typename T>
static void print_sequence(const containers::Sequence<T>& seq) {
    // Print seq content using [] operator.
    for (size_t i = 0; i < seq.size(); i++) {
        std::cout << seq[i];
        if (i < seq.size() - 1) {
            std::cout << ", ";
        }
    }
    println();
}

template <typename T>
static void print_sequence_using_at( const containers::Sequence<T>& seq) {
    // Print seq content using at() member function.
    for (size_t i = 0; i < seq.size(); i++) {
        std::cout << seq.at(i);
        if (i < seq.size() - 1) {
            std::cout << ", ";
        }
    }
    println();
}


template <typename T>
void print_sequence_size(const containers::Sequence<T>& seq) {
    std::cout << "seq.size() = " << seq.size() << std::endl;
}

template <typename T>
void present_out_of_range(containers::Sequence<T>& seq, size_t out_of_range_pos) {
    std::cout << "seq[" << out_of_range_pos << "] = " << seq[out_of_range_pos] << std::endl;
    try {
        std::cout << "seq.at(" << out_of_range_pos << ") = " << seq.at(out_of_range_pos) << std::endl;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << " Index = " << out_of_range_pos << std::endl;
    }
}

// Useful Functions
void println() {
    std::cout << std::endl;
}

