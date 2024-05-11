#include "Collider.h"
#include <algorithm>
#include <cmath> 

Vector2 CircleCollider::GetPosition() const {
    return parent->GetPosition() + point;
}

bool CircleCollider::isColliding(const Collider& other) const {
    // 원과 원 충돌
    if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other)) {
        float distance = std::sqrt(std::pow(circle->GetPosition().x - GetPosition().x, 2) +
            std::pow(circle->GetPosition().y - GetPosition().y, 2));
        return distance < circle->radius + radius;
    }
    // 원과 사각형 충돌
    else if (const RectangleCollider* r = dynamic_cast<const RectangleCollider*>(&other)) {
        if (GetPosition().x >= r->GetPosition().x - r->bounds.extents.x &&
            GetPosition().x <= r->GetPosition().x + r->bounds.extents.x &&
            GetPosition().y >= r->GetPosition().y - r->bounds.extents.y &&
            GetPosition().y <= r->GetPosition().y + r->bounds.extents.y) {
            return true;
        }

        // 원의 중심이 사각형의 가장자리에 있는지 확인
        float dx = GetPosition().x - std::max(r->GetPosition().x - r->bounds.extents.x,
            std::min(GetPosition().x, r->GetPosition().x + r->bounds.extents.x));
        float dy = GetPosition().y - std::max(r->GetPosition().y - r->bounds.extents.y,
            std::min(GetPosition().y, r->GetPosition().y + r->bounds.extents.y));
        return (dx * dx + dy * dy) <= (radius * radius);
    }
    return false;
}

Vector2 RectangleCollider::GetPosition() const {
    return parent->GetPosition() + bounds.center;
}

bool RectangleCollider::isColliding(const Collider& other) const {
    // 사각형과 원 충돌
    if (const CircleCollider* c = dynamic_cast<const CircleCollider*>(&other)) {
        if (c->GetPosition().x >= GetPosition().x - bounds.extents.x && 
            c->GetPosition().x <= GetPosition().x + bounds.extents.x &&
            c->GetPosition().y >= GetPosition().y - bounds.extents.y && 
            c->GetPosition().y <= GetPosition().y + bounds.extents.y) {
            return true;
        }

        // 원의 중심이 사각형의 가장자리에 있는지 확인
        float dx = c->GetPosition().x - std::max(GetPosition().x - bounds.extents.x,
            std::min(c->GetPosition().x, GetPosition().x + bounds.extents.x));
        float dy = c->GetPosition().y - std::max(GetPosition().y - bounds.extents.y,
            std::min(c->GetPosition().y, GetPosition().y + bounds.extents.y));
        return (dx * dx + dy * dy) <= (c->radius * c->radius);
    }
    // 사각형과 사각형 충돌
    else if (const RectangleCollider* r = dynamic_cast<const RectangleCollider*>(&other)) {
        auto compare1 = GetPosition();
        auto compare2 = r->GetPosition();
        Vector2 thisLcorner = Vector2(-bounds.extents.x, - bounds.extents.y);
        thisLcorner += compare1;
        Vector2 thisRcorner = bounds.extents;
        thisRcorner += compare1;
        Vector2 otherLcorner = Vector2(-r->bounds.extents.x, -r->bounds.extents.y);
        otherLcorner += compare2;
        Vector2 otherRcorner = r->bounds.extents;
        otherRcorner += compare2;

        if (otherRcorner.y < thisLcorner.y
            || otherLcorner.y > thisRcorner.y
            || otherRcorner.x < thisLcorner.x
            || otherLcorner.x > thisRcorner.x)
            return false;
        else
            return true;
    }
}