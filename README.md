# Charbrary
The Charbrary is a C++ library made for :
- Vector mathematics in 2D (basic stuff like computing magnitude, normalizing vectors, polar coordinates, etc...)
- Collision detection in 2D (AABBs, circles and line segments)
- Simple usage. A single-include .hpp is available.

There are plenty of other vector math/physics libraries out there that do much more than the Charbrary ever will. The Charbrary is not a huge library, but it is simple-to-use and it works. I can assure you of that because the code is entirely tested; Almost every function from every class/namespace has one or more unit tests written for it.
I've created the Charbrary mainly for myself and thought it would be interesting to make it a public repository if people are curious.

# Documentation
The documentation can be found in the doc/ folder. Simply open *index.html* in your browser to view the start page.
The documentation is generated using Doxygen (https://github.com/doxygen/doxygen).

# How do I link the Charbrary to my project ?
You don't.
Ever heard of a *single-include* ? If not, you can probably guess what it is by the name of it :)
In order to use the charbrary in your code, you *#include* a single header file called "charbrary-single_include.hpp" and... that's it.

The single-include header is generated using https://github.com/Viatorus/quom. It's very simple to use and does the job.

# Releases version names
Charbrary releases are named according to Semantic Versioning 2.0.0 (https://semver.org/)
