#pragma once

#include "Vector.h"

#ifdef USE_SFML_VECTORS
#include <SFML/System/Vector2.hpp>
namespace ch {
	using vec_t = sf::Vector2f;
}
#else
namespace ch {
	using vec_t = ch::Vector;
}
#endif USE_SFML_VECTORS

#include "vector_maths_functions.h"
