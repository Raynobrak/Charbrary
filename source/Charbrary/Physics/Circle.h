/* Copyright 2019 Lucas Charbonnier

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include "vector_type_definition.h"
#include "AABB.h"

namespace CB {

	/**
	 * \brief Represents a circle.
	 * 
	 * This class contains methods that perform common operations that can be done with
	 * circles such as computing the diameter, the area, the circumference and also
	 * collision detection.
	 * Circles are defined by the position of their center (a vector) and their radius (a real number).
	 */
	class Circle {

	public:

		vec_t pos; /**< The circle's center position. */

		float radius; /**< The circle's radius. */

	public:

		/**
		 * \brief Constructs a new Circle with default values.
		 * 
		 * The new circle will be positioned at 0,0 and have a radius of 0.
		 */
		Circle();

		/**
		 * \brief Constructs a new Circle from a vector and a radius.
		 * \param position Position of the center of the circle.
		 * \param radius_ Radius of the circle.
		 */
		Circle(const vec_t& position, float radius_);

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
		 * 
		 * The computed AABB will be as small as possible and the Circle will be
		 * centered inside it.
		 * 
		 * \return A new AABB containing the current circle.
		 */
		AABB enclosingAABB() const;

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