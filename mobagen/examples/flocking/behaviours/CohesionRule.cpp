#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

#include <iostream>

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  if (!neighborhood.empty()) {
    Vector2f sumOfPositions = Vector2f::zero();

    // find center of mass
    for (Boid* neighbor : neighborhood)
      sumOfPositions += neighbor->getPosition();

    Vector2f centerOfMass = sumOfPositions / neighborhood.size();

    cohesionForce = (centerOfMass - boid->getPosition());
  }

  return cohesionForce;
}