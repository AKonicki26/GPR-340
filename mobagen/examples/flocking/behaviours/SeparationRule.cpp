#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  if (neighborhood.empty()) return Vector2f::zero();

  // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them

  Vector2f position = boid->transform.position;
  int countCloseFlockmates = 0;
  // todo: find and apply force only on the closest mates


  for (Boid* neightbor : neighborhood) {
    Vector2f seperationVector = neightbor->getPosition() - boid->getPosition();

    if (seperationVector.getMagnitude() <= desiredDistance && seperationVector.getMagnitude() > 0) {
      separatingForce += Vector2f::normalized(seperationVector) / seperationVector.getMagnitude();
    }
  }

  //separatingForce = Vector2f::normalized(separatingForce);

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
