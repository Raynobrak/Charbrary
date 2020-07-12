#pragma once

#include "vector_type_definition.h"

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
		 * 
		 * \param position Position of the AABB.
		 * \param size_ Size of the AABB.
		 */
		AABB(const vec_t& position, const vec_t& size_);

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
		void move(const vec_t& movement);

		/**
		 * \brief Returns the center of the AABB.
		 * 
		 * \return The position of the AABB's center.
		 */
		vec_t center() const;

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
		vec_t corner(const Corner corner) const;

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
		bool contains(const vec_t& point) const;

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