#include "ImGuiWindowRegistry.h"


ImGuiWindowRegistry::ImGuiWindowRegistry()
{}

ImGuiWindowRegistry::~ImGuiWindowRegistry()
{}
    
// ... Registry Accessors
void ImGuiWindowRegistry::add(ImGuiWindow* imGuiWindow)
{
    this->m_registry.push_back(ImGuiWindowRegistry::ImGuiWindowEntry(imGuiWindow));
}

void ImGuiWindowRegistry::update()
{
	for (auto entry : this->m_registry )
	{
		entry.imGuiWindow->show();
	}
}

void ImGuiWindowRegistry::clear()
{
	this->m_registry.clear();
}
