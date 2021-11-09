#include "ImGuiUIWindow.h"

ImGuiUIWindow::ImGuiUIWindow(bool show): _show(show)
{}

ImGuiUIWindow::~ImGuiUIWindow()
{}

bool ImGuiUIWindow::begin(std::string name)
{
    return ImGui::Begin(name.c_str(), &this->_show);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
}

void ImGuiUIWindow::update()
{
    if(this->needShow())
    {
        if(this->begin("Base window"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }
        this->end();
    }
}
void ImGuiUIWindow::end()
{
    ImGui::End();
}

bool ImGuiUIWindow::needShow()
{
    return this->_show;
}

void ImGuiUIWindow::show()
{
    this->_show = true;
}

void ImGuiUIWindow::hide()
{
    this->_show = false;
}

void ImGuiUIWindow::toggle()
{
    this->_show = !this->_show;
}