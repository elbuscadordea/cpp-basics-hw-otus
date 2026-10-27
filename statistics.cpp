#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

class IStatistics {
public:
	virtual ~IStatistics() {}

	virtual void update(double next) = 0;
	virtual double eval() const = 0;
	virtual const char * name() const = 0;
};

class Min : public IStatistics {
public:
	Min() : m_min{std::numeric_limits<double>::max()} { }

	void update(double next) override {
		if (next < m_min) {
			m_min = next;
		}
	}

	double eval() const override {
		return m_min;
	}

	const char * name() const override {
		return "min";
	}

private:
	double m_min;
};

class Max : public IStatistics {
public:
	Max() : m_max{std::numeric_limits<double>::min()} { }

	void update(double next) override {
		if (next > m_max) {
			m_max = next;
		}
	}

	double eval() const override {
		return m_max;
	}

	const char * name() const override {
		return "max";
	}

private:
	double m_max;
};

class Mean : public IStatistics {
public:
	Mean() : count {0}, mean{0} { }

	void update(double next) override {
		// Welford algorithm for mean calculation.
		++count;
		mean = ((count - 1) * mean + next) / count;
	}

	double eval() const override {
		return mean;
	}

	const char * name() const override {
		return "mean";
	}

private:
	int count;
	double mean;
};

class STD : public IStatistics {
public:
	STD() : count {0}, mean{0}, m2{0} { }

	void update(double next) override {
		// Welford algorithm for M2 calculation.
		++count;
		const double delta = next - mean;
		mean = mean + delta / count;
		m2 =  m2 + delta * (next - mean);
	}

	double eval() const override {
		// Final STD calculation
		double variance = m2 / count;
		return std::sqrt(variance);
	}

	const char * name() const override {
		return "std";
	}

private:
	int count;
	double mean;
	double m2;
};

/**
 * Base class for percentile calculation.
 */
class IPercentile : public IStatistics {};

struct Centroid {
	double mean;
	int weight;

	Centroid(const double m, const int w): mean(m), weight(w) {}
};

class TDigestPercentile : public IPercentile {
public:
	TDigestPercentile(const int percentile, const int sigma)
		: percentile_(percentile), sigma_(sigma) {
		n_ = 0;
		centroids_.reserve(sigma_ + 1);
	}

	void update(double next) override {
  		// Add new value with t-digest alg.
		// STEP 1.1
		++n_;

		// STEP 1.2
		if (centroids_.empty()) {
			const Centroid c = {next, 1};
			centroids_.push_back(c);
			return;
		}
		// TODO: Add Steps to process x value.
		// STEP 1.3
		int nearest_idx = findNearestCentroid(next);
		if (nearest_idx == -1) {
			// TODO: Unexpected case. Show warning! Then add new centroid like on step 1.2.
			std::cout << "Unexpected case: no nearest centroids found. New centroid ("
				<< next << ", 1) will be added." << std::endl;
			const Centroid c = {next, 1};
			centroids_.push_back(c);
			return;
		}
		double new_mean = (centroids_[nearest_idx].mean * centroids_[nearest_idx].weight + next) / n_;
		int new_weight = centroids_[nearest_idx].weight + 1;

		// Calculate w_left
                const int w_left = calc_w_left(nearest_idx);
                const double q_left = static_cast<double>(w_left) / n_;
                const double q_right = static_cast<double>(w_left + new_weight) / n_;
                const double k_left = scale_func(q_left);
                const double k_right = scale_func(q_right);

                if (k_right - k_left < 1) {
			// Update the nearest centroid.
			centroids_[nearest_idx] = {new_mean, new_weight};
		} else {
			// Insert a new centroid
			if (nearest_idx == centroids_.size() - 1) {
				// Add the new centroid into the end of the vector.
				centroids_.emplace_back(new_mean, new_weight);
			} else {
				for (auto it = centroids_.begin() + nearest_idx + 1; it != centroids_.end(); ++it) {
					if (new_mean < it->mean) {
						centroids_.insert(it, {next, 1});
						break;
					}
				}
			}
		}

		// STEP 2. MERGE.
		// TODO: Add merge.
	}

        double eval() const override {
		// TODO: calculate percentile.
	}

        const char *name() const override {
		return ("pct" + std::to_string(percentile_)).data();
	}

private:
	int percentile_;
	int sigma_;
	int n_;
	std::vector<Centroid> centroids_;

	int findNearestCentroid(const double x) const {
		if (centroids_.empty()) { return -1; }
		if (centroids_.size() == 1) { return 0; }

		int min_idx = 0;
		double min_diff = fabs(x - centroids_[0].mean);
		for (int i = 1; i < centroids_.size(); ++i) {
			double cur_fabs = fabs(x - centroids_[i].mean);
			if (cur_fabs < min_diff) {
				min_diff = cur_fabs;
				min_idx = i;
			} else {
				break;
			}
		}
		return min_idx;
	}

	int calc_w_left(const int max_idx) const {
		int wl = 0;
		if (max_idx > 0) {
			for (int i = 0; i < max_idx; i++) {
				wl += centroids_[i].weight;
			}
		}
		return wl;
	}

	double scale_func(const double q) const {
		return sigma_/(2 *  M_PI) * asin(2 * q - 1);
	}
};






int main() {
	const size_t statistics_count = 4;
	IStatistics *statistics[statistics_count];

	statistics[0] = new Min{};
	statistics[1] = new Max{};
	statistics[2] = new Mean{};
	statistics[3] = new STD{};

	double val = 0;
	while (std::cin >> val) {
		for (size_t i = 0; i < statistics_count; ++i) {
			statistics[i]->update(val);
		}
	}

	// Handle invalid input data
	if (!std::cin.eof() && !std::cin.good()) {
		std::cerr << "Invalid input data\n";
		return 1;
	}

	// Print results if any
	for (size_t i = 0; i < statistics_count; ++i) {
		std::cout << statistics[i]->name() << " = " << statistics[i]->eval() << std::endl;
	}

	// Clear memory - delete all objects created by new
	for (size_t i = 0; i < statistics_count; ++i) {
		delete statistics[i];
	}

	return 0;
}