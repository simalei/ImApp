#pragma once
#include <string>
#include <Windows.h>
#include <gl/GL.h>


typedef unsigned int GLuint;

namespace ImApp {
	class Image
	{
	public:
		Image(const std::string& path);

		inline int GetWidth() {
			return m_Width;
		}

		inline int GetHeight() {
			return m_Width;
		}

		inline GLuint GetTexutre() {
			return m_Texture;
		}

	private:
		int m_Width;
		int m_Height;
		GLuint m_Texture;
	};
}

namespace ImGui {
	void Image(ImApp::Image* image);
}