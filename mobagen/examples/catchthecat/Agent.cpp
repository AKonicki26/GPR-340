#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <functional>
using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  auto getVistableNeighbors = [&](World* world, Point2D point)  -> std::vector<Point2D> {
    std::vector<Point2D> validNeighbors;

    auto isValidNeighbor = [&](const Point2D& neighbor) -> bool {
      if (neighbor == catPos)
        return false;
      if (world->getContent(neighbor))
        return false;
      if (visited.find(neighbor) != visited.end() && visited.at(neighbor))
        return false;
      if (frontierSet.contains(neighbor))
        return false;
      if (!world->isValidPosition(neighbor))
        return false;

      // Return true only if everything else is false
      return true;
    };

    // Vector of all functions that return a neighbor relative to some point p
    std::vector<function<Point2D(Point2D)>> const neighborFunctions = { World::NE, World::NW, World::SE,
    World::SW, World::E, World::W};

    for (const auto& function : neighborFunctions) {
      if (isValidNeighbor(function(point)))
        validNeighbors.push_back(function(point));
    }

    return validNeighbors;
  };

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D const current = frontier.front();
    frontier.pop();
    // remove the current from frontierset
    frontierSet.erase(current);
    // mark current as visited
    visited[current] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> const neighbors = getVistableNeighbors(w, current);
    // iterate over the neighs:

    for (auto neighbor : neighbors) {
    // for every neighbor set the cameFrom
      cameFrom[neighbor] = current;

      // Neighbor exists on the border
      if (abs(neighbor.x) == w->getWorldSideSize() / 2 || abs(neighbor.y) == w->getWorldSideSize() / 2) {
        borderExit = neighbor;
        break;
      }
    // enqueue the neighbors to frontier and frontierset
      frontier.push(neighbor);
      frontierSet.insert(neighbor);
    }
    // do this up to find a visitable border and break the loop
  }

  std::vector<Point2D> path =  std::vector<Point2D>();
  // if the border is not infinity, build the path from border to the cat using the camefrom map
  if (borderExit != Point2D::INFINITE) {
    Point2D current = borderExit;
    do {
      path.push_back(current);
      current = cameFrom[current];
    } while (current != catPos);
  }

  // if there isn't a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}
