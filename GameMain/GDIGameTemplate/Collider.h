#include "Vector2.h"
#include "Bounds.h"
#include "Object.h"
#pragma once

class Collider {
private:
    Object* parent;

    friend struct Object;
    friend class CircleCollider;
    friend class RectangleCollider;
    friend class ColliderManager;
    virtual Vector2 GetPosition() const = 0;
public:
    virtual bool isColliding(const Collider& other) const = 0;
};

class CircleCollider : public Collider {
private:
    float radius = 0.f;
    Vector2 point = {0.f, 0.f};

    friend struct Object;
    friend class Collider;
    friend class CircleCollider;
    friend class RectangleCollider;

    Vector2 GetPosition() const override;
public:
    CircleCollider(Vector2 _point, float _radius) : point(_point), radius(_radius) {}

    bool isColliding(const Collider& other) const override;
};

class RectangleCollider : public Collider {
private:
    Bounds bounds = { {0.f,0.f}, {0.f, 0.f} };

    friend struct Object;
    friend class Collider;
    friend class CircleCollider;
    friend class RectangleCollider;

    Vector2 GetPosition() const override;
public:
    RectangleCollider(Vector2 _pointUL, Vector2 _pointDR) {
        bounds = { {0.0f,0.0f}, {(_pointDR.x - _pointUL.x) / 2.0f, (_pointDR.y - _pointUL.y) / 2.0f} };
    }
    RectangleCollider(Vector2 _center, Vector2 _size) {
        bounds.center = _center;
        bounds.extents = _size / 2.f;
    }

    bool isColliding(const Collider& other) const override;
};