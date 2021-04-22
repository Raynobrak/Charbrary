#pragma once

#include "charbrary_and_catch2.h"

#include <array>

TEST_CASE("construct aabb from 2 vectors : the top left corner position and the size", "[AABB]") {
	ch::AABB aabb(ch::vec_t(3.f, 5.f), ch::vec_t(9.f, -8.f));

	REQUIRE(aabb.pos.x == 3.f);
	REQUIRE(aabb.pos.y == 5.f);
	REQUIRE(aabb.size.x == 9.f);
	REQUIRE(aabb.size.y == -8.f);
}

TEST_CASE("construct aabb from 4 floats", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 9.f, -8.f);

	REQUIRE(aabb.pos.x == 3.f);
	REQUIRE(aabb.pos.y == 5.f);
	REQUIRE(aabb.size.x == 9.f);
	REQUIRE(aabb.size.y == -8.f);
}

TEST_CASE("default construct aabb", "[AABB]") {
	ch::AABB aabb;

	REQUIRE(aabb.pos.x == 0.f);
	REQUIRE(aabb.pos.y == 0.f);
	REQUIRE(aabb.size.x == 0.f);
	REQUIRE(aabb.size.y == 0.f);
}

TEST_CASE("move aabb with a translation vector", "[AABB]") {
	ch::AABB aabb(1.f, 8.f, 5.f, 5.f);

	aabb.move({ -7.f,2.f });

	ch::AABB expected(-6.f, 10.f, 5.f, 5.f);

	REQUIRE(aabb == expected);
}

TEST_CASE("compute aabb center position", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t expected(8.f, 15.f);

	REQUIRE(aabb.center() == expected);
}

TEST_CASE("compute top left corner position of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t expected(3.f, 5.f);

	REQUIRE(aabb.corner(ch::Corner::TopLeft) == expected);
}

TEST_CASE("compute top right corner position of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t expected(13.f, 5.f);

	REQUIRE(aabb.corner(ch::Corner::TopRight) == expected);
}

TEST_CASE("compute bottom left corner position of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t expected(3.f, 25.f);

	REQUIRE(aabb.corner(ch::Corner::BottomLeft) == expected);
}

TEST_CASE("compute bottom right corner position of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t expected(13.f, 25.f);

	REQUIRE(aabb.corner(ch::Corner::BottomRight) == expected);
}

TEST_CASE("try to compute invalid corner position of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);

	REQUIRE_THROWS_AS(aabb.corner(static_cast<ch::Corner>(434923)), std::invalid_argument);
}
 
TEST_CASE("compute the position of all 4 corners of aabb", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);

	auto corners = aabb.corners();

	REQUIRE(corners[0] == aabb.corner(ch::Corner::TopLeft));
	REQUIRE(corners[1] == aabb.corner(ch::Corner::TopRight));
	REQUIRE(corners[2] == aabb.corner(ch::Corner::BottomLeft));
	REQUIRE(corners[3] == aabb.corner(ch::Corner::BottomRight));
}

TEST_CASE("scale an aabb relative to its center by a factor smaller than 1", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t centerPosBefore = aabb.center();
	ch::vec_t expectedSize(6.f, 12.f);

	aabb.scaleRelativeToCenter(0.6f);

	REQUIRE(aabb.center() == centerPosBefore);
	REQUIRE(aabb.size == expectedSize);
}

TEST_CASE("scale an aabb relative to its center by a factor greater than 1", "[AABB]") {
	ch::AABB aabb(3.f, 5.f, 10.f, 20.f);
	ch::vec_t centerPosBefore = aabb.center();
	ch::vec_t expectedSize(20.f, 40.f);

	aabb.scaleRelativeToCenter(2.f);

	REQUIRE(aabb.center() == centerPosBefore);
	REQUIRE(aabb.size == expectedSize);
}

TEST_CASE("compute the perimeter of an aabb", "[AABB]") {
	ch::AABB aabb(0.f, 0.f, 1.f, 3.f);
	float expected = 8.f;

	REQUIRE(aabb.perimeter() == expected);
}

TEST_CASE("compute the area of an aabb", "[AABB]") {
	ch::AABB aabb(0.f, 0.f, 2.f, 3.f);
	float expected = 6.f;

	REQUIRE(aabb.area() == expected);
}

TEST_CASE("compute the length of an aabb's diagonals", "[AABB]") {
	ch::AABB aabb(0.f, 0.f, 3.f, 4.f);
	float expected = 5.f;

	REQUIRE(aabb.diagonalLength() == expected);
}

TEST_CASE("aabb assignment operator", "[AABB]") {
	ch::AABB aabb(6.f, 4.f, 10.f, 30.f);
	ch::AABB expected(19.f, 25.f, 45.f, 898.f);
	aabb = expected;

	REQUIRE(aabb == expected);
}

TEST_CASE("aabb equality operator", "[AABB]") {
	ch::AABB first(1.f, 2.f, 3.f, 4.f);
	ch::AABB second(1.f, 2.f, 3.f, 4.f);

	REQUIRE(first == second);
}

TEST_CASE("aabb inequality operator", "[AABB]") {
	ch::AABB first(1.f, 2.f, 3.f, 4.f);
	ch::AABB second(4.f, 3.f, 2.f, 1.f);

	REQUIRE_FALSE(first == second);
}


