#include "PrimExample.h"
#include "../World.h"
#include "Random.h"
#include "AKRandom.h"

bool PrimExample::Step(World* w) {
  int sideOver2 = w->GetSize() / 2;

  // todo: code this

  return true;
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;

  // todo: code this

  return visitables;
}

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  // todo: code this

  return neighbors;
}
