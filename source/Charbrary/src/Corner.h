#pragma once

namespace ch {
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
	 * \brief Utility function to find the diagonal opposite of a corner.
	 *
	 * The diagonally opposed corner is the "opposite" of a given corner.
	 * Example : TopLeft is diagonally opposed to BottomRight and vice-versa.
	 *
	 * \returns The opposite of the given corner.
	 */
	constexpr Corner diagonally_opposed_corner(Corner corner);

	/**
	 * \brief Utility function to find the vertical opposite of a corner.
	 *
	 * Example : TopLeft is vertically opposed to BottomLeft and vice-versa.
	 *
	 * \returns The vertical opposite of the given corner.
	 */
	constexpr Corner vertically_opposed_corner(Corner corner);

	/**
	 * \brief Utility function to find the horizontal opposite of a corner.
	 *
	 * Example : TopLeft is horizontally opposed to TopRight and vice-versa.
	 *
	 * \returns The horizontal opposite of the given corner.
	 */
	constexpr Corner horizontally_opposed_corner(Corner corner);
}

