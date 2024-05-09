#pragma once
#include <math.h>

namespace Engine {
	struct Vector2 {
		float x;
		float y;
		Vector2() = default;
		Vector2(float x, float y) {
			this->x = x;
			this->y = y;
		}
		Vector2 operator*(const float& rhs) {
			Vector2 temp;
			temp.x = this->x * rhs;
			temp.y = this->y * rhs;
			return temp;
		}
		Vector2 operator*=(const float& rhs) {
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		Vector2 operator/(const float& rhs) {
			Vector2 temp;
			temp.x = this->x / rhs;
			temp.y = this->y / rhs;
			return temp;
		}
		Vector2 operator=(const Vector2& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Vector2 operator+(const Vector2& rhs) {
			Vector2 temp;
			temp.x = this->x + rhs.x;
			temp.y = this->y + rhs.y;
			return temp;
		}
		Vector2 operator-(const Vector2& rhs) {
			Vector2 temp;
			temp.x = this->x - rhs.x;
			temp.y = this->y - rhs.y;
			return temp;
		} 
		Vector2& operator+=(const Vector2& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		Vector2& operator-=(const Vector2& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}
		void Normalize() {
			float length = sqrtf(this->x * this->x + this->y * this->y);
			if (length == 0) return;
			this->x /= length;
			this->y /= length;
		}
	};

	struct Vector2Int {
		int x;
		int y;
		Vector2Int() = default;
		Vector2Int(int x, int y) {
			this->x = x;
			this->y = y;
		}
		Vector2Int operator*(const float& rhs) {
			Vector2Int temp;
			temp.x = this->x * rhs;
			temp.y = this->y * rhs;
			return temp;
		}
		Vector2Int operator*=(const float& rhs) {
			this->x *= rhs;
			this->y *= rhs;
			return *this;
		}
		Vector2Int operator/(const float& rhs) {
			Vector2Int temp;
			temp.x = this->x / rhs;
			temp.y = this->y / rhs;
			return temp;
		}
		Vector2Int operator=(const Vector2Int& rhs) {
			this->x = rhs.x;
			this->y = rhs.y;
			return *this;
		}
		Vector2Int operator+(const Vector2Int& rhs) {
			Vector2Int temp;
			temp.x = this->x + rhs.x;
			temp.y = this->y + rhs.y;
			return temp;
		}
		Vector2Int operator-(const Vector2Int& rhs) {
			Vector2Int temp;
			temp.x = this->x - rhs.x;
			temp.y = this->y - rhs.y;
			return temp;
		}
		Vector2Int& operator+=(const Vector2Int& other) {
			this->x += other.x;
			this->y += other.y;
			return *this;
		}
		Vector2Int& operator-=(const Vector2Int& other) {
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}
	};

	struct Bounds {
		Vector2 center;
		Vector2 extents;
		Bounds() {
			this->center = { 0.0f, 0.0f };
			this->extents = { 0.0f, 0.0f };
		}
		Bounds(Vector2 center, Vector2 extents) {
			this->center = center;
			this->extents = extents;
		}

		Vector2 size() {
			return extents * 2;
		}
		
		Vector2 maxPosition() {
			return center + extents;
		}

		Vector2 minPosition() {
			return center - extents;
		}
	};
}