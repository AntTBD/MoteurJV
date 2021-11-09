#pragma once

#include <vector>
#include "ImGuiWindow.h"

class ImGuiWindowRegistry
{
private:
    struct ImGuiWindowEntry
	{
		ImGuiWindow* imGuiWindow;
		ImGuiWindowEntry(ImGuiWindow* imGuiWindow);

	};
	using Registry = std::vector<ImGuiWindowEntry>;
	Registry m_registry;
public:
    ImGuiWindowRegistry();
    ~ImGuiWindowRegistry();
    
	// ... Registry Accessors
	void add(ImGuiWindow* imGuiWindow);
	void update();
	void clear();
    
}