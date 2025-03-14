#pragma once
#include "Integers.h"
#include "Sequences.h"

#include <limits>
#include <string>
#include <random>

template <class T, class Generator = std::mt19937_64, class Distribution = std::uniform_int_distribution<T>>
class RandomInternal {
protected:
	std::random_device rd;

	Generator gen;
public:
	RandomInternal() {
		gen.seed(rd());
	}

	T Generate(const T& min = std::numeric_limits<T>::min(), const T& max = std::numeric_limits<T>::max()) {
		Distribution dist = Distribution(min, max);
	
		return dist(gen);
	}


	Vector<T> GenerateVector(uint64 num, Vector<T>& options) {
		Vector<T> out(num);
		std::uniform_int_distribution<uint64> dist = std::uniform_int_distribution<uint64>(0, options.size());

		for (uint64 i = 0; i < num; ++i) {
			out[i] = options[dist(gen)];
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 minNum, uint64 maxNum, Vector<T>& options) {
		Distribution numDist = Distribution(minNum, maxNum);
		uint64 num = numDist(gen);

		Vector<T> out(num);
		std::uniform_int_distribution<uint64> dist = std::uniform_int_distribution<uint64>(0, options.size());

		for (uint64 i = 0; i < num; ++i) {
			out[i] = options[dist(gen)];
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 num, T min, T max) {
		Vector<T> out(num);
		Distribution dist = Distribution(min, max);

		for (uint64 i = 0; i < num; ++i) {
			out[i] = dist(gen);
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 minNum, uint64 maxNum, T min, T max) {
		Distribution numDist = Distribution(minNum, maxNum);
		uint64 num = numDist(gen);

		Vector<T> out(num);
		Distribution dist = Distribution(min, max);

		for (uint64 i = 0; i < num; ++i) {
			out[i] = dist(gen);
		}
		return std::move(out);
	}


	Vector<T> GenerateString(uint64 num, Vector<T>& options) {
		Vector<T> out(num);
		std::uniform_int_distribution<uint64> dist = std::uniform_int_distribution<uint64>(0, options.size());

		for (uint64 i = 0; i < num; ++i) {
			out[i] = options[dist(gen)];
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 minNum, uint64 maxNum, Vector<T>& options) {
		Distribution numDist = Distribution(minNum, maxNum);
		uint64 num = numDist(gen);

		Vector<T> out(num);
		std::uniform_int_distribution<uint64> dist = std::uniform_int_distribution<uint64>(0, options.size());

		for (uint64 i = 0; i < num; ++i) {
			out[i] = options[dist(gen)];
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 num, T min, T max) {
		Vector<T> out(num);
		Distribution dist = Distribution(min, max);

		for (uint64 i = 0; i < num; ++i) {
			out[i] = dist(gen);
		}
		return std::move(out);
	}

	Vector<T> GenerateVector(uint64 minNum, uint64 maxNum, T min, T max) {
		Distribution numDist = Distribution(minNum, maxNum);
		uint64 num = numDist(gen);

		Vector<T> out(num);
		Distribution dist = Distribution(min, max);

		for (uint64 i = 0; i < num; ++i) {
			out[i] = dist(gen);
		}
		return std::move(out);
	}
};

template <class T>
using FastRandomInt = RandomInternal<T, std::minstd_rand, std::uniform_int_distribution<T>>;
template <class T>
using FastRandomReal = RandomInternal<T, std::minstd_rand, std::uniform_real_distribution<T>>;

template <class T>
using RandomInt = RandomInternal<T, std::mt19937_64, std::uniform_int_distribution<T>>;
template <class T>
using RandomReal = RandomInternal<T, std::mt19937_64, std::uniform_real_distribution<T>>;
