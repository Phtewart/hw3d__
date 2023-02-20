#pragma once
#include "TestObject.h"
#include "ConstantBuffers.h"

class AssimpM : public TestObject<AssimpM>
{
public:
	AssimpM(Graphics& gfx, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist,
		DirectX::XMFLOAT3 material,
		float scale);
};