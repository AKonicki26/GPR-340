#include "Cat.h"
#include "World.h"
#include <stdexcept>

Point2D Cat::Move(World* world) {

  auto pathToExit = generatePath(world);
  if (!pathToExit.empty()) {
    return pathToExit[pathToExit.size() - 1];
  }

  // When no exit, make random move
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  switch (rand) {
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
