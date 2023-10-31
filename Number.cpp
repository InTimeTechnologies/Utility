#include "Number.h"

// Dependencies | std
#include <stdexcept>

// class Number

// Static | public

// Properties
const int Number::MAX_DIGIT_COUNT = 18;
const int Number::MAX_WHOLE_DIGIT_COUNT = 10;
const int Number::MAX_DECIMAL_DIGIT_COUNT = 8;

// Object | public

// Constructor / Destructor
Number::Number() : value(0LL), text("0.0") {

}
Number::Number(long long amount) : Number() {
	setValue(amount);
}
Number::Number(const std::string& stringAmount) : Number() {
	setValue(stringAmount);
}
Number::~Number() {

}

// Getters
long long Number::getValue() const {
	return value;
}
std::string Number::getText() const {
	return text;
}

// Setters
bool Number::setValue(long long value) {
	// Local variable string
	std::string string = std::to_string(value);
	bool isNegative = false;
	if (value < 0LL)
		isNegative = true;

	if (string.size() <= MAX_DECIMAL_DIGIT_COUNT) {
		// Update properties
		this->value = value;
		std::string decimalDigitFillers = std::string(MAX_DECIMAL_DIGIT_COUNT - string.size(), '0');

		// Remove trailing zeros
		while (string.size() > 0) {
			if (string[string.size() - 1] == '0') {
				string.erase(string.size() - 1);
				continue;
			}
			break;
		}
		text = "0." + decimalDigitFillers + string;

		// Return success
		return true;
	}

	if (string.size() <= MAX_DIGIT_COUNT) {
		// Update properties
		this->value = value;

		// Add decimal point to string
		string.insert(string.begin() + string.length() - MAX_DECIMAL_DIGIT_COUNT, '.');

		// Remove significant position except the tenth significant position
		int originalLength = string.length();
		for (int i = originalLength - 1; i > originalLength - 8; i--) {
			if (string[i] == '0') {
				string.erase(i);
				continue;
			}
			break;
		}

		// Update properties
		text = string;

		// Return success
		return true;
	}

	// Return fail
	return false;
}
bool Number::setValue(const std::string& string) {
	// If string is empty, reset properties
	if (string.length() == 0) {
		value = 0LL;
		text = "0.0";
		return true;
	}

	// Local variables
	std::string stringBuild = "";
	bool isNegative = false;

	if (string[0] == '-') {
		isNegative = true;
		stringBuild = string.substr(1, string.length() - 1);
	}
	else {
		stringBuild = string;
	}

	// Counters and flags
	int digitCount = 0;
	int wholeDigitCount = 0;
	int decimalDigitCount = 0;
	bool hasDecimalPoint = false;

	// Go through stringBuild updating counters and flags
	for (char c : stringBuild) {
		bool detectedValidCharacter = false;

		if (c == '.') {
			if (hasDecimalPoint)
				return false;
			else
				hasDecimalPoint = true;

			detectedValidCharacter = true;
		}

		if (std::isdigit(c)) {
			digitCount++;

			if (hasDecimalPoint)
				decimalDigitCount++;
			else
				wholeDigitCount++;

			detectedValidCharacter = true;
		}

		if (!detectedValidCharacter || digitCount > MAX_DIGIT_COUNT || wholeDigitCount > MAX_WHOLE_DIGIT_COUNT || decimalDigitCount > MAX_DECIMAL_DIGIT_COUNT || (decimalDigitCount > 0 && !hasDecimalPoint))
			return false;
	}

	// Resulting formatted and validated number
	std::string formattedText = "";

	// Whole number part
	if (wholeDigitCount == 0)
		formattedText += "0";
	else
		formattedText += stringBuild.substr((size_t)0, (size_t)wholeDigitCount);

	// Decimal point part
	formattedText += ".";

	// Decimal number part
	if (decimalDigitCount > 0)
		formattedText += stringBuild.substr((size_t)(wholeDigitCount + 1), (size_t)decimalDigitCount);

	// Update properties
	if (isNegative)
		text = "-" + formattedText;
	else
		text = formattedText;

	if (decimalDigitCount < MAX_DECIMAL_DIGIT_COUNT)
		formattedText = formattedText + std::string(MAX_DECIMAL_DIGIT_COUNT - decimalDigitCount, '0');
	size_t decimalPointIndex = formattedText.find('.');
	formattedText.erase(decimalPointIndex, 1);
	value = std::stoll(formattedText);
	if (isNegative)
		value *= -1LL;

	// Return success
	return true;
}

// Functions
std::string Number::to_string() const {
	return text;
}

// Operators
Number Number::operator+(const Number& other) const {
	return Number(value + other.value);
}
Number Number::operator-(const Number& other) const {
	return Number(value - other.value);
}
Number Number::operator*(const Number& other) const {
	if (other.value == 0LL)
		return Number();

	long long thisWholePart = value / 100000000LL;
	long long thisDecimalPart = value % 100000000LL;

	long long otherWholePart = other.value / 100000000LL;
	long long otherDecimalPart = other.value % 100000000LL;

	long long resultWholePart = thisWholePart * otherWholePart;
	long long resultDecimalPart = 0LL;
	if (other.value != 0LL)
		resultDecimalPart = thisWholePart * otherDecimalPart + otherWholePart * thisDecimalPart + (thisDecimalPart * otherDecimalPart) / 100000000LL;

	long long result = resultWholePart * 100000000LL + resultDecimalPart;

	return Number(result);
}
Number Number::operator/(const Number& other) const {
	if (other.value == 0LL) {
		// Division by zero is undefined, so return a default-constructed Number (0.0).
		return Number();
	}

	// Find the common scale for both numbers
	long long common_scale = 100000000LL;
	// long long thisValue = value;
	// long long otherValue = other.value;

	// while (thisValue >= 100000000LL || otherValue >= 100000000LL) {
	// 	common_scale *= 10LL;
	// 	thisValue /= 10LL;
	// 	otherValue /= 10LL;
	//  }

	// Convert both numbers to the common scale
	long long this_scaled = value * (100000000LL / common_scale);
	long long other_scaled = other.value * (100000000LL / common_scale);

	// Perform the division
	long long result_scaled = (this_scaled * common_scale) / other_scaled;

	return Number(result_scaled);

	/*
	if (other.value == 0LL) {
		// Division by zero is undefined, so return a default-constructed Number (0.0).
		return Number();
	}

	long long thisWholePart = value / 100000000LL;
	long long thisDecimalPart = value % 100000000LL;

	long long otherWholePart = other.value / 100000000LL;
	long long otherDecimalPart = other.value % 100000000LL;

	long long resultWholePart = thisWholePart / otherWholePart;
	long long resultDecimalPart = 0LL;
	if (other.value != 0LL) {
		long long scaledThisDecimalPart = thisDecimalPart * 10000000LL;
		resultDecimalPart = (scaledThisDecimalPart / other.value) + ((scaledThisDecimalPart % other.value) * 10000000LL) / other.value;
	}

	long long result = resultWholePart * 100000000LL + resultDecimalPart;

	return Number(result);
	*/
	/*
	if (other.value == 0LL) {
		// Division by zero is undefined, so return a default-constructed Number (0.0).
		return Number();
	}

	// Find the common scale for both numbers
	long long common_scale = 1LL;
	long long this_temp = value;
	long long other_temp = other.value;

	while (this_temp >= 100000000LL || other_temp >= 100000000LL) {
		common_scale *= 10LL;
		this_temp /= 10LL;
		other_temp /= 10LL;
	}

	// Convert both numbers to the common scale
	long long this_scaled = value * (100000000LL / common_scale);
	long long other_scaled = other.value * (100000000LL / common_scale);

	// Perform the division
	long long result_scaled = this_scaled / other_scaled;

	// Adjust the scale of the result
	long long result = result_scaled * common_scale;

	return Number(result);
	*/
	/*
	if (other.amount == 0LL)
		return Number();

	long long thisWholePart = amount / 100000000LL;
	long long thisDecimalPart = amount % 100000000LL;

	long long otherWholePart = other.amount / 100000000LL;
	long long otherDecimalPart = other.amount % 100000000LL;

	// Ensure we have enough decimal places for accuracy in the result.
	long long scaledThisDecimalPart = thisDecimalPart * 10000000LL;

	// Perform division for the whole parts and scaled decimal parts.
	long long resultWholePart = (thisWholePart * 100000000LL + scaledThisDecimalPart) / other.amount;

	// Calculate the remainder for decimal parts.
	long long remainder = (thisWholePart * 100000000LL + scaledThisDecimalPart) % other.amount;

	// Calculate the decimal part of the result.
	long long resultDecimalPart = 0LL;
	if (remainder != 0LL) {
		// Ensure enough precision for the division.
		remainder *= 10000000LL;

		// Calculate the decimal part of the result.
		resultDecimalPart = remainder / other.amount;
	}

	long long result = resultWholePart * 100000000LL + resultDecimalPart;

	return Number(result);
	*/
}
Number& Number::operator+=(const Number& other) {
	setValue(value + other.value);
	return *this;
}
Number& Number::operator-=(const Number& other) {
	setValue(value - other.value);
	return *this;
}
Number& Number::operator*=(const Number& other) {
	setValue(value * other.value);
	return *this;
}
Number& Number::operator/=(const Number& other) {
	setValue(value / other.value);
	return *this;
}
Number& Number::operator=(const Number& other) {
	if (this != &other)
		setValue(other.value);
	return *this;
}
bool Number::operator==(const Number& other) const {
	return value == other.value;
}
bool Number::operator<(const Number& other) const {
	return value < other.value;
}
bool Number::operator>(const Number& other) const {
	return value > other.value;
}
bool Number::operator<=(const Number& other) const {
	return value <= other.value;
}
bool Number::operator>=(const Number& other) const {
	return value >= other.value;
}
bool Number::operator!=(const Number& other) const {
	return value != other.value;
}
