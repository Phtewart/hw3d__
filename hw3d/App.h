#pragma once
#include "Window.h"
#include "Timer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include <set>

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
private:
	ImguiManager imguim;
	Window wnd;
	Timer timer;
	float speed_factor = 1.0f;
	Camera camera;
	PointLight pLight;
	Model nano{ wnd.Gfx(),"models\\nano.gltf" };
};
