#include "ImGuiUIWindowConsole.h"

ImGuiUIWindowConsole::ImGuiUIWindowConsole(bool show) : ImGuiUIWindow(show)
{
//	if (show)
//		this->show();
//	else
//		this->hide();
}

ImGuiUIWindowConsole::~ImGuiUIWindowConsole()
{}

void ImGuiUIWindowConsole::update()
{
    if(this->needShow())
    {

        // For the demo: add a debug button _BEFORE_ the normal log window contents
        // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
        // Most of the contents of the window will be added by the log.Draw() call.
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);

        /*if (this->begin("Console"))
		{
            if (ImGui::SmallButton("[Debug] Add 5 entries"))
            {
                static int counter = 0;
                const char* categories[3] = { "info", "warn", "error" };
                const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
                for (int n = 0; n < 5; n++)
                {
                    const char* category = categories[counter % IM_ARRAYSIZE(categories)];
                    const char* word = words[counter % IM_ARRAYSIZE(words)];
                    EngineManager::getInstance().console.log("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                               ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
                    counter++;
                }
            }

        }
		this->end();*/
        // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
        // /!\  same window if same name !
        EngineManager::getInstance().console.Draw("Console", &this->_show);
	}
}