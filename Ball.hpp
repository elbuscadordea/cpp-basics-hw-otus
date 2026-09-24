#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;

    Ball();
    Ball(
        const Point& center,
        double radius,
        const Velocity& velocity, const Color& color,
        bool isCollidable = false
        );

private:
    Point center_;
    Velocity velocity_;
    double radius_;
    bool isCollidable_;
    Color color_;
};
