# Charbrary
A SFML-compatible C++ library for vector math and collision detection in 2D.

Key features of the Charbrary :
- **Vector math** in **2D** (basic stuff like computing magnitude, normalizing vectors, converting to polar coordinates, etc...)
- **Collision detection** of simple 2D shapes (AABBs, circles and line segments)
- **Simple installation** (available as a *single-include*).
- **SFML** Compatiblity

There are plenty of other vector math/physics libraries out there that do much more than the Charbrary ever will.<br>
It's a fun side project I enjoy working on.


If you happen to use the Charbrary in one of your project one day, let me know ! I'd be curious to see the result.

# How to "install" the Charbrary

The Charbrary is available as a **single-include**.


If you're not familiar with the concept, it means that the library is not pre-built (in the form of **.lib**s or **.dll**s). Instead, you add the entire source of the library to your project and compile it at the same time as the rest of your project.

In order to make it easier for you (so you don't have to download every single code files), the entire library is "concatenated" into 2 files.


Basically, you just need to add **charbrary.cpp** to your project and *#include* "**charbrary.h**" in the files where you will need it.

These **2 files** can be found in the "*single-include/*" folder at the root of the repository, along with the python script that is used to generate them.

## Generating the single-include files
1. I use **quom** (https://github.com/Viatorus/quom) to generate a **.hpp** header which contains the entire library.
2. To prevent redefinition errors (when including the .hpp in a project), I split it in two to separate the **declaration** (.h) from the **implementation** (.cpp).<br>
This step is done using a python script I wrote.


# SFML Compatibility
The vector type used within the Chabrary can be set to ```sf::Vector2f``` (SFML's vector type) by uncommenting the following line in your copy of *charbrary.h* :<br>
*```// #define USE_SFML_VECTORS 1```*
<br>
This is optional, though. The Charbrary still has its own built-in Vector type and works perfectly even without SFML.

# Tests
The test project can be found in the root folder "*tests/*". The test are written with the library catch2 (https://github.com/catchorg/Catch2).

# Documentation
The documentation can be found in the *doc/html* folder. Simply open *index.html* in your browser to view the start page.
The documentation is generated using Doxygen (https://github.com/doxygen/doxygen).

# Releases version names
Charbrary releases are named according to Semantic Versioning 2.0.0 (https://semver.org/)
