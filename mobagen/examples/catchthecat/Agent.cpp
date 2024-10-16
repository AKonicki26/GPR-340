#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"

#include <functional>

#define Weight unsigned int

template<typename T>
concept UnsignedDatatype = !std::is_signed_v<T>;

// struct for comparing the pairs for the priority queue
template<UnsignedDatatype T>
struct WeightCompare {
  bool operator()(const std::pair<Point2D, Weight>& first, const std::pair<Point2D, Weight>& second) {
    return first.second > second.second;
  }
};

using namespace std;
std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path

  priority_queue<std::pair<Point2D, Weight>, vector<std::pair<Point2D, Weight>>, WeightCompare<Weight>> frontier;

  //queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  unordered_map<Point2D, Weight> weights;

  // bootstrap state
  auto catPos = w->getCat();
  frontier.push(std::make_pair(catPos, 0));
  frontierSet.insert(catPos);
  weights[catPos] = 0;
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  auto getVistableNeighbors = [&](World* world, Point2D point)  -> std::vector<Point2D> {
    std::vector<Point2D> validNeighbors;

    auto isValidNeighbor = [&](const Point2D& neighbor) -> bool {
      if (neighbor == catPos)
        return false;
      if (world->getContent(neighbor))
        return false;
      if (visited.contains(neighbor))
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

  bool exitFound = false;

  while (!frontier.empty() && !exitFound) {
    // get the current from frontier
    std::pair<Point2D, Weight> const current = frontier.top();
    frontier.pop();
    // remove the current from frontierSet
    frontierSet.erase(current.first);
    if (visited.contains(current.first)) {
      continue;
    }

    const auto currentPoint = current.first;
    const auto currentWeight = current.second;

    // mark current as visited
    visited[currentPoint] = true;
    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    std::vector<Point2D> const neighbors = getVistableNeighbors(w, currentPoint);
    // iterate over the neighs:

    for (auto neighbor : neighbors) {
    // for every neighbor set the cameFrom
      cameFrom[neighbor] = currentPoint;

      // Neighbor exists on the border
      if (abs(neighbor.x) == w->getWorldSideSize() / 2 || abs(neighbor.y) == w->getWorldSideSize() / 2) {
        borderExit = neighbor;
        exitFound = true;
        break;
      }
    // enqueue the neighbors to frontier and frontierSet
      frontier.push(std::make_pair(neighbor, currentWeight + 1));
      frontierSet.insert(neighbor);
    }
    // do this up to find a visitable border and break the loop
  }

  std::vector<Point2D> path =  std::vector<Point2D>();
  // if the border is not infinity, build the path from border to the cat using the cameFrom map
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


