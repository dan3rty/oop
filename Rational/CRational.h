#pragma once

#include <iostream>
#include <numeric>
#include <compare>

class CRational
{
public:
	CRational() = default;
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;

	double ToDouble() const;

	std::pair<int, CRational> ToCompoundFraction() const;

	// конст тож нинада (исправлено)
	CRational operator+() const;
	CRational operator-() const;

	CRational& operator+=(CRational const& other);
	CRational& operator-=(CRational const& other);

	CRational& operator*=(CRational const& other);
	CRational& operator/=(CRational const& other);

	std::strong_ordering operator<=>(CRational const& rhs) const;
	bool operator==(CRational const& rhs) const = default;

private:
	void Normalize();

	int m_numerator = 0;
	int m_denominator = 1;
};

// нинада конст (пользы никакой) (исправлено)
CRational operator+(CRational r1, CRational const& r2);
CRational operator-(CRational r1, CRational const& r2);

CRational operator*(CRational r1, CRational const& r2);
CRational operator/(CRational r1, CRational const& r2);

// spaceship (исправлено)

std::ostream& operator<<(std::ostream& stream, CRational const& r);
std::istream& operator>>(std::istream& stream, CRational& r);