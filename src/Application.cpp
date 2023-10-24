#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl2.h>
#include <Windows.h>
#include <imgui_internal.h>
#include "Font.h"
#include "Image.h"

//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
namespace ImApp {
    int Application::m_oWidth = 0, Application::m_oHeight = 0;
    std::unordered_map<std::string, Font> Application::m_FontStack;
    std::unordered_map<std::string, Image> Application::m_ImageStack;
    void glfwErrorCallback(int error, const char* description) {
        char buf[256];
        sprintf(buf, "GLFW Error %d: %s", error, description);
        MessageBoxA(NULL, buf, "ImApp", MB_ICONERROR);
    }

    void glfwWindowSizeCallback() {
        
    }

	Application::Application(const AppSpecification& spec) : m_Spec(spec), m_IsRunning(false), m_Window(nullptr) {}

	Application::~Application()
	{
		Shutdown_int();
	}

    void Application::AddFont(const std::string& id, const std::string& path, float size)
    {
        Font font = Font(path, size);
        m_FontStack.insert({ id, font });
    }

    void Application::AddFont(const std::string& id, void* data, int dataSize, float size)
    {
        Font font = Font(data, dataSize, size);
        m_FontStack.insert({ id, font });
    }

    Font* Application::GetFont(const std::string& id)
    {
        if (&ImApp::Application::GetFontStack().at(id))
        {
            return &ImApp::Application::GetFontStack().at(id);
        } else {
            return nullptr;
        }
    }

    void Application::AddImage(const std::string& id, const std::string& path) 
    {
        Image image = Image(path);
        m_ImageStack.insert({ id, image });

    }

    Image* Application::GetImage(const std::string& id)
    {
        if (&ImApp::Application::GetImageStack().at(id))
        {
            return &ImApp::Application::GetImageStack().at(id);
        }
        else {
            return nullptr;
        }
    }

    void Application::Init_int()
	{
        glfwInit();
        glfwSetErrorCallback(glfwErrorCallback);
        /*
        if (this->m_Spec.customTitlebar)
        {
            // TODO: Custom titlebar
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        }
        */
        // Create window with graphics context
        GLFWwindow* window = glfwCreateWindow(this->m_Spec.width, this->m_Spec.height, this->m_Spec.title.c_str(), NULL, NULL);
        if (window == NULL)
            return;
        glfwMakeContextCurrent(window);
        glfwSwapInterval(this->m_Spec.vsync); // Enable vsync

        m_oWidth = this->m_Spec.width;
        m_oHeight = this->m_Spec.height;

        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            Application::m_oWidth = width;
            Application::m_oHeight = height;
        });

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        
        if (this->m_Spec.viewports)
        {
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        }

        if (this->m_Spec.docking)
        {
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        }

        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        switch (this->m_Spec.style)
        {
            case Style::Dark: ImGui::StyleColorsDark(); break;
            case Style::Light: ImGui::StyleColorsLight(); break;
            case Style::Classic: ImGui::StyleColorsClassic(); break;
        }

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL2_Init();


        this->m_Window = window;
		this->m_IsRunning = true;
        
	}
	void Application::Update_int() 
	{

        ImGuiStyle& style = ImGui::GetStyle();
        
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        /*
        if (this->m_Spec.customTitlebar)
        {
            // TODO: Custom titlebar
        }
        */
        this->m_Spec.width = m_oWidth;
        this->m_Spec.height = m_oHeight;
        this->m_Render(&this->m_Spec);



        glfwSetWindowTitle(this->m_Window, this->m_Spec.title.c_str());
        glfwSetWindowSize(this->m_Window, this->m_Spec.width, this->m_Spec.height);
        glfwSwapInterval(this->m_Spec.vsync);
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->m_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        auto& io = ImGui::GetIO();
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwMakeContextCurrent(this->m_Window);
        glfwSwapBuffers(this->m_Window);



        this->m_IsRunning = !glfwWindowShouldClose(this->m_Window);
	}

	void Application::Shutdown_int() 
	{
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(this->m_Window);
        glfwTerminate();
	}

	void Application::Run()
	{
		this->Init_int();
		this->m_Init(&this->m_Spec);
		while (m_IsRunning)
		{
			this->Update_int();
		}
		//this->Shutdown_int(); shutting down happens automatically in destructor
	}

	void Application::SetInit(const std::function<void(ImApp::AppSpecification*)>& func) {
		this->m_Init = func;
	}
	void Application::SetRender(const std::function<void(ImApp::AppSpecification*)>& func) {
		this->m_Render = func;
	}
}