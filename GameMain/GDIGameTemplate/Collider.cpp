#include "Collider.h"
#include <algorithm>
#include <cmath> 

bool CircleCollider::isColliding(const Collider& other) const {
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float distance = std::sqrt(std::pow(circle->point.x - point.x, 2) + std::pow(circle->point.y - point.y, 2));
        return distance < circle->radius + radius;
    }
    else if (const RectangleCollider* rectangle = dynamic_cast<const RectangleCollider*>(&other)) {
        float localX = point.x - rectangle->pointUL.x;
        float localY = point.y - rectangle->pointUL.y;

        float closestX = std::clamp(localX, -rectangle->pointUL.x / 2, rectangle->pointDR.x / 2);
        float closestY = std::clamp(localY, -rectangle->pointUL.y / 2, rectangle->pointDR.x / 2);

        float distanceX = localX - closestX;
        float distanceY = localY - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;

        return distanceSquared < radius * radius;
    }
    return false;
}

bool RectangleCollider::isColliding(const Collider& other) const {
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float localX = circle->point.x - pointUL.x;
        float localY = circle->point.y - pointUL.y;

        float closestX = std::clamp(localX, -pointUL.x / 2, pointDR.x / 2);
        float closestY = std::clamp(localY, -pointUL.y / 2, pointDR.x / 2);

        float distanceX = localX - closestX;
        float distanceY = localY - closestY;
        float distanceSquared = distanceX * distanceX + distanceY * distanceY;

        return distanceSquared < circle->radius * circle->radius;
    }
    else if (const RectangleCollider* rectangle = dynamic_cast<const RectangleCollider*>(&other)) {

    }
}