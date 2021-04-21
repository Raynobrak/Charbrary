#pragma once

#include "AABB.h"
#include "Circle.h"
#include "AABBCollision.h"
#include "CirclesCollision.h"
#include "CircleAABBCollision.h"

namespace ch {
	namespace collision {

		/** \return A circle that contains the given AABB. */
		Circle enclosingCircle(const AABB& aabb);

		/** \return A circle contained in the given AABB. */
		Circle inscribedCircle(const AABB& aabb);

		/** \return An AABB that contains the given circle. */
		AABB enclosingAABB(const Circle& circle);

		/** \return An AABB contained in the given circle. */
		AABB inscribedAABB(const Circle& circle);
			
		/** \returns True if the given point is inside the AABB, false otherwise. */
		bool aabb_contains(const AABB& aabb, const vec_t& point);

		/** \returns True if the first AABB contains the other AABB, false otherwise. */
		bool aabb_contains(const AABB& first, const AABB& other);

		/** \returns True if the AABB contains the circle, false otherwise. */
		bool aabb_contains(const AABB& aabb, const Circle& circle);


		/** \returns True if the circle contains the point, false otherwise. */
		bool circle_contains(const Circle& circle, const vec_t& point);

		/** \returns True if the first circle contains the other, false otherwise. */
		bool circle_contains(const Circle& first, const Circle& other);

		/** \returns True if the circle contains the AABB, false otherwise. */
		bool circle_contains(const Circle& circle, const AABB& aabb);


		/** \returns True if the given AABBs intersect, false otherwise. */
		bool aabb_intersects(const AABB& a, const AABB& b);

		/** \returns True if the AABB and the circle intersect, false otherwise. */
		bool aabb_intersects(const AABB& aabb, const Circle& circle);

		/** \returns True if the circles intersect, false otherwise. */
		bool circle_intersects(const Circle& circle, const Circle& other);

		/** \returns True if the Circle and the AABB intersect, false otherwise. */
		bool circle_intersects(const Circle& circle, const AABB& aabb);

		/** \returns The distance separating two circles (negative if overlapping) */
		float circles_distance(const Circle& a, const Circle& b);


		/**
		 * \brief Checks if the first AABB collides with the other one.
		 *
		 * In case of a collision, this function returns an instance of AABBCollision containing the collision normal and the delta (overlap).
		 * The collision normal is the direction (a unit vector) towards which the other AABB needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns An AABBCollision containing information about the collision.
		 */
		AABBCollision aabb_collision_info(const AABB& first, const AABB& other);

		/**
		 * \brief Checks if the first circle collides with the other one.
		 *
		 * In case of a collision, this function returns an instance of CirclesCollision containing the collision normal and the penetration depth.
		 * The collision normal is the direction (a unit vector) towards which the other circle needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns A CirclesCollision object containing information about the collision.
		 */
		CirclesCollision circles_collision_info(const Circle& first, const Circle& other);

		/**
		 * \brief Checks if an AABB and a circle collide with each other.
		 *
		 * In case of a collision, this function returns an instance of CircleAABBCollision containing the collision normal and the penetration depth.
		 * The collision normal is the direction (a unit vector) towards which the *circle* needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) if there is no collision.
		 *
		 * \returns A CircleAABBCollision object containing information about the collision.
		 */
		CircleAABBCollision circle_aabb_collision_info(const AABB& aabb, const Circle& circle);

		void ensureContainment(AABB& object, const AABB& container);
		void ensureContainment(Circle& object, const AABB& container);
	}
}

