#pragma once
#include "Test.h"
#include "../Physics/Shape/CircleShape.h"
#include "../Physics/World.h"
#include "../Physics/Body.h"

class ParticleTest : public Test
{
public:
	void Initialize() override;

	void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

protected:



};