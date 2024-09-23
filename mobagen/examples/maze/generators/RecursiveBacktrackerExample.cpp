#include "../World.h"
#include "Random.h"
#include "AKRandom.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <algorithm>

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  Point2D point = randomStartPoint(w);

  getVisitables(w, point);
  stack.push_back(point);

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

  auto getPointInStack = [this](Point2D p) -> bool {
    return std::find(stack.begin(), stack.end(), p) != stack.end();
  };

  auto getPointVisited = [=](Point2D p) -> bool {
    return w->GetNodeColor(p) == Color::DarkGray;
  };

  SDL_Log("Is the point in the stack? %d\n", getPointInStack(p) ? "true" : "false");

  if (w->GetSouth(p)) {
    SDL_Log("Hi");
  }

  Point2D westPoint = Point2D(p.x - 1, p.y);
  Point2D eastPoint = Point2D(p.x + 1, p.y);
  Point2D northPoint = Point2D(p.x, p.y + 1);
  Point2D southPoint = Point2D(p.x, p.y - 1);


  // X Axis
  if (p.x != -sideOver2 && !getPointInStack(westPoint) && !getPointVisited(westPoint)) {
    visitables.push_back(Point2D(p.x - 1, p.y));
  }
  if (p.x == sideOver2 && !w->GetEast(p)) {
    visitables.push_back(Point2D(p.x + 1, p.y));
  }
  // Y Axis
  if (p.y == -sideOver2 && !w->GetNorth(p)) {
    visitables.push_back(Point2D(p.x, p.y - 1));
  }
  if (p.y == sideOver2 && !w->GetSouth(p)) {
    visitables.push_back(Point2D(p.x, p.y + 1));
  }

  return visitables;
}
