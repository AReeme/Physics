#include "Body.h"
#include "Integrator.h"
#include "World.h"
#include "../Physics/Shape/Shape.h"
#include "../Physics/Shape/CircleShape.h"
#include <glm/glm.hpp>

void Body::ApplyForce(const glm::vec2& force)
{
	this->force += force;
}

void Body::Step(float dt)
{
	if (type != DYNAMIC)
	{
		return;
	}

	//gravity
	ApplyForce(World::gravity * gravityScale * mass);

	Integrator::ExplicitEuler(*this, dt);
	ClearForce();
	// damping
	velocity *= (1.0f / (1.0f + (damping * dt)));
}

void Body::Draw(Graphics* graphics)
{
	shape->Draw(graphics, position);
}

bool Body::Intersects(Body* body)
{
	glm::vec2 direction = body->position - position;
	float distance = glm::length(direction);
	float radius = ((CircleShape*)shape)->radius + ((CircleShape*)body->shape)->radius;
	return distance <= radius;
}
