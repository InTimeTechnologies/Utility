#include "RealNumber.h"

// struct RealNumber

// Static

// Properties
const std::regex RealNumber::REAL_NUMBER_PATTERN(R"(^[-+]?\d+(\.\d*)?$)");
const std::regex RealNumber::WHOLE_PART_PATTERN(R"(^\d+)");
const std::regex RealNumber::DECIMAL_PART_PATTERN(R"(\d{0,8})");

// Object

// Constructor / Destructor
RealNumber::RealNumber(long long value) : value(value) {

}
RealNumber::RealNumber(const std::string& value) {
	setValue(value);
}

// Getters
std::string RealNumber::getText() const {
	std::string text = std::to_string(value);

	if (text.length() < 9)
		text = std::string(9 - text.length(), '0') + text;

	text.insert(text.end() - 8, '.');
	
	return text;
}

// Setters
bool RealNumber::setValue(const std::string& text) {
	// Validate input
	bool validExpression = std::regex_match(text, REAL_NUMBER_PATTERN);
	if (!validExpression)
		return false; // Return fail

	// Local variables
	std::string textCopy = text;
	std::smatch match = std::smatch();

	// Text separated by parts
	long long sign = 1LL;
	std::string wholePart = std::string();
	std::string decimalPart = std::string();

	// Get sign
	switch (textCopy[0]) {
		case '-':
			sign = -1LL;
			[[fallthrough]];
		case '+':
			textCopy.erase(0, 1);
			[[fallthrough]];
		default:
			break;
	}

	// Get whole part
	std::regex_search(textCopy, match, WHOLE_PART_PATTERN);
	wholePart = match.str();
	textCopy.erase(0, wholePart.size());

	// Does textCopy have a decimal part?
	if (textCopy.length() > 0 && textCopy[0] == '.') {
		textCopy.erase(0, 1); // Erase the decimal point. It is not needed

		// Get decimal numbers if any
		if (textCopy.size() > 0) {
			match = std::smatch();
			std::regex_search(textCopy, match, DECIMAL_PART_PATTERN);
			decimalPart = match.str();
		}
	}

	// Fill in trailing zeroes to decimal part as needed
	decimalPart += std::string(8 - decimalPart.length(), '0');

	// Convert text to value : long long
	value = std::stoll(wholePart) * 100000000;
	value += std::stoll(decimalPart);
	value *= sign;

	// Return success
	return true;
}

RealNumber RealNumber::operator+(const RealNumber& other) const {
	return RealNumber(value + other.value);
}
RealNumber RealNumber::operator-(const RealNumber& other) const {
	return RealNumber(value - other.value);
}
RealNumber RealNumber::operator*(const RealNumber& other) const {
	if (other.value == 0LL)
		return RealNumber(0LL);

	long long thisWholePart = value / 100000000LL;
	long long thisDecimalPart = value % 100000000LL;

	long long otherWholePart = other.value / 100000000LL;
	long long otherDecimalPart = other.value % 100000000LL;

	long long resultWholePart = thisWholePart * otherWholePart;
	long long resultDecimalPart = 0LL;
	if (other.value != 0LL)
		resultDecimalPart = thisWholePart * otherDecimalPart + otherWholePart * thisDecimalPart + (thisDecimalPart * otherDecimalPart) / 100000000LL;

	long long result = resultWholePart * 100000000LL + resultDecimalPart;

	return RealNumber(result);
}
RealNumber RealNumber::operator/(const RealNumber& other) const {
	if (other.value == 0LL)
		return RealNumber(0LL);
	return RealNumber((value * 100000000) / other.value);
}
RealNumber& RealNumber::operator+=(const RealNumber& other) {
	value += other.value;
	return *this;
}
RealNumber& RealNumber::operator-=(const RealNumber& other) {
	value += other.value;
	return *this;
}
RealNumber& RealNumber::operator*=(const RealNumber& other) {
	value += other.value;
	return *this;
}
RealNumber& RealNumber::operator/=(const RealNumber& other) {
	value += other.value;
	return *this;
}
RealNumber& RealNumber::operator=(const RealNumber& other) {
	if (this != &other)
		value += other.value;
	return *this;
}
bool RealNumber::operator==(const RealNumber& other) const {
	return value == other.value;
}
bool RealNumber::operator<(const RealNumber& other) const {
	return value < other.value;
}
bool RealNumber::operator>(const RealNumber& other) const {
	return value > other.value;
}
bool RealNumber::operator<=(const RealNumber& other) const {
	return value <= other.value;
}
bool RealNumber::operator>=(const RealNumber& other) const {
	return value >= other.value;
}
bool RealNumber::operator!=(const RealNumber& other) const {
	return value != other.value;
}
