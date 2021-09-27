#include <iostream>
#include "GUI.h"

GUI::GUI(Simulator* sim)
{
   // this->init();
    this->window = nullptr;


    this->show_config_window = true;
    this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    this->sim = sim;
    this->isSimulating = false;
    this->isThreadActive = false;

    this->opengl = new OpenGL3(this->sim);
}

int GUI::init()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return 1;
    }
    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    this->window = glfwCreateWindow(1280, 720, "Moteur physique de Jeux Video", NULL, NULL);
    if (!this->window) {
        fprintf(stderr, "Failed to create window with graphics context\n");
        return -1;
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

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

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return 0;
}


void GUI::update()
{

    // Main loop
    while (!glfwWindowShouldClose(this->window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // ---- Show config window ----
        this->showConfigWindow();
        // -------------------------------

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);


        // ---- Show 3d Render ----
        this->render3D();
        // ------------------------

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->window);
    }
}

void GUI::end()
{

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (this->simThread.joinable())
    {
        this->simThread.join();
    }

    glfwDestroyWindow(this->window);
    glfwTerminate();
}

void GUI::showConfigWindow()
{
    if (this->show_config_window) {
        ImGui::Begin("Config Window", &this->show_config_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        {
            static float px = 0.0f;
            static float py = 0.1f;
            static float pz = 0.0f;
            static float sx = 0.0f;
            static float sy = 0.0f;
            static float sz = 0.0f;
            static float invMass = 1.0f;
            static float gravityFactor = 1.0f;

            ImGui::Text("Initial Position");
            ImGui::InputFloat("pos x", &px);
            ImGui::InputFloat("pos y", &py);
            ImGui::InputFloat("pos z", &pz);
            ImGui::Text("Initial Speed");
            ImGui::InputFloat("speed x", &sx);
            ImGui::InputFloat("speed y", &sy);
            ImGui::InputFloat("speed z", &sz);
            ImGui::InputFloat("inv mass", &invMass);
            ImGui::InputFloat("gravity factor", &gravityFactor);

            if (ImGui::Button("Add"))
            {
                if (!this->isSimulating && !this->isThreadActive)
                {
                    Particle p = Particle(Vector3(px, py, pz), Vector3(sx, sy, sz), invMass, gravityFactor);
                    this->sim->AddParticle(p);
                    std::cout << "New particle added -> " << p << std::endl;
                }
                else
                {
                    std::cout << "Simulation in progress..." << std::endl;
                }

            }

            if (ImGui::Button("Particles"))
            {
                if (!this->isSimulating && !this->isThreadActive)
                {
                    this->sim->Print();
                }
                else
                {
                    std::cout << "Simulation in progress..." << std::endl;
                }
            }

            if (ImGui::Button("Start Simulation"))
            {
                if (!this->isSimulating && !this->isThreadActive)
                {
                    this->simThread = std::thread{ &GUI::Simulate, this };
                }
                else
                {
                    std::cout << "Simulation in progress..." << std::endl;
                }
            }

            if (ImGui::Button("StopSim"))
            {
                this->isSimulating = false;
                Clear();
                std::cout << "Particles cleared" << std::endl;
                
            }


        }
        ImGui::End();
    }
}

void GUI::render3D()
{
    this->opengl->update();
}

void GUI::Simulate()
{
    int deltaTime = 20;
    this->isSimulating = true;
    this->isThreadActive = true;
    while (this->isSimulating)
    {
        this->isSimulating = sim->Update(deltaTime/1000.0f);
        std::this_thread::sleep_for(std::chrono::milliseconds(deltaTime));
    }

}

void GUI::Clear()
{
    if (!this->isSimulating)
    {
        sim->ClearParticles();
        this->simThread.join();
        this->isThreadActive = false;
    }
}