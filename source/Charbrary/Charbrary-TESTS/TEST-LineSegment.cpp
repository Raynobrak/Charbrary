#pragma once

#include "pch.h"

#include "../Physics/LineSegment.h"
#include "../Physics/SegmentsIntersection.h"

TEST(LineSegment, ctor_default) {
	CB::LineSegment expected;
	expected.start = CB::vec_t(0.f,0.f);
	expected.end = CB::vec_t(0.f,0.f);

	EXPECT_EQ(CB::LineSegment(), expected);
}

TEST(LineSegment, ctor) {
	CB::LineSegment expected;
	expected.start = CB::vec_t(45.f, -94.f);
	expected.end = CB::vec_t(2.f, 1.f);

	EXPECT_EQ(CB::LineSegment({ 45.f, -94.f }, { 2.f,1.f }), expected);
}

TEST(LineSegment, slope) {
	CB::LineSegment segment({ 0.f,-2.f }, { 4.f, 0.f });
	EXPECT_FLOAT_EQ(segment.slope(), 0.5f);
}

TEST(LineSegment, slope_infinite) {
	CB::LineSegment segment({ 7.f,-2.f }, { 7.f, 1.f });
}

TEST(LineSegment, length) {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	EXPECT_FLOAT_EQ(segment.length(), 5.f);
}

TEST(LineSegment, lengthSquared) {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	EXPECT_FLOAT_EQ(segment.lengthSquared(), 25.f);
}

TEST(LineSegment, absoluteSize) {
	CB::LineSegment segment({ -6.f, -2.f }, { -10.f,-5.f });
	EXPECT_EQ(segment.absoluteSize(), CB::vec_t(4.f, 3.f));
}

TEST(LineSegment, dirFromStart) {
	CB::LineSegment segment({ 10.f,10.f }, { 13.f,14.f });
	EXPECT_EQ(segment.dirFromStart(), CB::vec_t(0.6f, 0.8f));
}

TEST(LineSegment, minX_maxX_minY_maxY) {
	CB::LineSegment segment({ 5.f,14.f }, { 13.f,7.f });

	EXPECT_EQ(segment.minX(), 5.f);
	EXPECT_EQ(segment.maxX(), 13.f);
	EXPECT_EQ(segment.minY(), 7.f);
	EXPECT_EQ(segment.maxY(), 14.f);
}

TEST(LineSegment, enclosingAABB) {
	CB::LineSegment segment({ 5.f,14.f }, { 13.f,7.f });
	EXPECT_EQ(segment.enclosingAABB(), CB::AABB(5.f, 7.f, 8.f, 7.f));
}


TEST(LineSegment, checkForIntersection_no_intersection) {
	CB::LineSegment first({ -70.f,4.f }, { -1.f,10.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	EXPECT_EQ(intersection.type, CB::IntersectionType::None);
}

TEST(LineSegment, checkForIntersection_crossing_segments) {
	CB::LineSegment first({ -7.f,4.f }, { -1.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	EXPECT_EQ(intersection.type, CB::IntersectionType::Crossing);
	EXPECT_EQ(intersection.point, CB::vec_t(-3.f, 2.f));
}

TEST(LineSegment, checkForIntersection_intersecting_aabbs_but_no_crossing) {
	CB::LineSegment first({ -7.f,4.f }, { -1.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -3.f,3.f });
	auto intersection = first.checkForIntersection(second);

	EXPECT_EQ(intersection.type, CB::IntersectionType::None);
}

TEST(LineSegment, checkForIntersection_segments_crossing_at_yIntercept) {
	CB::LineSegment first({ 9.f,-5.f }, { -3.f,3.f });
	CB::LineSegment second({ -3.f,-1.f }, { 6.f,5.f });
	auto intersection = first.checkForIntersection(second);

	ASSERT_EQ(intersection.type, CB::IntersectionType::Crossing);
	EXPECT_EQ(intersection.point, CB::vec_t(0.f, 1.f));
}

TEST(LineSegment, checkForIntersection_parallel_segments) {
	CB::LineSegment first({ -2.f,4.f }, { -5.f,1.f });
	CB::LineSegment second({ -1.f,4.f }, { -4.f,1.f });
	auto intersection = first.checkForIntersection(second);

	EXPECT_EQ(intersection.type, CB::IntersectionType::None);
}

TEST(LineSegment, checkForIntersection_vertically_parallel_segments) {
	CB::LineSegment first({ -3.f,3.f }, { -3.f,2.f });
	CB::LineSegment second({ -2.f,4.f }, { -2.f,-1.f });
	auto intersection = first.checkForIntersection(second);

	EXPECT_EQ(intersection.type, CB::IntersectionType::None);
}

TEST(LineSegment, checkForIntersection_overlapping_segments) {
	CB::LineSegment first({ -11.f,3.f }, { -5.f,0.f });
	CB::LineSegment second({ -7.f,1.f }, { -3.f,-1.f });
	auto intersection = first.checkForIntersection(second);
	
	ASSERT_EQ(intersection.type, CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	EXPECT_EQ(CB::LineSegment({ -7.f,1.f }, { -5.f, 0.f }), expected);
}

TEST(LineSegment, checkForIntersection_vertically_overlapping_segments) {
	CB::LineSegment first({ -5.f,-1.f }, { -5.f,2.f });
	CB::LineSegment second({ -5.f,0.f }, { -5.f,-4.f });
	auto intersection = first.checkForIntersection(second);

	ASSERT_EQ(intersection.type, CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	EXPECT_EQ(CB::LineSegment({ -5.f,-1.f }, { -5.f, 0.f }), expected);
}

TEST(LineSegment, checkForIntersection_horizontally_overlapping_segments) {
	CB::LineSegment first({ -1.f,-4.f }, { 3.f,-4.f });
	CB::LineSegment second({ 0.f,-4.f }, { 5.f,-4.f });
	auto intersection = first.checkForIntersection(second);

	ASSERT_EQ(intersection.type, CB::IntersectionType::Overlapping);
	auto pair = intersection.resultingSegment;
	CB::LineSegment expected(pair.first, pair.second);
	EXPECT_EQ(CB::LineSegment({ 0.f,-4.f }, { 3.f, -4.f }), expected);
}


TEST(LineSegment, YIntercept) {
	float slope = 0.5f;
	CB::vec_t point(10.f, 3.f);

	float expected = -2.f;

	EXPECT_EQ(CB::LineSegment::YIntercept(point, slope), expected);
}

TEST(LineSegment, YIntercept_infinite_slope) {
	CB::LineSegment verticalSegment({ 0.f,0.f }, { 0.f,1.f });

	CB::vec_t point = verticalSegment.start;
	
	constexpr float expected = std::numeric_limits<float>::infinity();

	EXPECT_EQ(CB::LineSegment::YIntercept(point, verticalSegment.slope()), expected);
}

TEST(LineSegment, assignment_operator) {
	CB::LineSegment segment;
	CB::LineSegment expected({ 0.f,1.f }, { 2.f,3.f });
	EXPECT_NE(segment, expected);
	segment = expected;
	EXPECT_EQ(segment, expected);
}

TEST(LineSegment, equality_operator) {
	CB::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	CB::LineSegment right({ 0.f,1.f }, { 2.f,3.f });

	EXPECT_EQ(left, right);

	CB::LineSegment other(left.end, left.start);

	EXPECT_EQ(other, right);
}

TEST(LineSegment, inequality_operator) {
	CB::LineSegment left({ 0.f,1.f }, { 2.f,3.f });
	CB::LineSegment right({ 0.f,2.f }, { 2.f,3.f });
	EXPECT_NE(left, right);
}