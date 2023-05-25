#include "CollisionTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shape/CircleShape.h"

void CollisionTest::Initialize()
{
	Test::Initialize();

	glm::vec4 color = { 0, 0, 1, 1 };
	m_user = new Body(new CircleShape(1, color), { 0, 0 }, { 0, 0 }, 1, Body::KINEMATIC);
	m_world->AddBody(m_user);

	glm::vec4 color3 = glm::vec4{ 1.0f };
	auto body = new Body(new CircleShape(200, color3), { 0, -207.5 }, { 0, 0 }, 1, Body::STATIC);
	m_world->AddBody(body);
}

void CollisionTest::Update()
{
	Test::Update();

	glm::vec2 position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
	m_user->velocity = position - m_user->position;
	m_user->position = position;

	glm::vec4 color2 = { randomf(), randomf(), randomf(), 1 };
	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = { 0,0 };//randomUnitCircle() * randomf(1, 3);
		float size = randomf(0.1f, 0.8f);

		auto body = new Body(new CircleShape(size, color2), position, velocity, size);
		body->damping = 0.4f;
		body->gravityScale = 0.5f;
		body->restitution = 1;

		m_world->AddBody(body);
	}
}

void CollisionTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void CollisionTest::Render()
{
	m_world->Draw(m_graphics);
}