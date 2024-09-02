#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();

  float desiredDistance = desiredMinimalDistance;

  if (neighborhood.empty()) return Vector2f::zero();

  const float MAX_SEPERATION_FORCE = 100;

  for (Boid* neighbor : neighborhood) {
    Vector2f separationVector = boid->getPosition() - neighbor->getPosition();
    float separationVectorMagnitude = separationVector.getMagnitude();

    // Only apply force if inner radius
    if (separationVectorMagnitude <= desiredDistance) {
      // Prevent dividing by 0
      if (separationVectorMagnitude <= 0) separationVectorMagnitude = 0.0001;

      separatingForce += (separationVector.normalized() / separationVectorMagnitude)
          //* (std::pow(separationVectorMagnitude, 1.05)) // Small boost to make separation more powerful
          ;
    }
  }

  if (separatingForce.getMagnitude() > MAX_SEPERATION_FORCE) separatingForce = separatingForce.normalized() * MAX_SEPERATION_FORCE;

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
