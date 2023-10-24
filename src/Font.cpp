#include "Font.h"


namespace ImApp {
	Font::Font(const std::string& path, float size) {
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		m_Font = io.Fonts->AddFontFromFileTTF(path.c_str(), size);
		m_Size = size;
	}
	Font::Font(void* data, int dataSize, float size) {
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		m_Font = io.Fonts->AddFontFromMemoryCompressedTTF(data, dataSize, size);
		m_Size = size;
	}
}