#include "ImGuiUIWindowConsole.h"

ImGuiUIWindowConsole::ImGuiUIWindowConsole(bool show) : ImGuiUIWindow(show)
{
//	if (show)
//		this->show();
//	else
//		this->hide();
}

ImGuiUIWindowConsole::~ImGuiUIWindowConsole()
{}

void ImGuiUIWindowConsole::update()
{
    if(this->needShow())
    {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

        EngineManager::getInstance().console.Draw("Console", &this->_show);
	}
}