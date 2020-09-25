#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("construct vector from 2 floats", "[Vector]") {
	CB::Vector v(54.f, -23.f);

	REQUIRE(v.x == 54.f);
	REQUIRE(v.y == -23.f);
}

TEST_CASE("default construct vector", "[Vector]) {
	CB::Vector v; 

	REQUIRE(v.x == 0.f);
	REQUIRE(v.y == 0.f);
}

TEST_CASE("vector add-assign operator", "[Vector]) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	REQUIRE((first += second) == expected);
}

TEST_CASE("vector substract-assign operator", "[Vector]) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	REQUIRE((first -= second) == expected);
}

TEST_CASE("vector multiply-assign operator", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	REQUIRE((vector *= scalar) == expected);
}

TEST_CASE("vector divide-assign operator", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	REQUIRE((vector /= scalar) == expected);
}

TEST_CASE("vector divide assign operator with division by 0", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	REQUIRE_THROWS_AS(vector /= scalar, std::invalid_argument);
}

TEST_CASE("vector assignment operator", "[Vector]) {
	CB::Vector vector(-456.f, 201.f);

	CB::Vector expected(13.f, -8.f);

	vector = expected;

	REQUIRE(vector == expected);
}

TEST_CASE("vector plus (+) operator", "[Vector]) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	REQUIRE(first + second == expected);
}

TEST_CASE("vector minus (-) operator", "[Vector]) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	REQUIRE(first - second == expected);
}

TEST_CASE("vector unary-minus operator", "[Vector]) {
	CB::Vector v(45.f, -39.f);
	CB::Vector expected(-45.f, 39.f);

	REQUIRE(-v == expected);
}

TEST_CASE("vector multiply operator", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	REQUIRE(vector * scalar == expected);
}

TEST_CASE("vector divide operator", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	REQUIRE(vector / scalar == expected);
}

TEST_CASE("vector divide operator with division by 0", "[Vector]) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	REQUIRE_THROWS_AS(vector / scalar, std::invalid_argument);
}

TEST_CASE("vector equality operator", "[Vector]) {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.f, -4.7f);

	REQUIRE(a == b);
}

TEST_CASE("vector inequality operator", "[Vector]) {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.1f, -4.7f);

	REQUIRE(a != b);
}


