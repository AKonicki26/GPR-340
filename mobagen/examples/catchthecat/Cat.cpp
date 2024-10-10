#include "Cat.h"
#include "World.h"

#include <functional>
#include <stdexcept>

Point2D Cat::Move(World* world) {

  auto pathToExit = generatePath(world);
  if (!pathToExit.empty()) {
    return pathToExit[pathToExit.size() - 1];
  }

  // When no exit, make random move

  // Vector of all functions that return a neighbor relative to some point p
  std::vector<std::function<Point2D(Point2D)>> const neighborFunctions = { World::NE, World::NW, World::SE,
  World::SW, World::E, World::W};
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  return neighborFunctions[rand](pos);
}
