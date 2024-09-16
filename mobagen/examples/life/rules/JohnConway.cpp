#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  // todo: implement

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

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int neighborCount = 0;

  // Iterate through all neighbors of the point
  for (int x = point.x - 1; x <= point.x + 1; x++) {
    for (int y = point.y - 1; y <= point.y + 1; y++) {
      Point2D potentialNeighbor = Point2D(x, y);

      if (potentialNeighbor != point && world.Get(potentialNeighbor))
        neighborCount++;
    }
  }

  return neighborCount;
}
