#pragma once

#include "pch.h"

#include "../Physics/Circle.h"
#include "../Physics/Circle.cpp"

TEST(Circle, default_constructor) {
	CB::Circle circle;
	
	EXPECT_FLOAT_EQ(circle.pos.x, 0.f);
	EXPECT_FLOAT_EQ(circle.pos.y, 0.f);
	EXPECT_FLOAT_EQ(circle.radius, 0.f);
}

TEST(Circle, pos_radius_constructor) {
	CB::Circle circle({ 13.f, 49.f }, 42.5f);

	EXPECT_FLOAT_EQ(circle.pos.x, 13.f);
	EXPECT_FLOAT_EQ(circle.pos.y, 49.f);
	EXPECT_FLOAT_EQ(circle.radius, 42.5f);
}

TEST(Circle, diameter) {
	CB::Circle circle({ 0.f,0.f }, 4);
	EXPECT_FLOAT_EQ(circle.diameter(), 8.f);
}

TEST(Circle, circumference) {
	CB::Circle circle({ 0.f,0.f }, 7);
	EXPECT_FLOAT_EQ(circle.circumference(), 43.98229715f);
}

TEST(Circle, area) {
	CB::Circle circle({ 0.f,0.f }, 7);
	EXPECT_FLOAT_EQ(circle.area(), 153.9380400f);
}

TEST(Circle, enclosingAABB) {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::AABB expected(3.f, 1.f, 4.f, 4.f);
	EXPECT_EQ(circle.enclosingAABB(), expected);
}

TEST(Circle, contains_true) {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, 2.f);

	EXPECT_TRUE(circle.contains(point));
}

TEST(Circle, contains_false) {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, -5.f);

	EXPECT_FALSE(circle.contains(point));
}

TEST(Circle, intersects_true_center_inside) {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 6.f,2.f }, 1.f);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(Circle, intersects_true_center_outside) {
	CB::Circle first({ 5.f,3.f }, 3.f);
	CB::Circle second({ 10.f,3.f }, 3.f);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(Circle, intersects_false) {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 10.f,5.f }, 1.f);

	EXPECT_FALSE(first.intersects(second));
	EXPECT_FALSE(second.intersects(first));
}

TEST(Circle, intersects_overlapping) {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	EXPECT_TRUE(circle.intersects(circle));
}

TEST(Circle, strictlyContains_true) {
	CB::Circle container({ 5.f,3.f }, 2.f);
	CB::Circle contained({ 6.f,3.f }, 0.5f);
	EXPECT_TRUE(container.strictlyContains(contained));
	EXPECT_FALSE(contained.strictlyContains(container));
}

TEST(Circle, strictlyContains_false) {
	CB::Circle container({ 5.f,3.f }, 2.f);
	CB::Circle contained({ 6.f,3.f }, 2.f);
	EXPECT_FALSE(container.strictlyContains(contained));
	EXPECT_FALSE(contained.strictlyContains(container));
}


TEST(Circle, strictlyContains_overlapping) {
	CB::Circle container({ 5.f,3.f }, 2.f);
	EXPECT_TRUE(container.strictlyContains(container));
}

TEST(Circle, assign_operator) {
	CB::Circle c({ 1.f,1.f }, 1.f);
	CB::Circle expected({ 434.f,4622.f }, 398523.f);
	c = expected;
	EXPECT_EQ(c, expected);
}

TEST(Circle, equality_operator) {
	CB::Circle left({ 1.f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	EXPECT_EQ(left, right);
}

TEST(Circle, inequality_operator) {
	CB::Circle left({ 1.2f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	EXPECT_NE(left, right);
}