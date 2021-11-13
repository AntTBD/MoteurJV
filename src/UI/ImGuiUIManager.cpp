#include "ImGuiUIManager.h"

ImGuiUIManager::ImGuiUIManager(MainWindow* mainWindow)
{
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
#endif

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    /// TODO add docking
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    this->setStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mainWindow->getWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // set all imgui windows to the registry
    this->imGuiUIWindowRegistry = new ImGuiUIWindowRegistry();
    this->imGuiUIWindowRegistry->add(new ImGuiUIWindowConfig(true));
    this->imGuiUIWindowRegistry->add(new ImGuiUIWindowRender(true));
    this->imGuiUIWindowRegistry->add(new ImGuiUIWindowConsole(true));
    this->imGuiUIWindowRegistry->add(new ImGuiUIWindowInspector(true));
}

ImGuiUIManager::~ImGuiUIManager()
{
    // remove all windows
    this->imGuiUIWindowRegistry->clear();
    delete this->imGuiUIWindowRegistry;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiUIManager::setStyle()
{
    // Setup Dear ImGui style
    ImGui::StyleColorsDark(); // dark mode
    //ImGui::StyleColorsClassic(); // classic

    ImGuiIO& io = ImGui::GetIO();
    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    io.Fonts->AddFontDefault();

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    ImFont* font = io.Fonts->AddFontFromFileTTF( (std::string("../../fonts/") + FONT_ICON_FILE_NAME_FAS).c_str(), 10.0f, &icons_config, icons_ranges );
    IM_ASSERT(font != NULL);
    // use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid

}

/// <summary>
/// Update all windows of User Interface using ImGui
/// </summary>
void ImGuiUIManager::update()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ------------------------

    ImGui::ShowDemoWindow();
    this->imGuiUIWindowRegistry->update();
    // ------------------------

    // Rendering
    ImGui::Render();

    /// TODO add viewports
    /*ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }*/
}

void ImGuiUIManager::render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

template <class T>
T* ImGuiUIManager::FindWindow(){
    for(auto window : this->windows) {
        if(T *ptr = dynamic_cast<T*>(window))
            return ptr;
    }
    return nullptr;
}