#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
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

  auto getVistableNeighbors = [=](World* w, Point2D p)  -> std::vector<Point2D> {
    auto catPos = w->getCat();
    std::vector<Point2D> validNeighbors;

    auto isValidNeighbor = [=](Point2D neighbor) -> bool {
      return (neighbor != catPos &&
        !w->getContent(neighbor) &&
        w->isValidPosition(neighbor) &&
        !visited.contains(neighbor) &&
        !frontierSet.contains(neighbor)
        );

    };

    if (isValidNeighbor(World::NE(p)))
      validNeighbors.push_back(World::NE(p));
    if (isValidNeighbor(World::NW(p)))
      validNeighbors.push_back(World::NW(p));

    if (isValidNeighbor(World::SE(p)))
      validNeighbors.push_back(World::SE(p));
    if (isValidNeighbor(World::SW(p)))
      validNeighbors.push_back(World::SW(p));

    if (isValidNeighbor(World::E(p)))
      validNeighbors.push_back(World::E(p));
    if (isValidNeighbor(World::W(p)))
      validNeighbors.push_back(World::W(p));

    return validNeighbors;
  };

  while (!frontier.empty()) {
    // get the current from frontier
    Point2D current = frontier.front();
    frontier.pop();
    // remove the current from frontierset
    frontierSet.erase(current);
    // mark current as visited
    visited[current] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> neighbors = getVistableNeighbors(w, current);
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
    Point2D catPos, current;
    catPos = w->getCat();
    current = borderExit;
    do {
      path.push_back(current);
      current = cameFrom[current];
    } while (current != catPos);
  }

  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return path;
}
