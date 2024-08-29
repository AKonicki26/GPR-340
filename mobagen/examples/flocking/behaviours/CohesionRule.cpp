#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

#include <iostream>

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood

  // find center of mass

  Vector2f sumOfPositions;

  for (Boid* neighbor : neighborhood)
    sumOfPositions += neighbor->getPosition();

  Vector2f centerOfMass = sumOfPositions / neighborhood.size();

  cohesionForce = (centerOfMass - boid->getPosition()) / boid->getDetectionRadius();

  return cohesionForce;
}