#ifndef ImGuiUIWindowConfig_H_
#define ImGuiUIWindowConfig_H_
#include "../ClassIncludes.h"

#include "ImGuiUIWindow.h"
#include "../EngineManager.h"


class ImGuiUIWindowConfig : public ImGuiUIWindow {
public:
    ImGuiUIWindowConfig(bool show = true);
    ~ImGuiUIWindowConfig();

    void update() override;
};

#endif // ImGuiUIWindowConfig_H_