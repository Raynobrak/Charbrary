# Charbrary
The Charbrary is a C++ library made for :
- Vector math in 2D (basic stuff like computing magnitude, normalizing vectors, converting to polar coordinates, etc...)
- Collision detection of simple 2D shapes (AABBs, circles and line segments)
- Simple installation.

There are plenty of other vector math/physics libraries out there that do much more than the Charbrary ever will. The Charbrary is not a huge library, it's a small personnal project but it is simple to use and it *works* (close to 100% of every method/function/class is tested via unit tests). 

# Documentation
The documentation can be found in the *doc/html* folder. Simply open *index.html* in your browser to view the start page.
The documentation is generated using Doxygen (https://github.com/doxygen/doxygen).

# How do I link the Charbrary to my project ?
You don't.

To use the Charbrary, you simply need to add the **charbrary.cpp** file to your project and *#include* "**charbrary.h**" where you need it.

How do I generate these files ?
1. I use quom (https://github.com/Viatorus/quom) to generate a single-include file which contains the entire library.
2. To prevent redefinition errors, I split the single-include file in two to separate the **declaration** (.h) from the **implementation** (.cpp).

# Releases version names
Charbrary releases are named according to Semantic Versioning 2.0.0 (https://semver.org/)
