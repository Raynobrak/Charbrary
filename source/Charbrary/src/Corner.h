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
	 * \brief Utility function to find the opposite of a corner.
	 *
	 * The diagonally opposed corner is the "opposite" of a given corner.
	 * Example : TopLeft is diagonally opposed to BottomRight and vice-versa.
	 *
	 * \returns The opposite of the given corner.
	 */
	constexpr Corner diagonally_opposed_corner(Corner corner);
}

