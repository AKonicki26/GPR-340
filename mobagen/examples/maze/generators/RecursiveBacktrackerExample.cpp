#include "../World.h"
#include "Random.h"
#include "AKRandom.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <algorithm>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  // If we don't have a starting point, make one
  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));
  }

  auto point = stack[stack.size() - 1];

  getVisitables(w, point);

  return true;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  /// If a point is on the edge, it cannot have a neighbor on that side
  /// So dont bother checking that edge
  /// If not on the edge, check for the neighbor

  auto getPointInStack = [this](Point2D p) -> bool { return std::find(stack.begin(), stack.end(), p) != stack.end(); };

  auto getPointVisited = [=](Point2D p) -> bool { return w->GetNodeColor(p) != Color::DarkGray; };

  SDL_Log((std::string("Is the point in the stack? ") + (getPointInStack(p) ? "true" : "false")).c_str());

  Point2D westPoint = Point2D(p.x - 1, p.y);
  Point2D eastPoint = Point2D(p.x + 1, p.y);
  Point2D northPoint = Point2D(p.x, p.y + 1);
  Point2D southPoint = Point2D(p.x, p.y - 1);

  // X Axis
  if (!getPointInStack(westPoint) && !getPointVisited(westPoint)) {
    visitables.push_back(westPoint);
  }
  if (!getPointInStack(eastPoint) && !getPointVisited(eastPoint)) {
    visitables.push_back(eastPoint);
  }
  // Y Axis
  if (!getPointInStack(northPoint) && !getPointVisited(northPoint)) {
    visitables.push_back(northPoint);
  }
  if (!getPointInStack(southPoint) && !getPointVisited(southPoint)) {
    visitables.push_back(southPoint);
  }

  return visitables;
}
