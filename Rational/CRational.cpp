#include "CRational.h"

CRational::CRational(int value)
	: CRational(value, 1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
	{
		throw std::invalid_argument("zero denominator");
	}

	if (m_denominator < 0)
	{
		m_numerator *= -1;
		m_denominator *= -1;
	}

	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return m_numerator / static_cast<double>(m_denominator);
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int integerPart = m_numerator / m_denominator;
	int newNumerator = m_numerator % m_denominator;

	return { integerPart, { newNumerator, m_denominator } };
}

CRational CRational::operator+() const
{
	return *this;
}

CRational CRational::operator-() const
{
	return { -m_numerator, m_denominator };
}

CRational& CRational::operator+=(CRational const& other)
{
	int commonDenominator = std::lcm(GetDenominator(), other.GetDenominator());
	int numerator1 = GetNumerator() * (commonDenominator / GetDenominator());
	int numerator2 = other.GetNumerator() * (commonDenominator / other.GetDenominator());

	*this = CRational(numerator1 + numerator2, commonDenominator);
	return *this;
}

CRational& CRational::operator-=(CRational const& other)
{
	return *this += (-other);
}

CRational& CRational::operator*=(CRational const& other)
{
	int numerator = GetNumerator() * other.GetNumerator();
	int denominator = GetDenominator() * other.GetDenominator();

	*this = CRational(numerator, denominator);
	return *this;
}

CRational& CRational::operator/=(CRational const& other)
{
	return *this *= CRational(other.GetDenominator(), other.GetNumerator());
}

std::strong_ordering CRational::operator<=>(CRational const& rhs) const
{
	int commonDenominator = std::lcm(GetDenominator(), rhs.GetDenominator());
	int numerator1 = GetNumerator() * (commonDenominator / GetDenominator());
	int numerator2 = rhs.GetNumerator() * (commonDenominator / rhs.GetDenominator());

	return numerator1 <=> numerator2;
}

CRational operator+(CRational r1, CRational const& r2)
{
	return r1 += r2;
}

CRational operator-(CRational r1, CRational const& r2)
{
	return r1 -= r2;
}

CRational operator*(CRational r1, CRational const& r2)
{
	return r1 *= r2;
}

CRational operator/(CRational r1, CRational const& r2)
{
	return r1 /= r2;
}

std::ostream& operator<<(std::ostream& stream, CRational const& r)
{
	stream << r.GetNumerator() << '/' << r.GetDenominator();
	return stream;
}

std::istream& operator>>(std::istream& stream, CRational& r)
{
	int numerator;
	int denominator;
	char divider;

	if (!(stream >> numerator) || !(stream >> divider) || !(stream >> denominator) || divider != '/')
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
		return stream;
	}

	r = CRational(numerator, denominator);
	return stream;
}

void CRational::Normalize()
{
	int gcd = std::gcd(m_numerator, m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}