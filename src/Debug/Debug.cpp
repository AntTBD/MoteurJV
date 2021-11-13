#include "Debug.h"


AppLog::AppLog()
{
    //Buf = new ImGuiTextBuffer();
    this->AutoScroll = true;
    this->Clear();
}

AppLog::~AppLog() {
    this->Clear();
}

void AppLog::Clear()
{
    this->Buf.clear();
    this->LineOffsets.clear();
    this->LineOffsets.push_back(0);
    this->LineDebugType.clear();
}

void AppLog::log(DebugType type, const char* fmt,  va_list args) IM_FMTLIST(3)
{
    int old_size = this->Buf.size();
    this->Buf.appendfv(fmt, args);
    for (int new_size = this->Buf.size(); old_size < new_size; old_size++)
        if (this->Buf[old_size] == '\n') {
            this->LineOffsets.push_back(old_size + 1);
            this->LineDebugType.push_back(type);
        }
}

void AppLog::Draw(const char* title, bool* p_open)
{
    if (!ImGui::Begin(title, p_open))
    {
        ImGui::End();
        return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &this->AutoScroll);
        ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Remove all logs");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    if (ImGui::IsItemHovered())
        ImGui::SetTooltip("Copy all logs");
    ImGui::SameLine();
    this->Filter.Draw("Filter", -100.0f);

    ImGui::Separator();
    ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    if (clear)
        Clear();
    if (copy)
        ImGui::LogToClipboard();

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    const char* buf = this->Buf.begin();
    const char* buf_end = this->Buf.end();
    if (this->Filter.IsActive())
    {
        // In this example we don't use the clipper when Filter is enabled.
        // This is because we don't have a random access on the result on our filter.
        // A real application processing logs with ten of thousands of entries may want to store the result of
        // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
        for (int line_no = 0; line_no < this->LineOffsets.Size; line_no++)
        {
            const char* line_start = buf + this->LineOffsets[line_no];
            const char* line_end = (line_no + 1 < this->LineOffsets.Size) ? (buf + this->LineOffsets[line_no + 1] - 1) : buf_end;
            if (this->Filter.PassFilter(line_start, line_end)) {
                bool has_color = false;
                if (line_no < this->LineDebugType.size()){
                    if(this->LineDebugType[line_no] != DebugType::_log){
                        ImGui::PushStyleColor(ImGuiCol_Text, this->getColor(this->LineDebugType[line_no]));
                        has_color = true;
                    }
                }
                ImGui::TextUnformatted(line_start, line_end);
                if (has_color)
                    ImGui::PopStyleColor();
            }
        }
    }
    else
    {
        // The simplest and easy way to display the entire buffer:
        //   ImGui::TextUnformatted(buf_begin, buf_end);
        // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
        // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
        // within the visible area.
        // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
        // on your side is recommended. Using ImGuiListClipper requires
        // - A) random access into your data
        // - B) items all being the  same height,
        // both of which we can handle since we an array pointing to the beginning of each line of text.
        // When using the filter (in the block of code above) we don't have random access into the data to display
        // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
        // it possible (and would be recommended if you want to search through tens of thousands of entries).
        ImGuiListClipper clipper;
        clipper.Begin(this->LineOffsets.Size);
        while (clipper.Step())
        {
            for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
            {
                const char* line_start = buf + this->LineOffsets[line_no];
                const char* line_end = (line_no + 1 < this->LineOffsets.Size) ? (buf + this->LineOffsets[line_no + 1] - 1) : buf_end;
                bool has_color = false;
                if (line_no < this->LineDebugType.size()){
                    if(this->LineDebugType[line_no] != DebugType::_log){
                        ImGui::PushStyleColor(ImGuiCol_Text, this->getColor(this->LineDebugType[line_no]));
                        has_color = true;
                    }
                }
                ImGui::TextUnformatted(line_start, line_end);
                if (has_color)
                    ImGui::PopStyleColor();
            }
        }
        clipper.End();
    }
    ImGui::PopStyleVar();

    if (this->AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}

void AppLog::log(const char *fmt, ...) {
    va_list args;
            va_start(args, fmt);
    this->log(DebugType::_log,fmt, args);
            va_end(args);
}

void AppLog::logSuccess(const char *fmt, ...) {
    va_list args;
            va_start(args, fmt);
    this->log(DebugType::_logSuccess,fmt, args);
            va_end(args);

}

void AppLog::logWarning(const char *fmt, ...) {
    va_list args;
            va_start(args, fmt);
    this->log(DebugType::_logWarning,fmt, args);
            va_end(args);
}

void AppLog::logError(const char *fmt, ...) {
    va_list args;
            va_start(args, fmt);
    this->log(DebugType::_logError,fmt, args);
            va_end(args);
}

ImVec4 AppLog::getColor(DebugType type) {
    ImVec4 color;
    switch (type) {
        case DebugType::_log:
            color = ImVec4(*ImGui::GetStyle().Colors);
            break;
        case DebugType::_logSuccess:
            color = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
            break;
        case DebugType::_logWarning:
            color = ImVec4(0.87f, 0.62f, 0.0f, 1.0f);
            break;
        case DebugType::_logError:
            color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
            break;
    }
    return color;
}
