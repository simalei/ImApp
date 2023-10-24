#pragma once

// ImApp - ImGui app framework

constexpr char* IMAPP_VERSION = "0.1";

#define IMAPP_FONT(id)	ImApp::Application::GetFont(id)->GetImFont()
#define IMAPP_IMAGE(id) ImApp::Application::GetImage(id)

#include "Application.h"
#include "Image.h"
#include "Font.h"