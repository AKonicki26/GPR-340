//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world) {
  for (int x = 0; x <= world.SideSize(); x++) {
    for (int y = 0; y <= world.SideSize(); y++) {
      Point2D point = Point2D(x, y);
      int neightbors = CountNeighbors(world, point);

      // point is currently alive
      if (world.Get(point)) {
        if (neightbors < 2) {
          world.SetNext(point, false);
        } else if (neightbors < 4) {
          world.SetNext(point, true);
        } else {
          world.SetNext(point, false);
        }
        // point is currently dead
      } else {
        if (neightbors == 3) {
          world.SetNext(point, true);
        }
      }
    }
  }
}

int HexagonGameOfLife::CountNeighbors(World& world, Point2D point) {
  int neighborCount = 0;

  // Iterate through all neighbors of the point
  for (int x = point.x; x <= point.x + 1; x++) {
    for (int y = point.y - 1; y <= point.y + 1; y++) {
      Point2D potentialNeighbor = Point2D(x, y);

      // for middle row, check the one to the left of the point
      if (potentialNeighbor == point) {
        potentialNeighbor.x -= 1;
      }

      if (world.Get(potentialNeighbor)) neighborCount++;
    }
  }

  return neighborCount;
}
