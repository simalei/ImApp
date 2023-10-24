#include <ImApp.h>

#include <iostream>
#include <imgui.h>

#include <misc/cpp/imgui_stdlib.h>

#include "DroidSans.h"

static bool ShowDemo = false;
static bool ShowAbout = false;

void Init(ImApp::AppSpecification* spec) {

	using namespace ImApp;
	ImGui::GetIO().Fonts->AddFontDefault();
	Application::AddFont("droid-sans14", (void*)DroidSans_compressed_data, DroidSans_compressed_size, 14.f);
	Application::AddFont("droid-sans16", (void*)DroidSans_compressed_data, DroidSans_compressed_size, 16.f);
	Application::AddFont("droid-sans20", (void*)DroidSans_compressed_data, DroidSans_compressed_size, 20.f);
	Application::AddFont("droid-sans24", (void*)DroidSans_compressed_data, DroidSans_compressed_size, 24.f);

	Application::AddImage("my-image01", "MyImage01.jpg");
}

void Render(ImApp::AppSpecification* spec) {
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	ImGui::Begin("Example app", nullptr, ImGuiWindowFlags_NoTitleBar);

	ImGui::SeparatorText("ImGui");
	
	ImGui::Checkbox("Show demo window", &ShowDemo);
	ImGui::Checkbox("Show about window", &ShowAbout);

	ImGui::SeparatorText("Font");

	ImGui::PushFont(IMAPP_FONT("droid-sans14"));
	ImGui::Text("Droid sans font, size 14");
	ImGui::PopFont();
	
	ImGui::PushFont(IMAPP_FONT("droid-sans16"));
	ImGui::Text("Droid sans font, size 16");
	ImGui::PopFont();

	ImGui::PushFont(IMAPP_FONT("droid-sans20"));
	ImGui::Text("Droid sans font, size 20");
	ImGui::PopFont();

	ImGui::PushFont(IMAPP_FONT("droid-sans24"));
	ImGui::Text("Droid sans font, size 24");
	ImGui::PopFont();

	ImGui::SeparatorText("App properties");

	ImGui::InputText("Window title", &spec->title);
	ImGui::InputInt("Window width", &spec->width);
	ImGui::InputInt("Window height", &spec->height);

	ImGui::Checkbox("VSync", &spec->vsync);

	ImGui::Text("Docking and viewports options can not be changed at runtime");

	ImGui::SeparatorText("Image");

	ImGui::Image(IMAPP_IMAGE("my-image01"));

	ImGui::SeparatorText("Info");

	ImGui::Text("Running ImApp version %s based on ImGui %s", IMAPP_VERSION, ImGui::GetVersion());
	ImGui::Text("Framerate: %f", ImGui::GetIO().Framerate);
	ImGui::Text("Frametime: %f ms", 1000.f / ImGui::GetIO().Framerate);
	ImGui::Text("Platform: %s", ImGui::GetIO().BackendPlatformName);
	ImGui::Text("Backend: %s", ImGui::GetIO().BackendRendererName);
	

	ImGui::End();

	if (ShowDemo)
	{
		ImGui::ShowDemoWindow();
	}

	if (ShowAbout)
	{
		ImGui::ShowAboutWindow();
	}
}


int main(int argc, char** argv) {
	using namespace ImApp;

	AppSpecification spec;
	spec.title = "ImApp Example";
	spec.width = 800;
	spec.height = 600;
	spec.viewports = true;
	spec.docking = true;
	
	Application app(spec);
	app.SetInit(Init);
	app.SetRender(Render);
	
	app.Run();
}