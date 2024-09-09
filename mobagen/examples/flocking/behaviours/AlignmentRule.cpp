#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  if (neighborhood.empty()) return averageVelocity;

  // hint: iterate over the neighborhood

  // get average velocity
  for (Boid* neighbor : neighborhood)
    averageVelocity += neighbor->getVelocity();
  averageVelocity /= neighborhood.size();

  return Vector2f::normalized(averageVelocity);
}