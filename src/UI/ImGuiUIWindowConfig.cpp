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
            ImGui::Text(u8"Application average %.3f ms/frame (%.1f FPS)",
                        1000.f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::Text(u8"Physique Engine dT %.3f ms",
                        1000.f * EngineManager::getInstance().getPhysicEngine()->dT);
		}
		this->end();
	}
}