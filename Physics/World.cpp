#include "World.h"
#include "Body.h"
#include "../Physics/Forces/ForceGenerator.h"
#include "../Physics/Constraints/Joint.h"
#include "Collision/Collision.h"

glm::vec2 World::gravity{ 0, -9.8f };

World::~World()
{
	// <delete all the objects>
	for (auto body : m_bodies)
	{
		delete body;
	}

	// <clear the objects form the list clear()>
	m_bodies.clear();
}
void World::Step(float dt)
{
	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
	if (!m_bodies.empty() && !m_forceGenerators.empty())
	{
		for (auto forceGenerator : m_forceGenerators)
		{
			forceGenerator->Apply(bodies);
		}
	}

	for (auto joint : m_joints) joint->Step(dt);
	for (auto body : bodies) body->Step(dt);

	//Collision
	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);
}
void World::Draw(Graphics* graphics)
{
	// <call Draw() on all the objects>
	for (auto joint : m_joints) joint->Draw(graphics);
	for (auto forceGenerator : m_forceGenerators) forceGenerator->Draw(graphics);
	for (auto body : m_bodies) body->Draw(graphics);
}
void World::AddBody(Body* body)
{
	// <push back the po onto objects list>
	m_bodies.push_back(body);
}
void World::RemoveBody(Body* body)
{
	// <remove po from the objects list>
	m_bodies.remove(body);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}

void World::AddForceGenerator(ForceGenerator* forceGenerator)
{
	m_forceGenerators.push_back(forceGenerator);
}
