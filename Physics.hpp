#pragma once
#include "Ball.hpp"
#include "Duster.h"

#include <vector>

class Physics {
  public:
    Physics(double timePerTick = 0.001);
    void setWorldBox(const Point& topLeft, const Point& bottomRight);
    void update(std::vector<Ball>& balls, Duster& duster, size_t ticks) const;

  private:
    void collideBalls(std::vector<Ball>& balls, Duster& duster) const;
    void collideWithBox(std::vector<Ball>& balls) const;
    void move(std::vector<Ball>& balls, Duster& duster) const;
    void processCollision(Ball& a, Ball& b, Duster& duster,
                          double distanceBetweenCenters2) const;

  private:
    Point topLeft;
    Point bottomRight;
    double timePerTick;
};
