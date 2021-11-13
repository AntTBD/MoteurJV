#ifndef Debug_H_
#define Debug_H_
#include "../ImGuiIncludes.h"

enum DebugType{
    _log,           // do not write log
    _logSuccess,
    _logWarning,
    _logError       // do not write logError
};

// copied/pasted from imgui_demo and transform into a class + add colors for log error / warning / success
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
    ImVector<DebugType> LineDebugType;
    void log(DebugType type, const char* fmt,  va_list args) IM_FMTLIST(3);
    ImVec4 getColor(DebugType type);
public:
    AppLog();
    ~AppLog();

    void Clear();

    void log(const char* fmt, ...) IM_FMTARGS(2);
    void logSuccess(const char* fmt, ...) IM_FMTARGS(2);
    void logWarning(const char* fmt, ...) IM_FMTARGS(2);
    void logError(const char* fmt, ...) IM_FMTARGS(2);

    void Draw(const char* title, bool* p_open = NULL);
};

static AppLog console = AppLog();
//-----------------------------------------------------------------------------


#endif // Debug_H_
