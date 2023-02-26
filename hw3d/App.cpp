#include "App.h"
#include <memory>
#include <algorithm>
#include "Surface.h"
#include "imgui/imgui.h"
#include <dxtex\DirectXTex.h>


namespace dx = DirectX;

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

	//nano.Draw(wnd.Gfx());
	cube.Draw(wnd.Gfx());
	pLight.Draw(wnd.Gfx());
	
	
	if(wnd.mouse.RightIsPressed())
	{
		wnd.DisableCursor();
		wnd.mouse.EnableRaw();
	}
	else
	{
		wnd.EnableCursor();
		wnd.mouse.DisableRaw();
	}


	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			camera.Translate({ 0.0f,0.0f,dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			camera.Translate({ -dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			camera.Translate({ 0.0f,0.0f,-dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			camera.Translate({ dt,0.0f,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('E'))
		{
			camera.Translate({ 0.0f,dt,0.0f });
		}
		if (wnd.kbd.KeyIsPressed('Q'))
		{
			camera.Translate({ 0.0f,-dt,0.0f });
		}
	}
	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			camera.Rotate((float)delta->x, (float)delta->y);
		}
	}

	//imgui window
	camera.SpawnControlWindow();
	pLight.SpawnControlWindow();
	cube.ShowWindow();
	//nano.ShowWindow();

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