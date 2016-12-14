#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>
#include <cassert>
#include <string>
 
void CRational::Initialization(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	m_numerator = numerator;
	m_denominator = denominator;
	Normalize();
}

CRational::CRational(int numerator, int denominator)
{
	Initialization(numerator, denominator);
} 

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}
//находит наибольший общий делитель для двух чисел
unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}
//находит наименьший общий делитель для двух чисел
unsigned LCM(unsigned a, unsigned b)
{
	return a / GCD(a, b) * b;
}


void CRational::SetNumerator(int numerator)
{
	m_numerator = numerator;
}

void CRational::SetDenominator(int denominator)
{
	m_denominator = denominator;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////

double CRational::ToDouble() const
{ 
	return static_cast<double>(m_numerator) / m_denominator;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////
const CRational CRational::operator+() const
{
	return *this;
}

const CRational CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}


//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
////////////////////////////////////////////////////////////////////////// 
const CRational operator+(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	int denominator = lRationalNumber.GetDenominator() * rRationalNumber.GetDenominator();
	int numerator = lRationalNumber.GetNumerator() * rRationalNumber.GetDenominator() + rRationalNumber.GetNumerator() * lRationalNumber.GetDenominator();
	return CRational(numerator, denominator);
} 

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////
const CRational operator-(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return lRationalNumber + CRational(-rRationalNumber.m_numerator, rRationalNumber.m_denominator); 
}

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator+=(const CRational & sumNumber)
{ 
	return *this = *this + sumNumber;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator-=(const CRational & substrNumber)
{
#pragma message("use +=") //DONE!
	return *this += -CRational(substrNumber.m_numerator, substrNumber.m_denominator); 
}
 
//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////
const CRational operator*(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return CRational(lRationalNumber.GetNumerator() * rRationalNumber.GetNumerator(), 
		lRationalNumber.GetDenominator() * rRationalNumber.GetDenominator());
} 

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////
const CRational operator/(const CRational & dividend, const CRational & divider)
{
#pragma message("use *") // DONE!
	return dividend * CRational(divider.m_denominator, divider.m_numerator);
} 

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator*=(const CRational & multiplier)
{
	Initialization(multiplier.GetNumerator() * m_numerator, multiplier.GetDenominator() * m_denominator);
	return *this;
}
 
//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator/=(const CRational & divider)
{
#pragma message("use *=")//Done
	return *this *= CRational(divider.m_denominator, divider.m_numerator);
}

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////

const bool operator == (const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return (lRationalNumber.GetNumerator() == rRationalNumber.GetNumerator() &&
		lRationalNumber.GetDenominator() == rRationalNumber.GetDenominator());
}

const bool operator != (const CRational & lRationalNumber, const CRational & rRationalNumber)
{
#pragma message("use ==") //Done!
	return !(lRationalNumber == rRationalNumber); 
}
 
//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////
const bool operator<(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return (lRationalNumber.GetNumerator() * rRationalNumber.GetDenominator() < rRationalNumber.GetNumerator() * lRationalNumber.GetDenominator());
}

const bool operator>(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return (lRationalNumber.GetNumerator() * rRationalNumber.GetDenominator() > rRationalNumber.GetNumerator() * lRationalNumber.GetDenominator());
}

const bool operator<=(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return !(lRationalNumber > rRationalNumber);
}

const bool operator>=(const CRational & lRationalNumber, const CRational & rRationalNumber)
{
	return !(lRationalNumber < rRationalNumber);
} 

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////

std::ostream & operator<<(std::ostream & output, const CRational & value)
{
	output << value.GetNumerator() << '/' << value.GetDenominator();
	return output;
} 
