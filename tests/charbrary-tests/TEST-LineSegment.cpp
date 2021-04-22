#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("default construct line segment", "[LineSegment]") {
	ch::LineSegment expected;
	expected.start = ch::vec_t(0.f,0.f);
	expected.end = ch::vec_t(0.f,0.f);

	REQUIRE(ch::LineSegment() == expected);
}

TEST_CASE("construct line segment from 2 points : start and end", "[LineSegment]") {
	ch::LineSegment expected;
	expected.start = ch::vec_t(45.f, -94.f);
	expected.end = ch::vec_t(2.f, 1.f);

	REQUIRE(ch::LineSegment({ 45.f, -94.f }, { 2.f,1.f }) == expected);
}

TEST_CASE("compute line segment slope", "[LineSegment]") {
	ch::LineSegment segment({ 0.f,-2.f }, { 4.f, 0.f });
	REQUIRE(segment.slope() == 0.5f);
}

TEST_CASE("compute slope for vertical line segment (infinite slope)", "[LineSegment]") {
	ch::LineSegment segment({ 7.f,-2.f }, { 7.f, 1.f });

	REQUIRE(segment.slope() == std::numeric_limits<float>::infinity());
}

TEST_CASE("compute line segment length", "[LineSegment]") {
	ch::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.length() == 5.f);
}

TEST_CASE("compute line segment length squared", "[LineSegment]") {
	ch::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.lengthSquared() == 25.f);
}

TEST_CASE("compute x and y size of line segment", "[LineSegment]") {
	ch::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.absoluteSize() == ch::vec_t(4.f, 3.f));
}

TEST_CASE("compute directional vector of line segment", "[LineSegment]") {
	ch::LineSegment segment({ 10.f,10.f }, { 13.f,14.f });
	REQUIRE(segment.dirFromStart() == ch::vec_t(0.6f, 0.8f));
}

TEST_CASE("compute the boundaries of the line segment (min and max values on the x and y axis)", "[LineSegment]") {
	ch::LineSegment segment({ 5.f,14.f }, { 13.f,7.f });

	REQUIRE(segment.minX() == 5.f);
	REQUIRE(segment.maxX() == 13.f);
	REQUIRE(segment.minY() == 7.f);
	REQUIRE(segment.maxY() == 14.f);
}

TEST_CASE("compute the y-intercept of a right", "[LineSegment]") {
	float slope = 0.5f;
	ch::vec_t point(10.f, 3.f);

	float expected = -2.f;

	REQUIRE(ch::LineSegment::YIntercept(point, slope) == expected);
}

TEST_CASE("compute the y-intercept of a vertical right (infinite slope)", "[LineSegment]") {
	ch::LineSegment verticalSegment({ 0.f,0.f }, { 0.f,1.f });

	ch::vec_t point = verticalSegment.start;
	
	constexpr float expected = std::numeric_limits<float>::infinity();

	REQUIRE(ch::LineSegment::YIntercept(point, verticalSegment.slope()) == expected);
}

TEST_CASE("line segment assignment operator", "[LineSegment]") {
	ch::LineSegment segment;
	ch::LineSegment expected({ 0.f,1.f }, { 2.f,3.f });
	REQUIRE_FALSE(segment == expected);
	segment = expected;
	REQUIRE(segment == expected);
}

TEST_CASE("line segment equality operator", "[LineSegment]") {
	ch::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	ch::LineSegment right({ 0.f,1.f }, { 2.f,3.f });

	REQUIRE(left == right);

	ch::LineSegment other(left.end, left.start);

	REQUIRE(other == right);
}

TEST_CASE("line segment inequality operator", "[LineSegment]") {
	ch::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	ch::LineSegment right({ 0.f,2.f }, { 2.f,3.f });
	REQUIRE_FALSE(left == right);
}