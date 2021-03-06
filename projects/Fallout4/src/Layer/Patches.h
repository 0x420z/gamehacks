#pragma once

#include "Icetrix/Layer.h"
#include "Icetrix/Memory/BytePatch.h"

using Icetrix::Memory::Patch;

class Patches
{
private:
	Icetrix::Application& app;
	std::vector<Patch>(patches) = {
		Patch{ "Unlimited Ammo", 0x34DBBD, { 0xFF, 0x90, 0x80, 0x07, 0x00, 0x00 }, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 } },
		Patch{ "Unlimited AP", 0xDC2D55, { 0xFF, 0x50, 0x30 }, { 0x90, 0x90, 0x90 } },
		Patch{ "No Weight", 0xD87163, { 0xE8, 0xE8, 0x91, 0x67, 0xFF }, { 0x90, 0x90, 0x90, 0x90, 0x90 } },
	};
public:
	Patches() : app(Icetrix::Application::GetInstance())
	{
		app.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&Patches::OnAttach>(*this);
		app.dispatcher.sink<Icetrix::LayerEvent::Update>().connect<&Patches::OnUpdate>(*this);
		app.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&Patches::OnDetach>(*this);
	}

	void OnAttach();
	void OnUpdate();
	void OnDetach();
};
