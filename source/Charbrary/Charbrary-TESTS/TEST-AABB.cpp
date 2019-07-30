#pragma once

#include "pch.h"

#include "../Physics/AABB.h"
#include "../Physics/AABB.cpp"

TEST(AABB, ctor_vectors) {
	CB::AABB aabb(CB::Vector(3, 5), CB::Vector(9, -8));

	EXPECT_TRUE(aabb.pos.x == 3 && aabb.pos.y == 5 && aabb.size.x == 9 && aabb.size.y == -8);
}

TEST(AABB, ctor_floats) {
	CB::AABB aabb(3, 5, 9, -8);

	EXPECT_TRUE(aabb.pos.x == 3 && aabb.pos.y == 5 && aabb.size.x == 9 && aabb.size.y == -8);
}

TEST(AABB, ctor_default) {
	CB::AABB aabb;

	EXPECT_TRUE(aabb.pos.x == 0 && aabb.pos.y == 0 && aabb.size.x == 0 && aabb.size.y == 0);
}

TEST(AABB, move) {
	CB::AABB aabb(1, 8, 5, 5);

	aabb.move({ -7,2 });

	CB::AABB expected(-6, 10, 5, 5);

	EXPECT_EQ(aabb, expected);
}

TEST(AABB, center) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector expected(8, 15);

	EXPECT_EQ(aabb.center(), expected);
}

TEST(AABB, corner_tl) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector expected(3, 5);

	EXPECT_EQ(aabb.corner(CB::Corner::TopLeft), expected);
}

TEST(AABB, corner_tr) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector expected(13, 5);

	EXPECT_EQ(aabb.corner(CB::Corner::TopRight), expected);
}

TEST(AABB, corner_bl) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector expected(3, 25);

	EXPECT_EQ(aabb.corner(CB::Corner::BottomLeft), expected);
}

TEST(AABB, corner_br) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector expected(13, 25);

	EXPECT_EQ(aabb.corner(CB::Corner::BottomRight), expected);
}

TEST(AABB, corner_invalid) {
	CB::AABB aabb(3, 5, 10, 20);

	EXPECT_THROW(aabb.corner(static_cast<CB::Corner>(434923)), std::invalid_argument);
}

TEST(AABB, scaleRelativeToCenter) {
	CB::AABB aabb(3, 5, 10, 20);
	CB::Vector centerPosBefore = aabb.center();
	CB::Vector expectedSize(6, 12);

	aabb.scaleRelativeToCenter(0.6f);

	EXPECT_EQ(aabb.center(), centerPosBefore);
	EXPECT_EQ(aabb.size, expectedSize);
}

TEST(AABB, perimeter) {
	CB::AABB aabb(0, 0, 1, 3);
	float expected = 8;

	EXPECT_EQ(aabb.perimeter(), expected);
}

TEST(AABB, area) {
	CB::AABB aabb(0, 0, 2, 3);
	float expected = 6;

	EXPECT_EQ(aabb.area(), expected);
}

TEST(AABB, diagonalLength) {
	CB::AABB aabb(0, 0, 3, 4);
	float expected = 5;

	EXPECT_EQ(aabb.diagonalLength(), expected);
}

TEST(AABB, contains_true) {
	CB::AABB aabb(6, 7, 10, 20);
	CB::Vector point(6, 26);

	EXPECT_TRUE(aabb.contains(point));
}

TEST(AABB, contains_false) {
	CB::AABB aabb(6, 7, 10, 20);
	CB::Vector point(5, 14);

	EXPECT_FALSE(aabb.contains(point));
}

TEST(AABB, intersects_false) {
	CB::AABB first(6, 7, 10, 20);
	CB::AABB second(18, 10, 30, 40);

	EXPECT_FALSE(first.intersects(second));
	EXPECT_FALSE(second.intersects(first));
}

TEST(AABB, intersects_true_inside) {
	CB::AABB first(6, 4, 10, 5);
	CB::AABB second(7, 5, 5, 2);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(AABB, intersects_true_itself) {
	CB::AABB aabb(6, 4, 10, 5);

	EXPECT_TRUE(aabb.intersects(aabb));
}

TEST(AABB, intersects_true_cross) {
	CB::AABB first(6, 4, 10, 30);
	CB::AABB second(1, 10, 30, 10);

	EXPECT_TRUE(first.intersects(second));
	EXPECT_TRUE(second.intersects(first));
}

TEST(AABB, strictlyContains_false) {
	CB::AABB first(6, 4, 10, 30);
	CB::AABB second(5, 6, 4, 3);

	EXPECT_FALSE(first.strictlyContains(second));
}

TEST(AABB, strictlyContains_true) {
	CB::AABB container(2, 3, 50, 20);
	CB::AABB contained(10, 10, 5, 5);

	EXPECT_TRUE(container.strictlyContains(contained));
	EXPECT_FALSE(contained.strictlyContains(container));
}

TEST(AABB, strictlyContains_true_itself) {
	CB::AABB aabb(6, 4, 10, 30);
	
	EXPECT_TRUE(aabb.strictlyContains(aabb));
}

TEST(AABB, assign_operator) {
	CB::AABB aabb(6, 4, 10, 30);
	CB::AABB expected(19, 25, 45, 898);
	aabb = expected;

	EXPECT_EQ(aabb, expected);
}

TEST(AABB, equality_operator) {
	CB::AABB first(1, 2, 3, 4);
	CB::AABB second(1, 2, 3, 4);

	EXPECT_EQ(first, second);
}

TEST(AABB, inequality_operator) {
	CB::AABB first(1, 2, 3, 4);
	CB::AABB second(4, 3, 2, 1);

	EXPECT_NE(first, second);
}


