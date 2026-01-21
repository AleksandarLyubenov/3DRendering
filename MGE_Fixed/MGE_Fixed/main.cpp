#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"

// Week 2 Scenes
#include "MediocreWeek2.hpp"
#include "AverageWeek2.hpp"
#include "GoodWeek2.hpp"
#include "ExcellentWeek2.hpp"

// Week 3 Scenes
#include "MediocreWeek3.hpp" // Also includes the 'Good' requirement
#include "GoodWeek3.hpp"

// Week 4 Scenes
#include "MediocreWeek4.hpp"
#include "AverageWeek4.hpp"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files if possible.
 *
 */
int main()
{
    std::cout << "Starting Game" << std::endl;

    AbstractGame* game = new MediocreWeek3();
    game->initialize();
    game->run();

	delete game;

    return 0;
}



