#include <string>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "UserInterface.h"

#include "Window.h"

void UserInterface::Init(RenderData& renderData)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderData.window->GetGLFWWindow(), true);
    const char *glslVersion = "#version 460 core";
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void UserInterface::CreateFrame(RenderData& renderData)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags imguiWindowFlags = 0;
    ImGui::SetNextWindowBgAlpha(0.8f);
    ImGui::Begin("Info", nullptr, imguiWindowFlags);

    ImGui::Text("Triangles:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(renderData.triangleCount).c_str());

    std::string windowDims =
        std::to_string(renderData.width) + 
        "x" +
        std::to_string(renderData.height);
    ImGui::Text("Window Dimensions: ");
    ImGui::Text("żaba Dimensions raz dwa: ");
    ImGui::SameLine();
    ImGui::Text(windowDims.c_str());

    ImGui::End();
}

void UserInterface::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::Cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
