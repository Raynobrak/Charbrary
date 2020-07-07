#pragma once

// Uncomment the following line to use the vectors from the SFML library.
#define USE_SFML_VECTORS 1
#undef USE_SFML_VECTORS

#ifdef USE_SFML_VECTORS
#include <SFML/System/Vector2.hpp>
namespace CB {
	using vec_t = sf::Vector2f;
}
#else
#include "Vector.h"
namespace CB {
	using vec_t = CB::CBVEC;
}
#endif USE_SFML_VECTORS

#include "VectorMaths.h"
