#pragma once

#include <vector>
#include "ImGuiUIWindow.h"

class ImGuiUIWindowRegistry
{
private:
    struct ImGuiUIWindowEntry
	{
        ImGuiUIWindow* imGuiUIWindow;
        ImGuiUIWindowEntry(ImGuiUIWindow* imGuiUIWindow);

	};
	using Registry = std::vector<ImGuiUIWindowEntry>;
	Registry m_registry;
public:
    ImGuiUIWindowRegistry();
    ~ImGuiUIWindowRegistry();
    
	// ... Registry Accessors
	void add(ImGuiUIWindow* imGuiUIWindow);
	void update();
	void clear();
    
};