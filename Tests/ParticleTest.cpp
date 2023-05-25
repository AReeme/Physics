#include "ParticleTest.h"

void ParticleTest::Initialize()
{
    Test::Initialize();
}

void ParticleTest::Update()
{
    Test::Update();

    if (m_input->GetMouseButton(0))
    {
        glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);
        glm::vec4 color{ randomf(), randomf(), randomf(), 1 };

        auto body = new Body(new CircleShape(randomf(10, 20), color), m_input->GetMousePosition(), velocity);
        body->damping = 1;
        m_world->AddBody(body);
    }
}

void ParticleTest::FixedUpdate()
{
    m_world->Step(m_time->GetFixedDeltaTime());
}

void ParticleTest::Render()
{
    m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
    m_world->Draw(m_graphics);
}
