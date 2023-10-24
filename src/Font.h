#pragma once
#include <string>
#include <map>
#include <imgui.h>

namespace ImApp {
	class Font
	{
	public:
		Font(const std::string& path, float size);
		Font(void* data, int dataSize, float size);
		inline ImFont* GetImFont() {
			return m_Font;
		}
	private:
		float m_Size;
		ImFont* m_Font;
	};
}

