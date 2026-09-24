//
// Created by elbus on 2026-09-18.
//

#include "Color.hpp"
#include "Dust.h"

static Color DEFAULT_DUST_COLOR = Color{0.99, 0.0, 0.0};

// CONSTRUCTORS
Dust::Dust() :
    center_(Point{0, 0}), velocity_(Velocity{0, 0.0}), radius_(0), color_(DEFAULT_DUST_COLOR), remainingTicks_(5) {}

Dust::Dust(const Point& center, const Velocity velocity, const double radius,
           const long remainingTicks, const Color& color) :
    center_(center),
    velocity_(velocity),
    radius_(radius),
    color_(color),
    remainingTicks_(remainingTicks) {}

// MEMBER FUNCTIONS
void Dust::setVelocity(const Velocity& velocity) {
    velocity_ = velocity;
}
Velocity Dust::getVelocity() const {
    return velocity_;
}

void Dust::draw(Painter& painter) const {
    painter.draw(center_, radius_, color_);
}

void Dust::setCenter(const Point& center) {
    center_ = center;
}

Point Dust::getCenter() const {
    return center_;
}
double Dust::getRadius() const {
    return radius_;
}
double Dust::getMass() const {
    return M_PI * radius_ * radius_ * radius_ * 4.0 / 3.0;
}
long Dust::getRemainingTicks() const {
    return remainingTicks_;
}

void Dust::setRemainingTicks(const long remainingTicks) {
    remainingTicks_ = remainingTicks;
}
