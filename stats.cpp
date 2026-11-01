//
// Created by elbus on 2026-10-27.
//
#include "stats.h"
#include <limits>
#include <cmath>


// Min Members
stats::Min::Min() : m_min{std::numeric_limits<double>::max()} {
}

void stats::Min::update(double next) {
    if (next < m_min) {
        m_min = next;
    }
}

double stats::Min::eval() const {
    return m_min;
}

const char *stats::Min::name() const {
    return "min";
}


// Max Members
stats::Max::Max() : m_max{std::numeric_limits<double>::min()} {
}

void stats::Max::update(double next) {
    if (next > m_max) {
        m_max = next;
    }
}

double stats::Max::eval() const { return m_max; }

const char *stats::Max::name() const { return "max"; }


// Mean Members
stats::Mean::Mean() : count{0}, mean{0} {
}

void stats::Mean::update(double next) {
    // Welford algorithm for mean calculation.
    ++count;
    mean = ((count - 1) * mean + next) / count;
}

double stats::Mean::eval() const { return mean; }

const char *stats::Mean::name() const { return "mean"; }


// STD Members
stats::STD::STD() : count{0}, mean{0}, m2{0} {
}

void stats::STD::update(double next) {
    // Welford algorithm for M2 calculation.
    ++count;
    const double delta = next - mean;
    mean = mean + delta / count;
    m2 = m2 + delta * (next - mean);
}

double stats::STD::eval() const {
    // Final STD calculation
    double variance = m2 / count;
    return std::sqrt(variance);
}

const char *stats::STD::name() const { return "std"; }
