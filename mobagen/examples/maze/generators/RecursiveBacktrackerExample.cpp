#include "../World.h"
#include "Random.h"
#include "AKRandom.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <algorithm>

#define FINISHED_COLOR Color::Black
#define UNTOUCHED_COLOR Color::DarkGray
#define STACK_COLOR Color::LightCyan

bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  // If we don't have a starting point, make one

  auto visit = [this, w](Point2D source, Point2D neighbor) -> void {
    auto difference = neighbor - source;

    Node sourceNode = w->GetNode(source);
    Node neighborNode = w->GetNode(neighbor);

    // p is to the east of source
    if (difference == Point2D::LEFT) {
      sourceNode.SetWest(false);
      neighborNode.SetEast(false);
    }
    // p is to the north of source
    else if (difference == Point2D::UP) {
      sourceNode.SetNorth(false);
      neighborNode.SetSouth(false);
    }
    // west
    else if (difference == Point2D::RIGHT) {

      sourceNode.SetEast(false);
      neighborNode.SetWest(false);
    }
    // south
    else if (difference == Point2D::DOWN) {
      sourceNode.SetSouth(false);
      neighborNode.SetNorth(false);
    }

    w->SetNode(source, sourceNode);
    w->SetNode(neighbor, neighborNode);

    stack.push_back(neighbor);
    w->SetNodeColor(neighbor, STACK_COLOR);
  };

  if (stack.empty()) {
    //auto startPoint = randomStartPoint(w); // Start in "random" (always top right)
    auto startPoint = Point2D(0, 0); // Start in center

    if (w->GetNodeColor(startPoint) == FINISHED_COLOR)
      return false;
    stack.push_back(startPoint);
    w->SetNodeColor(startPoint, STACK_COLOR);
    return true;
  }

  auto point = stack[stack.size() - 1];

  auto visitables = getVisitables(w, point);

  // There are neighbors
  if (!visitables.empty()) {
    Random rand = Random();

    int index = rand.Range(0, visitables.size() - 1);
    visit(point, visitables[index]);
    return true;
  }

  // There are no neighbors
  stack.pop_back();
  w->SetNodeColor(point, FINISHED_COLOR);




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

  auto getPointVisited = [=](Point2D p) -> bool { return w->GetNodeColor(p) != UNTOUCHED_COLOR; };

  auto getPointInWorld = [](Point2D p, int worldSizeOver2) -> bool {
    if (p.x > worldSizeOver2) return false;
    if (p.x < -worldSizeOver2) return false;
    if (p.y > worldSizeOver2) return false;
    if (p.y < -worldSizeOver2) return false;
    return true;
  };

  Point2D westPoint = Point2D(p.x - 1, p.y);
  Point2D eastPoint = Point2D(p.x + 1, p.y);
  Point2D northPoint = Point2D(p.x, p.y + 1);
  Point2D southPoint = Point2D(p.x, p.y - 1);

  // X Axis
  if (!getPointInStack(westPoint) &&
    !getPointVisited(westPoint) &&
    getPointInWorld(westPoint, w->GetSize() / 2)
    ) {

    visitables.push_back(westPoint);
  }
  if (!getPointInStack(eastPoint) &&
    !getPointVisited(eastPoint) &&
    getPointInWorld(eastPoint, w->GetSize() / 2)) {

    visitables.push_back(eastPoint);
  }
  // Y Axis
  if (!getPointInStack(northPoint) &&
    !getPointVisited(northPoint) &&
    getPointInWorld(eastPoint, w->GetSize() / 2)) {

    visitables.push_back(northPoint);
  }
  if (!getPointInStack(southPoint) &&
    !getPointVisited(southPoint) &&
    getPointInWorld(eastPoint, w->GetSize() / 2)) {

    visitables.push_back(southPoint);
  }

  return visitables;
}
