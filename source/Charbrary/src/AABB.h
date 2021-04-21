#pragma once

#include "vector_type_definition.h"
#include "AABBCollision.h"
#include "Corner.h"
#include "Circle.h"

#include <array>

namespace ch {

	/**
	 * \brief Represents an Axis-Aligned-Bounding-Box
	 * 
	 * An AABB is a rectangle that cannot rotate.
	 * 
	 * Since AABBs are commonly used to represent hitboxes, this class 
	 * contains a few functions to help dealing with collision detection.
	 */
	class AABB {

	public:

		vec_t pos; /**< Position of the top-left corner of the AABB. */

		vec_t size; /**< Size of the AABB. X for the width and Y for the height. */

	public:

		/**
		 * \brief Constructs a new AABB with default values.
		 * 
		 * By default, the AABB is positioned at 0,0 and has a size of 0,0.
		 */
		AABB();

		/**
		 * \brief Constructs a new AABB from 2 vectors.
		 * \param pos_ Position of the AABB.
		 * \param size_ Size of the AABB.
		 */
		AABB(const vec_t& pos_, const vec_t& size_);

		/**
		 * \brief Constructs a new AABB from 4 values.
		 * 
		 * \param x Top left corner position on the X axis.
		 * \param y Top left corner position on the Y axis.
		 * \param w Width of the AABB.
		 * \param h Height of the AABB.
		 *
		 * Good alternative if you want to build an AABB without creating temporary vectors.
		 */
		AABB(float x, float y, float w, float h);

		/**
		 * \brief Moves the AABB by the given movement vector.
		 * \param movement Vector representing the displacement.
		 */
		void move(const vec_t& movement);

		/**
		 * \brief Returns the center of the AABB.
		 * \return The Position of the AABB's center.
		 */
		vec_t center() const;

		/**
		 * \brief Computes the position of a corner of the AABB.
		 * 
		 * Returns the position of the specified corner (see enum Corner).
		 * 
		 * \return The position of the specified corner.
		 */
		vec_t corner(Corner corner) const;

		/**
		 * \brief Computes the position of every corner of the AABB.
		 * 
		 * The returned std::array is ordered in the order as the Corner enum.
		 * 
		 * \return An array containing all 4 corners of the AABB.
		 */
		std::array<vec_t, static_cast<size_t>(Corner::MAX_VALUE)> corners() const;

		/**
		 * \brief Scales the AABB's size while keeping it centered.
		 * 
		 * Scales the AABB's size by the given factor without moving it's center.
		 *
		 * \param factor Factor by which the size will be multiplied. Ex. A factor of 2 will double the width and height.
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
		 * \brief Computes the AABB's diagonal length.
		 * \return Length of the diagonal.
		 */
		float diagonalLength() const;
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