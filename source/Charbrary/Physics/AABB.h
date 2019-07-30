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

#include "Vector.h"

namespace CB {

	/**
	 * \brief Represents an AABB's corner.
	 */
	enum class Corner {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight
	};

	/**
	 * \brief Represents an Axis-Aligned-Bounding-Box
	 * 
	 * An AABB is a rectangle whose sides are aligned with the axis of the world in
	 * which it is defined.
	 * It's a rectangle that cannot rotate.
	 * 
	 * AABBs are commonly used to represent hitboxes. This class contains member
	 * functions that allow simple collision detection between AABBs.
	 */
	class AABB {

	public:

		Vector pos; /**< Position of the top-left corner of the AABB. */

		Vector size; /**< Size of the AABB. X for the width and Y for the height. */

	public:

		/**
		 * \brief Constructs a new AABB with default values.
		 * 
		 * By default, the AABB is positioned at 0,0 and has a size of 0,0.
		 */
		AABB();

		/**
		 * \brief Constructs a new AABB from 2 vectors.
		 * 
		 * \param position Position of the AABB.
		 * \param size_ Size of the AABB.
		 */
		AABB(const Vector& position, const Vector& size_);

		/**
		 * \brief Constructs a new AABB from 4 values.
		 * 
		 * \param left Distance from the AABB to the vertical axis.
		 * \param top Distance from the AABB to the horizontal axis.
		 * \param width Width of the AABB.
		 * \param height Height of the AABB.
		 */
		AABB(float left, float top, float width, float height);

		/**
		 * \brief Moves the AABB by the given movement.
		 *
		 * \param movement Vector representing the displacement.
		 */
		void move(const Vector& movement);

		/**
		 * \brief Returns the center of the AABB.
		 * 
		 * \return The position of the AABB's center.
		 */
		Vector center() const;

		/**
		 * \brief Computes the position of a single corner of the AABB.
		 * 
		 * Returns the position of one of the AABB's corner depending on the given enum
		 * value (see Corner).
		 * 
		 * \param corner Desired corner position.
		 * 
		 * \return The position of the specified corner.
		 */
		Vector corner(const Corner corner) const;

		/**
		 * \brief Scales the AABB's size.
		 * 
		 * Scales the AABB's size by the given factor while keeping the same center
		 * for the AABB. 
		 * This method will also modify the position of the AABB (pos).
		 */
		void scaleRelativeToCenter(float factor);

		/**
		 * \brief Computes the perimeter of the AABB.
		 * \return The perimeter of the AABB.
		 */
		float perimeter() const;

		/**
		 * \brief Computes the area of the AABB.
		 * \return The area of the AABB.
		 */
		float area() const;

		/**
		 * \brief Computes the length of any of the AABB's diagonals.
		 * \return Length of the diagonal.
		 */
		float diagonalLength() const;

		/**
		 * \brief Checks if the given point is inside the AABB.
		 * \param point The position of the point as a Vector.
		 * \return True if the point is contained in the AABB, false otherwise.
		 */
		bool contains(const Vector& point) const;

		/**
		 * \brief Checks if the given AABB intersects the current AABB.
		 * \param other AABB which is potentially overlapping with the current AABB.
		 * \return True if other intersects the current AABB, false otherwise.
		 */
		bool intersects(const AABB& other) const;

		/**
		 * \brief Checks if the given AABB is entirely contained in the current AABB.
		 * \param other AABB which is potentially contained inside the current AABB.
		 * \return True if other is contained inside the current AABB, false otherwise.
		 */
		bool strictlyContains(const AABB& other) const;
	};

	/**
	 * \brief Overload of the equality operator.
	 * \return True if left and right are equal, false otherwise.
	 */
	bool operator==(const AABB& left, const AABB& right);

	/**
	 * \brief Overload of the inequality operator.
	 * \return True if left and right are different, false otherwise.
	 */
	bool operator!=(const AABB& left, const AABB& right);
}