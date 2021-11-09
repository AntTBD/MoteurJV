#include "ImGuiUIWindowRegistry.h"


ImGuiUIWindowRegistry::ImGuiUIWindowRegistry()
{}

ImGuiUIWindowRegistry::~ImGuiUIWindowRegistry()
{
    this->clear();
}

ImGuiUIWindowRegistry::ImGuiUIWindowEntry::ImGuiUIWindowEntry(ImGuiUIWindow* imGuiUIWindow) : imGuiUIWindow(imGuiUIWindow)
{
}
    
// ... Registry Accessors
void ImGuiUIWindowRegistry::add(ImGuiUIWindow* imGuiUIWindow)
{
    this->m_registry.push_back(ImGuiUIWindowRegistry::ImGuiUIWindowEntry(imGuiUIWindow));
}

void ImGuiUIWindowRegistry::update()
{
	for (auto entry : this->m_registry )
	{
		entry.imGuiUIWindow->update();
	}
}

void ImGuiUIWindowRegistry::clear()
{
	this->m_registry.clear();
}
