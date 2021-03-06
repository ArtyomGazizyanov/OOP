﻿// RationalTest.cpp: определяет точку входа для консольного приложения.
// 

#include "stdafx.h"
#include "../Rational/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}



/*
Рациональное число:
равно нулю по умолчанию (0/1)
может быть созданно из целого в формате (n / 1)
может быть задано с указанием числителя и знаменателя
хранится в нормализованном виде
*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////

void VerifyToDouble(const CRational & r, double expectedNumber)
{
	BOOST_CHECK_EQUAL(r.ToDouble(), expectedNumber); 
}

BOOST_AUTO_TEST_SUITE(Rational_number_to_double_method)
	BOOST_AUTO_TEST_CASE(is_toDouble_working_with_positives)
	{
		VerifyToDouble(CRational(3, 5), 0.6);
	}
	BOOST_AUTO_TEST_CASE(is_toDouble_working_with_negatives)
	{
		VerifyToDouble(CRational(-10, 50), -0.2);
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число с противоположным знаком
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(unary_operators)
	BOOST_AUTO_TEST_CASE(has_unary_plus_that_return_itself)
	{
		VerifyRational(+CRational(3, 5), 3, 5);
		VerifyRational(+CRational(0, 15), 0, 1);
	}

	BOOST_AUTO_TEST_CASE(has_unary_minus_that_return_unsigned_fraction)
	{
		VerifyRational(-CRational(7, 9), -7, 9);
		VerifyRational(-CRational(-7, -9), -7, 9);
		VerifyRational(-CRational(7, -9), 7, 9);
		VerifyRational(-CRational(-7, 9), 7, 9);
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_plus)

	BOOST_AUTO_TEST_CASE(is_binary_operation_pus_working)
	{
		VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 6) + CRational(1, 2), 2, 3);
		VerifyRational(CRational(1, 2) + CRational(1, 2), 1, 1);
		VerifyRational(CRational(1, 2) + 1, 3, 2);
		VerifyRational(1 + CRational(1, 2), 3, 2);
		VerifyRational(CRational(1, 3) + CRational(1, 3) + CRational(1, 3), 1, 1);
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_minus)
	BOOST_AUTO_TEST_CASE(has_binary_subtraction_operation)
	{
		VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 6) - CRational(1, 2), -1, 3);
		VerifyRational(CRational(1, 2) - CRational(1, 2), 0, 1);
		VerifyRational(CRational(1, 2) - 1, -1, 2);
		VerifyRational(1 - CRational(1, 2), 1, 2);
		VerifyRational(CRational(1, 3) - CRational(1, 3) - CRational(1, 3), -1, 3);
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(add_result_operator)
	BOOST_AUTO_TEST_CASE(has_adding_assignment_operator)
	{
		CRational rationalNumber(3, 7);
		VerifyRational(rationalNumber += rationalNumber, 6, 7);
		VerifyRational(rationalNumber += rationalNumber, 12, 7);

		VerifyRational(CRational(1, 2) += CRational(1, 6), 2, 3);
		VerifyRational(CRational(1, 2) += 1, 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(subtract_result_operator)
	BOOST_AUTO_TEST_CASE(has_subtracting_assignment_operator)
	{
		CRational ratNum(3, 7);
		VerifyRational(ratNum -= ratNum, 0, 1);

		VerifyRational(CRational(1, 2) -= CRational(1, 6), 1, 3);
		VerifyRational(CRational(1, 2) -= 1, -1, 2);
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_multiplication_operator)
	BOOST_AUTO_TEST_CASE(has_binary_multiplication_operation)
	{
		VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
		VerifyRational(CRational(2, 3) * CRational(1, 2), 1, 3);
		VerifyRational(CRational(1, 2) * (-3), -3, 2);
		VerifyRational(CRational(11, 4) * 0, 0, 1);
		VerifyRational(CRational(0, 1) * 0, 0, 1);
		VerifyRational(7 * CRational(2, 3), 14, 3);
		VerifyRational(CRational(11, 4) * CRational(3, 2) * CRational(2, 7), 33, 28);
	}
BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(binary_division_operation)
	BOOST_AUTO_TEST_CASE(has_division_operation)
	{
		VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) / 5, 1, 10);
		VerifyRational(0 / CRational(2, 3), 0, 1);
		VerifyRational(7 / CRational(2, 3), 21, 2);
	}

	BOOST_AUTO_TEST_CASE(is_impossible_do_division_by_0)
	{
		BOOST_REQUIRE_THROW(CRational(2, 3) / 0, std::invalid_argument);
		BOOST_REQUIRE_THROW(CRational(2, 3) / CRational(0, 1), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(does_not_changed_by_the_division_by_one)
	{
		VerifyRational(CRational(0, 1) / 1, 0, 1);
		VerifyRational(CRational(2, 3) / -1, -2, 3);
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
////////////////////////////////////////////////////////////////////////// 
BOOST_AUTO_TEST_SUITE(multiplication_assignment_operation)
	BOOST_AUTO_TEST_CASE(has_multiply_assignment_operator)
	{
		CRational ratNum(3, 14);
		VerifyRational(ratNum *= ratNum, 9, 196);
		VerifyRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
		VerifyRational(CRational(1, 2) *= 3, 3, 2);
		VerifyRational(CRational(3, 14) *= 7, 3, 2);
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(division_assignment_operation)
	BOOST_AUTO_TEST_CASE(has_division_assignment_operator)
	{
		CRational ratNum(2, 3);
		VerifyRational(ratNum /= ratNum, 1, 1);
		VerifyRational(CRational(2, 3) /= CRational(2, 3), 1, 1);
		VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
		VerifyRational(CRational(1, 2) /= 3, 1, 6);
	}

	BOOST_AUTO_TEST_CASE(has_division_assignment_operator_impossible_to_divide_by_0)
	{
		BOOST_REQUIRE_THROW(CRational(1, 4) /= 0, std::invalid_argument);
		BOOST_REQUIRE_THROW(CRational(1, 4) /= CRational(0, 1), std::invalid_argument);
	}
BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(equal_not_equal_operators)
	BOOST_AUTO_TEST_CASE(can_be_compared)
	{
		BOOST_CHECK(CRational(1, 2) == CRational(1, 2));
		BOOST_CHECK(CRational(1, 3) == CRational(2, 6));
		BOOST_CHECK(CRational(4, 1) == 4);
		BOOST_CHECK(3 == CRational(3, 1));
		BOOST_CHECK(!(CRational(1, 2) == CRational(2, 3)));
		BOOST_CHECK(!(CRational(1, 2) == 7));
		BOOST_CHECK(!(3 == CRational(2, 3)));
	}
	BOOST_AUTO_TEST_CASE(cant_be_compared)
	{
		BOOST_CHECK(!(CRational(1, 2) != CRational(1, 2)));
		BOOST_CHECK(!(CRational(1, 3) != CRational(2, 6)));
		BOOST_CHECK(!(CRational(4, 1) != 4));
		BOOST_CHECK(!(3 != CRational(3, 1)));
		BOOST_CHECK(CRational(1, 2) != CRational(2, 3));
		BOOST_CHECK(CRational(1, 2) != 7);
		BOOST_CHECK(3 != CRational(2, 3));
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE(has_comparison_operators)
	BOOST_AUTO_TEST_CASE(less_than_operator)
	{
		BOOST_CHECK(CRational(1, 2) < 7);
		BOOST_CHECK(CRational(-1, 2) < 0);
		BOOST_CHECK(0 < CRational(1, 2));
		BOOST_CHECK(!(CRational(1, 2) < 0));
		BOOST_CHECK(!(CRational(1, 2) < CRational(1, 2)));
		BOOST_CHECK(CRational(1, 3) < CRational(1, 2));
		BOOST_CHECK(CRational(-1, 2) < CRational(1, 2));
	}

	BOOST_AUTO_TEST_CASE(greater_than_operator)
	{
		BOOST_CHECK(CRational(3, 1) > 2);
		BOOST_CHECK(CRational(3, 1) > 0);
		BOOST_CHECK(0 > CRational(-1, 2));
		BOOST_CHECK(!(CRational(-1, 2) > 0));
		BOOST_CHECK(CRational(1, 2) > CRational(-1, 2));
		BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
		BOOST_CHECK(!(CRational(1, 3) > CRational(1, 2)));
		BOOST_CHECK(!(CRational(-6, 2) > CRational(-2, 1)));
	}

	BOOST_AUTO_TEST_CASE(less_than_or_equal_operator)
	{
		BOOST_CHECK(3 <= CRational(7, 2));
		BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 3)));
		BOOST_CHECK(CRational(7, 2) <= CRational(7, 2));
		BOOST_CHECK(CRational(7, 3) <= CRational(7, 2));
		BOOST_CHECK(CRational(1, 2) <= 1);
		BOOST_CHECK(0 <= CRational(1, 2));
		BOOST_CHECK(CRational(-1, 2) <= CRational(-1, 3));
	}

	BOOST_AUTO_TEST_CASE(greater_than_or_equal_operator)
	{
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(!(3 >= CRational(8, 2)));
		BOOST_CHECK(CRational(1, 2) >= CRational(1, 3));
		BOOST_CHECK(CRational(7, 2) >= CRational(7, 2));
		BOOST_CHECK(CRational(1, 2) >= 0);
		BOOST_CHECK(1 >= CRational(1, 2));
		BOOST_CHECK(CRational(-1, 3) >= CRational(-1, 2));
	}
BOOST_AUTO_TEST_SUITE_END() 

//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(can_be_printed_to_ostream)
{ 
	{
		std::ostringstream output;
		output << CRational(7, 15);
		BOOST_CHECK_EQUAL(output.str(), "7/15");
	} 
	{
		std::ostringstream output;
		output << "My friend has a " << CRational(1, 2) << " of his bed";
		BOOST_CHECK_EQUAL(output.str(), "My friend has a 1/2 of his bed");
	}
	{
		std::ostringstream output;
		output << CRational(3);
		BOOST_CHECK_EQUAL(output.str(), "3/1");
	}
}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
