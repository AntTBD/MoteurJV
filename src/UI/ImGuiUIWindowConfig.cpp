#include "ImGuiUIWindowConfig.h"

ImGuiUIWindowConfig::ImGuiUIWindowConfig(bool show) : ImGuiUIWindow(show)
{
//	if (show)
//		this->show();
//	else
//		this->hide();
}

ImGuiUIWindowConfig::~ImGuiUIWindowConfig()
{}

void ImGuiUIWindowConfig::update()
{
    if(this->needShow())
    {
		if (this->begin("Config"))
		{
			/// TODO complete config window interface
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
		}
		this->end();
	}
}