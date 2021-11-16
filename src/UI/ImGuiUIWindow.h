#ifndef ImGuiUIWindow_H_
#define ImGuiUIWindow_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"

// string
#include <cstdio>
#include <string>


// generic class for ImGui Windows
class ImGuiUIWindow
{
public:
    ImGuiUIWindow(bool show = true);
	virtual ~ImGuiUIWindow();
    virtual void update();

protected:

	bool begin(std::string name);
	void end();

    bool needShow();
    void show();
    void hide();
    void toggle();

    bool _show;

    void HelpMarker(const char* desc);

};


#endif // ImGuiUIWindow_H_