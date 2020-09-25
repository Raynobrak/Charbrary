#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("Vector, ctor") {
	CB::Vector v(54.f, -23.f);

	REQUIRE(v.x == 54.f);
	REQUIRE(v.y == -23.f);
}

TEST_CASE("Vector, ctor_default") {
	CB::Vector v; 

	REQUIRE(v.x == 0.f);
	REQUIRE(v.y == 0.f);
}

TEST_CASE("Vector, add_assign_operator") {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	REQUIRE((first += second) == expected);
}

TEST_CASE("Vector, substract_assign_operator") {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	REQUIRE((first -= second) == expected);
}

TEST_CASE("Vector, multiply_assign_operator") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	REQUIRE((vector *= scalar) == expected);
}

TEST_CASE("Vector, divide_assign_operator") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	REQUIRE((vector /= scalar) == expected);
}

TEST_CASE("Vector, divide_assign_operator_div0_exception") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	REQUIRE_THROWS_AS(vector /= scalar, std::invalid_argument);
}

TEST_CASE("Vector, assign_operator") {
	CB::Vector vector(-456.f, 201.f);

	CB::Vector expected(13.f, -8.f);

	vector = expected;

	REQUIRE(vector == expected);
}

TEST_CASE("Vector, add_operator") {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	REQUIRE(first + second == expected);
}

TEST_CASE("Vector, substract_operator") {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	REQUIRE(first - second == expected);
}

TEST_CASE("Vector, unary_minus_operator") {
	CB::Vector v(45.f, -39.f);
	CB::Vector expected(-45.f, 39.f);

	REQUIRE(-v == expected);
}

TEST_CASE("Vector, multiply_operator") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	REQUIRE(vector * scalar == expected);
}

TEST_CASE("Vector, divide_operator") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	REQUIRE(vector / scalar == expected);
}

TEST_CASE("Vector, divide_operator_div0_exception") {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	REQUIRE_THROWS_AS(vector / scalar, std::invalid_argument);
}

TEST_CASE("Vector, equal_operator") {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.f, -4.7f);

	REQUIRE(a == b);
}

TEST_CASE("Vector, not_equal_operator") {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.1f, -4.7f);

	REQUIRE(a != b);
}


