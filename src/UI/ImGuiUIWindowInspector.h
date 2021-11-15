#ifndef ImGuiUIWindowInspector_H_
#define ImGuiUIWindowInspector_H_
#include "../ClassIncludes.h"

#include "ImGuiUIWindow.h"
#include "../EngineManager.h"

// adaptation de ShowExampleAppPropertyEditor from imgui_demo.cpp


class ImGuiUIWindowInspector : public ImGuiUIWindow {
private:
public:
    ImGuiUIWindowInspector(bool show = true);
    ~ImGuiUIWindowInspector();

    void update() override;


    void ShowPlaceholderObject(const char* prefix, int uid);
    Vector3 ShowVector3PlaceHolder(Vector3 vector3, int uid, const char* type);
    float ShowVector3PlaceHolder(float val, int uid, const char* type);
};

#endif // ImGuiUIWindowInspector_H_