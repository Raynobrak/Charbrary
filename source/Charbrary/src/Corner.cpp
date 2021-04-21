#include "Corner.h"

#include <array>

namespace ch {
	constexpr Corner diagonally_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> DIAGONALLY_OPPOSED_CORNERS =
		{
			Corner::BottomRight,
			Corner::BottomLeft,
			Corner::TopRight,
			Corner::TopLeft
		};
		return DIAGONALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}

	constexpr Corner vertically_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> VERTICALLY_OPPOSED_CORNERS =
		{
			Corner::BottomLeft,
			Corner::BottomRight,
			Corner::TopLeft,
			Corner::TopRight
		};
		return VERTICALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}

	constexpr Corner horizontally_opposed_corner(Corner corner) {
		constexpr std::array<Corner, static_cast<size_t>(Corner::MAX_VALUE)> HORIZONTALLY_OPPOSED_CORNERS =
		{
			vertically_opposed_corner(diagonally_opposed_corner(Corner::TopLeft)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::TopRight)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::BottomLeft)),
			vertically_opposed_corner(diagonally_opposed_corner(Corner::BottomRight))
		};
		return HORIZONTALLY_OPPOSED_CORNERS[static_cast<size_t>(corner)];
	}
}