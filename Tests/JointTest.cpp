#include "JointTest.h"
#include "../Physics/Body.h"
#include "../Physics/Shape/CircleShape.h"
#include "../Physics/World.h"
#include "../Physics/Constraints/Joint.h"

#define SPRING_STIFFNESS   100
#define SPRING_LENGTH      1
#define BODY_DAMPING       10
#define CHAIN_SIZE         3

void JointTest::Initialize()
{
	Test::Initialize();

	glm::vec4 color = { 1, 1, 1, 1 };
	m_anchor = new Body(new CircleShape(1, color), { 0, 0 }, { 0, 0 }, 1, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	auto prevBody = m_anchor;
    Body* prevRow[3] = {};

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 2; col++)
        {
            Body* body = new Body(new CircleShape(0.5f, color), { col * 3, row * 3 }, { 0, 0 }, 1, Body::DYNAMIC);
            body->damping = BODY_DAMPING;
            m_world->AddBody(body);

            if (prevBody)
            {
                Joint* joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
                m_world->AddJoint(joint);
            }

            if (prevRow[col])
            {
                Joint* joint = new Joint(prevRow[col], body, SPRING_STIFFNESS, SPRING_LENGTH);
                m_world->AddJoint(joint);
            }

            prevBody = body;
            prevRow[col] = body;
        }
    }
}

void JointTest::Update()
{
	Test::Update();
    m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}
