#pragma once

// Dependencies | std
#include <string>
#include <regex>

struct RealNumber {
	// Static

	// Properties
	static const std::regex REAL_NUMBER_PATTERN;
	static const std::regex WHOLE_PART_PATTERN;
	static const std::regex DECIMAL_PART_PATTERN;

	// Object

	// Properties
	long long value = 0LL;

	// Constructor / Destructor
	RealNumber() = default;
	RealNumber(long long value);
	RealNumber(const std::string& value);
	~RealNumber() = default;

	// Getters
	std::string getText() const;

	// Setters
	bool setValue(const std::string& text);

	// Operators
	RealNumber operator+(const RealNumber& other) const;
	RealNumber operator-(const RealNumber& other) const;
	RealNumber operator*(const RealNumber& other) const;
	RealNumber operator/(const RealNumber& other) const;
	RealNumber& operator+=(const RealNumber& other);
	RealNumber& operator-=(const RealNumber& other);
	RealNumber& operator*=(const RealNumber& other);
	RealNumber& operator/=(const RealNumber& other);
	RealNumber& operator=(const RealNumber& other);
	bool operator==(const RealNumber& other) const;
	bool operator<(const RealNumber& other) const;
	bool operator>(const RealNumber& other) const;
	bool operator<=(const RealNumber& other) const;
	bool operator>=(const RealNumber& other) const;
	bool operator!=(const RealNumber& other) const;

};
