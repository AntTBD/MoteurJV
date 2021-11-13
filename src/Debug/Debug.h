#ifndef Debug_H_
#define Debug_H_
#include "../ImGuiIncludes.h"

// pasted from imgui_demo and transform in class
//-----------------------------------------------------------------------------
// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
class AppLog
{
private:
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.

public:
    AppLog();

    void Clear();

    void log(const char* fmt, ...) IM_FMTARGS(2);

    void Draw(const char* title, bool* p_open = NULL);
};

static AppLog console = AppLog();
//-----------------------------------------------------------------------------


#endif // Debug_H_
