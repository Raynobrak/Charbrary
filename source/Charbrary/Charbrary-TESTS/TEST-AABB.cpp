#pragma once

#include "pch.h"

#include "../Physics/AABB.h"
#include "../Physics/AABB.cpp"

TEST(AABB, ctor_vectors) {
	CB::AABB aabb(CB::vec_t(3.f, 5.f), CB::vec_t(9.f, -8.f));

	EXPECT_FLOAT_EQ(aabb.pos.x, 3.f);
	EXPECT_FLOAT_EQ(aabb.pos.y, 5.f);
	EXPECT_FLOAT_EQ(aabb.size.x, 9.f);
	EXPECT_FLOAT_EQ(aabb.size.y, -8.f);
}

TEST(AABB, ctor_floats) {
	CB::AABB aabb(3.f, 5.f, 9.f, -8.f);

	EXPECT_FLOAT_EQ(aabb.pos.x, 3.f);
	EXPECT_FLOAT_EQ(aabb.pos.y, 5.f);
	EXPECT_FLOAT_EQ(aabb.size.x, 9.f);
	EXPECT_FLOAT_EQ(aabb.size.y, -8.f);
}

TEST(AABB, ctor_default) {
	CB::AABB aabb;

	EXPECT_FLOAT_EQ(aabb.pos.x, 0.f);
	EXPECT_FLOAT_EQ(aabb.pos.y, 0.f);
	EXPECT_FLOAT_EQ(aabb.size.x, 0.f);
	EXPECT_FLOAT_EQ(aabb.size.y, 0.f);
}

TEST(AABB, move) {
	CB::AABB aabb(1.f, 8.f, 5.f, 5.f);

	aabb.move({ -7.f,2.f });

	CB::AABB expected(-6.f, 10.f, 5.f, 5.f);

	EXPECT_EQ(aabb, expected);
}

TEST(AABB, center) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(8.f, 15.f);

	EXPECT_EQ(aabb.center(), expected);
}

TEST(AABB, corner_tl) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(3.f, 5.f);

	EXPECT_EQ(aabb.corner(CB::Corner::TopLeft), expected);
}

TEST(AABB, corner_tr) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(13.f, 5.f);

	EXPECT_EQ(aabb.corner(CB::Corner::TopRight), expected);
}

TEST(AABB, corner_bl) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(3.f, 25.f);

	EXPECT_EQ(aabb.corner(CB::Corner::BottomLeft), expected);
}

TEST(AABB, corner_br) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(13.f, 25.f);

	EXPECT_EQ(aabb.corner(CB::Corner::BottomRight), expected);
}

TEST(AABB, corner_invalid) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);

	EXPECT_THROW(aabb.corner(static_cast<CB::Corner>(434923)), std::invalid_argument);
}

TEST(AABB, scaleRelativeToCenter) {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t centerPosBefore = aabb.center();
	CB::vec_t expectedSize(6.f, 12.f);

	aabb.scaleRelativeToCenter(0.6f);

	EXPECT_EQ(aabb.center(), centerPosBefore);
	EXPECT_EQ(aabb.size, expectedSize);
}

TEST(AABB, perimeter) {
	CB::AABB aabb(0.f, 0.f, 1.f, 3.f);
	float expected = 8.f;

	EXPECT_FLOAT_EQ(aabb.perimeter(), expected);
}

TEST(AABB, area) {
	CB::AABB aabb(0.f, 0.f, 2.f, 3.f);
	float expected = 6.f;

	EXPECT_FLOAT_EQ(aabb.area(), expected);
}

TEST(AABB, diagonalLength) {
	CB::AABB aabb(0.f, 0.f, 3.f, 4.f);
	float expected = 5.f;

	EXPECT_FLOAT_EQ(aabb.diagonalLength(), expected);
}

TEST(AABB, contains_true) {
	CB::AABB aabb(6.f, 7.f, 10.f, 20.f);
	CB::vec_t point(6.f, 26.f);

	EXPECT_TRUE(aabb.contains(point));
}

TEST(AABB, contains_false) {
	CB::AABB aabb(6.f, 7.f, 10.f, 20.f);
	CB::vec_t point(5.f, 14.f);

	EXPECT_FALSE(aabb.contains(point));
}

TEST(AABB, intersects_false) {
	CB::AABB first(6.f, 7.f, 10.f, 20.f);
	CB::AABB second(18.f, 10.f, 30.f, 40.f);

	EXPECT_FALSE(first.intersects(second));
	EXPECT_FALSE(second.intersects(first));
}

TEST(AABB, intersects_true_inside) {
	CB::AABB first(6.f, 4.f, 10.f, 5.f);
	CB::AABB second(7.f, 5.f, 5.f, 2.f);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(AABB, intersects_true_itself) {
	CB::AABB aabb(6.f, 4.f, 10.f, 5.f);

	EXPECT_TRUE(aabb.intersects(aabb));
}

TEST(AABB, intersects_true_cross) {
	CB::AABB first(6.f, 4.f, 10.f, 30.f);
	CB::AABB second(1.f, 10.f, 30.f, 10.f);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(AABB, strictlyContains_false) {
	CB::AABB first(6.f, 4.f, 10.f, 30.f);
	CB::AABB second(5.f, 6.f, 4.f, 3.f);

	EXPECT_FALSE(first.strictlyContains(second));
}

TEST(AABB, strictlyContains_true) {
	CB::AABB container(2.f, 3.f, 50.f, 20.f);
	CB::AABB contained(10.f, 10.f, 5.f, 5.f);

	EXPECT_TRUE(container.strictlyContains(contained));
	EXPECT_FALSE(contained.strictlyContains(container));
}

TEST(AABB, strictlyContains_true_itself) {
	CB::AABB aabb(6.f, 4.f, 10.f, 30.f);
	
	EXPECT_TRUE(aabb.strictlyContains(aabb));
}

TEST(AABB, assign_operator) {
	CB::AABB aabb(6.f, 4.f, 10.f, 30.f);
	CB::AABB expected(19.f, 25.f, 45.f, 898.f);
	aabb = expected;

	EXPECT_EQ(aabb, expected);
}

TEST(AABB, equality_operator) {
	CB::AABB first(1.f, 2.f, 3.f, 4.f);
	CB::AABB second(1.f, 2.f, 3.f, 4.f);

	EXPECT_EQ(first, second);
}

TEST(AABB, inequality_operator) {
	CB::AABB first(1.f, 2.f, 3.f, 4.f);
	CB::AABB second(4.f, 3.f, 2.f, 1.f);

	EXPECT_NE(first, second);
}


