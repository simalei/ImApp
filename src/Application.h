#pragma once

#include <string>
#include <functional>

struct GLFWwindow;

namespace ImApp {

	enum Style {
		Dark,
		Light,
		Classic
	};

	class Font;
	class Image;

	struct AppSpecification {
		std::string title = "ImApp";
		int width = 800, height = 600;
		Style style = Style::Dark;
		bool vsync = true;
		bool viewports = true, docking = true;
	};

	class Application
	{
	public:
		Application(const AppSpecification& = AppSpecification());
		~Application();
		void Run();

		void SetInit(const std::function<void(ImApp::AppSpecification*)>&);
		void SetRender(const std::function<void(ImApp::AppSpecification*)>&);

		inline static auto& GetFontStack() {
			return m_FontStack;
		}
		inline static auto& GetImageStack() {
			return m_ImageStack;
		}
		static void AddImage(const std::string& id, const std::string& path);
		static Image* GetImage(const std::string& id);

		static void AddFont(const std::string& id, const std::string& path, float);
		static void AddFont(const std::string& id, void* data, int dataSize, float size);
		static Font* GetFont(const std::string& id);
		//static void AddFont();

	private:
		void Init_int();
		void Update_int();
		void Shutdown_int();
		std::function<void(ImApp::AppSpecification*)> m_Init;
		std::function<void(ImApp::AppSpecification*)> m_Render;

		static std::unordered_map<std::string, Font> m_FontStack;
		static std::unordered_map<std::string, Image> m_ImageStack;

		AppSpecification m_Spec;
		GLFWwindow* m_Window;
		bool m_IsRunning;

		static int m_oWidth, m_oHeight;

	};
}