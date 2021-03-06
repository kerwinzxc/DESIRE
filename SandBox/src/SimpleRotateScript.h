#pragma once

#include "Engine/Script/IScript.h"

class SimpleRotateScript : public IScript
{
public:
	SimpleRotateScript();
	~SimpleRotateScript();

	void Init() override;
	void Kill() override;
	void Update() override;

	std::function<void(std::array<IScript::Arg, 6>)> GetFunctionToCall(const char *functionName) override;

private:
	float rot = 0.0f;
};
