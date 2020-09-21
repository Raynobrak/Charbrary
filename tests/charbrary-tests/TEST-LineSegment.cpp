#pragma once

#include "catch.hpp"
#include "../../single-include/charbrary.h"

TEST_CASE("LineSegment, ctor_default") {
	CB::LineSegment expected;
	expected.start = CB::vec_t(0.f,0.f);
	expected.end = CB::vec_t(0.f,0.f);

	REQUIRE(CB::LineSegment() == expected);
}

TEST_CASE("LineSegment, ctor") {
	CB::LineSegment expected;
	expected.start = CB::vec_t(45.f, -94.f);
	expected.end = CB::vec_t(2.f, 1.f);

	REQUIRE(CB::LineSegment({ 45.f, -94.f }, { 2.f,1.f }) == expected);
}

TEST_CASE("LineSegment, slope") {
	CB::LineSegment segment({ 0.f,-2.f }, { 4.f, 0.f });
	REQUIRE(segment.slope() == 0.5f);
}

TEST_CASE("LineSegment, slope_infinite") {
	CB::LineSegment segment({ 7.f,-2.f }, { 7.f, 1.f });
}

TEST_CASE("LineSegment, length") {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.length() == 5.f);
}

TEST_CASE("LineSegment, lengthSquared") {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.lengthSquared() == 25.f);
}

TEST_CASE("LineSegment, absoluteSize") {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	REQUIRE(segment.absoluteSize() == CB::vec_t(4.f, 3.f));
}

TEST_CASE("LineSegment, dirFromStart") {
	CB::LineSegment segment({ 10.f,10.f }, { 13.f,14.f });
	REQUIRE(segment.dirFromStart() == CB::vec_t(0.6f, 0.8f));
}

TEST_CASE("LineSegment, minX_maxX_minY_maxY") {
	CB::LineSegment segment({ 5.f,14.f }, { 13.f,7.f });

	REQUIRE(segment.minX() == 5.f);
	REQUIRE(segment.maxX() == 13.f);
	REQUIRE(segment.minY() == 7.f);
	REQUIRE(segment.maxY() == 14.f);
}

TEST_CASE("LineSegment, enclosingAABB") {
	CB::LineSegment segment({ 5.f,14.f }, { 13.f,7.f });
	REQUIRE(segment.enclosingAABB() == CB::AABB(5.f, 7.f, 8.f, 7.f));
}


TEST_CASE("LineSegment, checkForIntersection_no_intersection") {
	CB::LineSegment first({ -70.f,4.f }, { -1.f,10.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::None);
}

TEST_CASE("LineSegment, checkForIntersection_crossing_segments") {
	CB::LineSegment first({ -7.f,4.f }, { -1.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::Crossing);
	REQUIRE(intersection.point == CB::vec_t(-3.f, 2.f));
}

TEST_CASE("LineSegment, checkForIntersection_intersecting_aabbs_but_no_crossing") {
	CB::LineSegment first({ -7.f,4.f }, { -1.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -3.f,3.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::None);
}

TEST_CASE("LineSegment, checkForIntersection_segments_crossing_at_yIntercept") {
	CB::LineSegment first({ 9.f,-5.f }, { -3.f,3.f });
	CB::LineSegment second({ -3.f,-1.f }, { 6.f,5.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::Crossing);
	REQUIRE(intersection.point == CB::vec_t(0.f, 1.f));
}

TEST_CASE("LineSegment, checkForIntersection_parallel_segments") {
	CB::LineSegment first({ -2.f,4.f }, { -5.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::None);
}

TEST_CASE("LineSegment, checkForIntersection_vertically_parallel_segments") {
	CB::LineSegment first({ -3.f,3.f }, { -3.f,2.f });
	CB::LineSegment second({ -2.f,4.f }, { -2.f,-1.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::None);
}

TEST_CASE("LineSegment, checkForIntersection_overlapping_segments") {
	CB::LineSegment first({ -11.f,3.f }, { -5.f,0.f });
	CB::LineSegment second({ -7.f,1.f }, { -3.f,-1.f });
	auto intersection = first.checkForIntersection(second);
	
	REQUIRE(intersection.type == CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	REQUIRE(CB::LineSegment({ -7.f,1.f }, { -5.f, 0.f }) == expected);
}

TEST_CASE("LineSegment, checkForIntersection_vertically_overlapping_segments") {
	CB::LineSegment first({ -5.f,-1.f }, { -5.f,2.f });
	CB::LineSegment second({ -5.f,0.f }, { -5.f,-4.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	REQUIRE(CB::LineSegment({ -5.f,-1.f }, { -5.f, 0.f }) == expected);
}

TEST_CASE("LineSegment, checkForIntersection_horizontally_overlapping_segments") {
	CB::LineSegment first({ -1.f,-4.f }, { 3.f,-4.f });
	CB::LineSegment second({ 0.f,-4.f }, { 5.f,-4.f });
	auto intersection = first.checkForIntersection(second);

	REQUIRE(intersection.type == CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	REQUIRE(CB::LineSegment({ 0.f,-4.f }, { 3.f, -4.f }) == expected);
}


TEST_CASE("LineSegment, YIntercept") {
	float slope = 0.5f;
	CB::vec_t point(10.f, 3.f);

	float expected = -2.f;

	REQUIRE(CB::LineSegment::YIntercept(point, slope) == expected);
}

TEST_CASE("LineSegment, YIntercept_infinite_slope") {
	CB::LineSegment verticalSegment({ 0.f,0.f }, { 0.f,1.f });

	CB::vec_t point = verticalSegment.start;
	
	constexpr float expected = std::numeric_limits<float>::infinity();

	REQUIRE(CB::LineSegment::YIntercept(point, verticalSegment.slope()) == expected);
}

TEST_CASE("LineSegment, assignment_operator") {
	CB::LineSegment segment;
	CB::LineSegment expected({ 0.f,1.f }, { 2.f,3.f });
	REQUIRE_FALSE(segment == expected);
	segment = expected;
	REQUIRE(segment == expected);
}

TEST_CASE("LineSegment, equality_operator") {
	CB::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	CB::LineSegment right({ 0.f,1.f }, { 2.f,3.f });

	REQUIRE(left == right);

	CB::LineSegment other(left.end, left.start);

	REQUIRE(other == right);
}

TEST_CASE("LineSegment, inequality_operator") {
	CB::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	CB::LineSegment right({ 0.f,2.f }, { 2.f,3.f });
	REQUIRE_FALSE(left == right);
}