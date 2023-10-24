#include "Image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <imgui_internal.h>

constexpr auto GL_CLAMP_TO_EDGE = 0x812F;

namespace ImApp {
	Image::Image(const std::string& path)
	{
        this->m_Width = 0;
        this->m_Height = 0;
        unsigned char* image_data = stbi_load(path.c_str(), &this->m_Width, &this->m_Height, NULL, 4);
        glGenTextures(1, &this->m_Texture);
        glBindTexture(GL_TEXTURE_2D, this->m_Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
	}
}

namespace ImGui {
    void Image(ImApp::Image* img) {
        //std::cout << img->GetTexutre() << ":" << img->GetWidth() << ":" << img->GetHeight() << std::endl;
        if (img->GetTexutre() != 1 || img->GetWidth() == 0 || img->GetHeight() == 0)
        {
            ImGui::TextColored({ 255, 0, 0, 255 }, "Failed to load image");
        }
        else {
            ImGui::Image((void*)(intptr_t)img->GetTexutre(), ImVec2((float)img->GetWidth(), (float)img->GetHeight()));
        }
    }
}