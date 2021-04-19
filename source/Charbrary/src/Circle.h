#pragma once

#include "vector_type_definition.h"
#include "AABB.h"

namespace ch {

	/**
	 * \brief Represents a circle.
	 *
	 * This class contains member functions that perform common mathematical operations
	 * done with circles (computing the area, perimeter, circumference) and also to help
	 * dealing with collision detection.
	 * Circles are defined by a position (the center) and a radius.
	 */
	class Circle {

	public:

		vec_t pos; /**< The circle's center position. */

		float radius; /**< The circle's radius. */

	public:

		/**
		 * \brief Constructs a new circle with default values.
		 * 
		 * The new circle will be positioned at 0,0 and have a radius of 0.
		 */
		Circle();

		/**
		 * \brief Constructs a new Circle from a vector and a radius.
		 * \param position Position of the center of the circle.
		 * \param radius_ Radius of the circle.
		 */
		Circle(const vec_t& position_, float radius_);

		/**
		 * \brief Computes the diameter of the circle.
		 * \return The diameter (radius * 2).
		 */
		float diameter() const;

		/**
		 * \brief Computes the circumference of the circle.
		 * \note The value for PI that will be used is the one contained in Constants.h
		 * \return The circumference.
		 */
		float circumference() const;

		/**
		 * \brief Computes the area of the circle. 
		 * \note The value for PI that will be used is the one contained in Constants.h
		 * \return The area of the circle.
		 */
		float area() const;

		/**
		 * \brief Computes the smallest AABB that contains the current circle.
		 * \return An AABB able to contain the current circle.
		 */
		AABB enclosingAABB() const;

		/**
		* \brief Computes the distance to the given circle.
		* \return A positive value if the circles do not overlap and a negative value otherwise.
		*/
		float distanceTo(const Circle& other) const;

		/**
		 * \brief Checks if the given point is contained inside the current circle.
		 * \param point The position of the point.
		 * \return True if the point is inside the circle, false otherwise.
		 */
		bool contains(const vec_t& point) const;

		/**
		 * \brief Checks if the given circle intersects the current circle.
		 * \param other Another circle.
		 * \return True if the circles are overlapping, false otherwise.
		 */
		bool intersects(const Circle& other) const;

		/**
		 * \brief Checks if the given circle is entirely contained inside the current
		 * circle.
		 * \param other The potentially contained circle.
		 * \return True if the given circle is contained in the current circle.
		 */
		bool strictlyContains(const Circle& other) const;

		/**
		 * \brief Overload of the assignment operator.
		 * \param toCopy Circle whose values will be copied into the current circle. 
		 */
		void operator=(const Circle& toCopy);
	};

	/**
	 * \brief Overload of the equality operator between 2 circles.
	 * \return True if left is equal to right.
	 */
	bool operator==(const Circle& left, const Circle& right);

	/**
	 * \brief Overload of the inequality operator between 2 circles.
	 * \return True if left and right are different.
	 */
	bool operator!=(const Circle& left, const Circle& right);
}