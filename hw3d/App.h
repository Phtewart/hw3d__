#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include <set>
#include "ScriptCommander.h"

class App
{
public:
	App(const std::string& commandLine = "");
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	ImguiManager imguim;
	Window wnd;
	ScriptCommander scriptCommander;
	Timer timer;
	float speed_factor = 1.0f;
	Camera camera;
	PointLight pLight;
	//Model nano{ wnd.Gfx(),"models\\nano_textured\\nanosuit.obj" };
	Model cube{ wnd.Gfx(),"models\\scene_1\\scene_1.obj" };
	bool mouseLeftIsPressed = false;
};
