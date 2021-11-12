#pragma once


#include "../myIncludes.h"

// string
#include <cstdio>
#include <string>

// generic class for ImGui Windows
class ImGuiUIWindow
{
public:
    ImGuiUIWindow(bool show = true);
	~ImGuiUIWindow();
    virtual void update();

protected:

	bool begin(std::string name);
	void end();

    bool needShow();
    void show();
    void hide();
    void toggle();

    bool _show;

};