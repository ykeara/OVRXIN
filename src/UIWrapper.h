#pragma once
#include "AppManifest.h"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

class UIWrapper
{
public:
    const char* m_glslVersion = "#version 130";
    GLFWwindow* m_window;
    void Init();
    void Update();
    void Render();
    void Shutdown();

    UIWrapper();
};