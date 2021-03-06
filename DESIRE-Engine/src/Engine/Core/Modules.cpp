#include "Engine/stdafx.h"
#include "Engine/Core/Modules.h"
#include "Engine/Core/Application.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Render/Render.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Script/ScriptSystem.h"
#include "Engine/Sound/SoundSystem.h"

std::unique_ptr<Application> Modules::Application;
std::unique_ptr<Input> Modules::Input;
std::unique_ptr<Physics> Modules::Physics;
std::unique_ptr<Render> Modules::Render;
std::unique_ptr<ResourceManager> Modules::ResourceManager;
std::unique_ptr<ScriptSystem> Modules::ScriptSystem;
std::unique_ptr<SoundSystem> Modules::SoundSystem;
