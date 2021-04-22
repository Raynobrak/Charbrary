#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("default construct circle", "[Circle]") {
	ch::Circle circle;
	
	REQUIRE(circle.pos.x == 0.f);
	REQUIRE(circle.pos.y == 0.f);
	REQUIRE(circle.radius == 0.f);
}

TEST_CASE("construct circle from position and radius", "[Circle]") {
	ch::Circle circle({ 13.f, 49.f }, 42.5f);

	REQUIRE(circle.pos.x == 13.f);
	REQUIRE(circle.pos.y == 49.f);
	REQUIRE(circle.radius == 42.5f);
}

TEST_CASE("compute circle diameter", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 4);
	REQUIRE(circle.diameter() == 8.f);
}

TEST_CASE("compute circle circumference", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.circumference() == Approx(43.98229715f));
}

TEST_CASE("compute circle area", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.area() == Approx(153.9380400f));
}

TEST_CASE("circle assignment operator", "[Circle]") {
	ch::Circle c({ 1.f,1.f }, 1.f);
	ch::Circle expected({ 434.f,4622.f }, 398523.f);
	c = expected;
	REQUIRE(c == expected);
}

TEST_CASE("circle equality operator", "[Circle]") {
	ch::Circle left({ 1.f,1.f }, 1.f);
	ch::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE(left == right);
}

TEST_CASE("circle inequality operator", "[Circle]") {
	ch::Circle left({ 1.2f,1.f }, 1.f);
	ch::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE_FALSE(left == right);
}