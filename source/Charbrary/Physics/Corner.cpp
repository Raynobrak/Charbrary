#include "Corner.h"

#include <array>

namespace CB {
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
}