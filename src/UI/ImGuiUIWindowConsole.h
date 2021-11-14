#ifndef ImGuiUIWindowConsole_H_
#define ImGuiUIWindowConsole_H_
#include "../ClassIncludes.h"

#include "ImGuiUIWindow.h"
#include "../EngineManager.h"


class ImGuiUIWindowConsole : public ImGuiUIWindow {
private:
public:
    ImGuiUIWindowConsole(bool show = true);
    ~ImGuiUIWindowConsole();

    void update() override;
};

#endif // ImGuiUIWindowConsole_H_