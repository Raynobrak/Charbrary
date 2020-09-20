#pragma once

#include "vector_type_definition.h"
#include "AABBCollision.h"

namespace CB {
	/**
	 * \brief Represents an AABB's corner.
	 */
	enum class Corner {
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		MAX_VALUE
	};

	/**
	 * \brief Utility function to find the opposite of a corner.
	 *
	 * The diagonally opposed corner is the "opposite" of a given corner.
	 * Example : TopLeft is diagonally opposed to BottomRight and vice-versa.
	 *
	 * \returns The opposite of the given corner.
	 */
	constexpr Corner diagonally_opposed_corner(Corner corner);
}

namespace CB {

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

		/**
		 * \brief Checks if the given point is inside the AABB.
		 * \param point The position of the point as a Vector.
		 * \return True if the point is contained in the AABB, false otherwise.
		 */
		bool contains(const vec_t& point) const;

		/**
		 * \brief Checks if the given AABB intersects the current AABB.
		 * \param other AABB to check the collision with.
		 * \return True if other intersects the current AABB, false otherwise.
		 */
		bool intersects(const AABB& other) const;

		/**
		 * \brief Checks if the given AABB is entirely contained in the current AABB.
		 * \param other AABB which is potentially contained inside the current AABB.
		 * \return True if other is strictly contained inside the current AABB, false otherwise.
		 */
		bool strictlyContains(const AABB& other) const;

		/**
		 * \brief Checks if the given AABB collides the current AABB.
		 * 
		 * In case of a collision, this function returns an instance of AABBCollision containing the collision normal and the delta (overlap).
		 * The collision normal is the direction (a unit vector) towards which the colliding AABB needs to be pushed in order to resolve the collision.
		 * The collision normal will be set to a null vector (0,0) in case there is no collision.
		 * 
		 * \returns An AABBCollision containing information about the collision.
		 */
		AABBCollision detectCollision(const AABB& other) const;
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