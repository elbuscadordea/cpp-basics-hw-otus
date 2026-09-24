//
// Created by elbus on 2026-09-18.
//
#pragma once

#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Dust {
public:
    Dust();
    Dust(const Point& center, Velocity velocity, double radius, long remainingTicks, const Color& color);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    long getRemainingTicks() const;
    void setRemainingTicks(long remainingTicks);

private:
    Point center_;
    Velocity velocity_;
    double radius_;
    Color color_;
    long remainingTicks_;

};

