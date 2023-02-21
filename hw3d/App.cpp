#include "App.h"
#include "Box.h"
#include "AssimpM.h"
#include <memory>
#include <algorithm>
#include "Surface.h"
#include "SkinnedBox.h"
#include "GDIPlusManager.h"
#include "imgui/imgui.h"

namespace dx = DirectX;
GDIPlusManager gdipm;

App::App()
	:
	wnd(1200, 900, "The Donkey Fart Box"),
	pLight(wnd.Gfx())
	
{
	wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speed_factor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(camera.GetMatrix());
	pLight.Bind(wnd.Gfx(),camera.GetMatrix());

	nano.Draw(wnd.Gfx());
	pLight.Draw(wnd.Gfx());
	
	//imgui window
	camera.SpawnControlWindow();
	pLight.SpawnControlWindow();
	nano.ShowWindow();

	// present
	wnd.Gfx().EndFrame();
}

App::~App()
{}


int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}