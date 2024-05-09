#include "Collider.h"
#include "Transform.h"

namespace Engine {
	Collider::Collider() {
	}
	bool Collider::isCollision(Collider& collider) {
		if (this->GetTransform() == nullptr || collider.GetTransform() == nullptr) return false;
		auto temp = this->GetTransform()->position;
		auto temp1 = collider.GetTransform()->position;
		Vector2 thisLcorner = this->bounds.center - this->bounds.extents;
		thisLcorner += temp;
		Vector2 thisRcorner = this->bounds.center + this->bounds.extents;
		thisRcorner += temp;
		Vector2 otherLcorner = collider.bounds.center - collider.bounds.extents;
		otherLcorner += temp1;
		Vector2 otherRcorner = collider.bounds.center + collider.bounds.extents;
		otherRcorner += temp1;

		if (otherRcorner.y < thisLcorner.y
			|| otherLcorner.y > thisRcorner.y
			|| otherRcorner.x < thisLcorner.x
			|| otherLcorner.x > thisRcorner.x)
			return false;
		else
			return true;
	}
}