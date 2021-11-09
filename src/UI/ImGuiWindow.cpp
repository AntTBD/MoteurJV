#include "ImGuiWindow.h"

ImGuiWindow::ImGuiWindow()
{}

ImGuiWindow::~ImGuiWindow()
{}

bool ImGuiWindow::begin(std::string name)
{
    return ImGui::Begin(name.c_str(), &show);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
}

void ImGuiWindow::show()
{
    begin("Base window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    end();
}
void ImGuiWindow::end()
{
    ImGui::End();
}