#include "ForceTest.h"
#include "../Physics/Forces/GravitationalGenerator.h"
#include "../Physics/Forces/GravitationalForce.h"
#include "../Physics/Shape/CircleShape.h"
#include "../Physics/Body.h"
#include "../Physics/Forces/PointForce.h"
#include "../Physics/Forces/AreaForce.h"
#include "../Physics/Forces/DragForce.h"
//#define POINT_FORCE
//#define AREA_FORCE
#define DRAG_FORCE

void ForceTest::Initialize()
{
    Test::Initialize();

#if defined(POINT_FORCE)
    glm::vec4 color = { 1, 1, 1, 0.2f };
    auto body = new Body(new CircleShape(200.0f, color), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new PointForce(body, 2000);
    m_world->AddForceGenerator(forceGenerator);
#elif defined(AREA_FORCE)
    glm::vec4 color = { 1, 1, 1, 0.2f };
    auto body = new Body(new CircleShape(200, color), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new AreaForce(body, 2000, -90);
    m_world->AddForceGenerator(forceGenerator);
#elif defined(DRAG_FORCE)
    glm::vec4 color = { 1, 1, 1, 0.2f };
    auto body = new Body(new CircleShape(200, color), { 400, 300 }, { 0, 0 }, 0, Body::STATIC);
    ForceGenerator* forceGenerator = new DragForce(body, 0.5f);
    m_world->AddForceGenerator(forceGenerator);
#endif

    //auto forceGenerator = new GravitationalForce(400);
    //m_world->AddForceGenerator(forceGenerator);
}

void ForceTest::Update()
{
    Test::Update();

    if (m_input->GetMouseButton(0))
    {
        glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

        float size = randomf(1, 8);
        glm::vec4 color{ randomf(), randomf(), randomf(), 1 };
        auto body = new Body(new CircleShape(size * 2, color), m_input->GetMousePosition(), velocity, size);
        body->damping = 1;
        body->gravityScale = 30;
        m_world->AddBody(body);
    }
}

void ForceTest::FixedUpdate()
{
    m_world->Step(m_time->GetFixedDeltaTime());
}

void ForceTest::Render()
{
    m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
    m_world->Draw(m_graphics);
}
