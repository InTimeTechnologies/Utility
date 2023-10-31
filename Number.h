#pragma once

// Dependencies | std
#include <string>

class Number {
	// Static
	public:
		// Properties
		static const int MAX_DIGIT_COUNT;
		static const int MAX_WHOLE_DIGIT_COUNT;
		static const int MAX_DECIMAL_DIGIT_COUNT;

	// Object
	private:
		// Properties
		long long value;
		std::string text;
	public:
		// Constructor / Destructor
		Number();
		Number(long long value);
		Number(const std::string& text);
		~Number();

		// Getters
		long long getValue() const;
		std::string getText() const;

		// Setters
		bool setValue(long long value);
		bool setValue(const std::string& string);

		// Functions
		std::string to_string() const;

		// Operators
		Number operator+(const Number& other) const;
		Number operator-(const Number& other) const;
		Number operator*(const Number& other) const;
		Number operator/(const Number& other) const;
		Number& operator+=(const Number& other);
		Number& operator-=(const Number& other);
		Number& operator*=(const Number& other);
		Number& operator/=(const Number& other);
		Number& operator=(const Number& other);
		bool operator==(const Number& other) const;
        bool operator<(const Number& other) const;
        bool operator>(const Number& other) const;
        bool operator<=(const Number& other) const;
        bool operator>=(const Number& other) const;
        bool operator!=(const Number& other) const;
};

// Notes
/*
 * long long range: [-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807]
 * long long range as decimal: [92,233,720,368.54775807,
 */
