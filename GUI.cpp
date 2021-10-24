#include <iostream>
#include "GUI.h"

/// <summary>
/// Constructor (instenciate simulator and openGL)
/// </summary>
/// <param name="sim">Global simulator</param>
GUI::GUI(Simulator* sim)
{
    this->window = nullptr;

    this->show_config_window = true;
    this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    this->sim = sim;
    this->isSimulating = false;
    this->isThreadActive = false;

    this->opengl = new OpenGL3(this->sim);
}

/// <summary>
/// Init ImGUI, create window and set useful settings for OpenGL
/// </summary>
/// <returns>1 if GLFW error OU -1 if window error OU 0 if not errors</returns>
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

    // configure global opengl state to be used with 3D view mode
    glEnable(GL_DEPTH_TEST);

    this->opengl->InitFormes();

    return 0;
}

/// <summary>
/// Update User Interface with ImGui + 3D OpenGL render
/// </summary>
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


        // ---- Show config window to add particles to simulator and manage the simulation ----
        this->showConfigWindow();
        // -------------------------------
        //ImGui::ShowDemoWindow();


        // ------------------------
        // Show 3D our Render
        if (this->isSimulating) // pause the simulation while rendering and resume after render is done
        {
            Pause();
            this->render3D();
            Pause();
        }
        else
        {
            this->render3D();
        }
        // ------------------------

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(this->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->window);
    }
}

/// <summary>
/// Stop all (ImGUI + GLFW + OpenGL + window)
/// </summary>
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

/// <summary>
/// ImGui Window to add particles to simulator, start, pause and clear the simulation
/// </summary>
void GUI::showConfigWindow()
{
    if (this->show_config_window) {
        ImGui::Begin("Config Window", &this->show_config_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        {
            // Variable needed to make a particle
            static float px = 0.0f;
            static float py = 5.0f;
            static float pz = 0.0f;
            static float sx = 0.0f;
            static float sy = 0.0f;
            static float sz = 0.0f;
            static float mass = 10.0f;

            // Associated buttons
            ImGui::Text("Initial Position");
            ImGui::InputFloat("pos x", &px);
            ImGui::InputFloat("pos y", &py);
            ImGui::InputFloat("pos z", &pz);
            ImGui::Text("Initial Speed");
            ImGui::InputFloat("speed x", &sx);
            ImGui::InputFloat("speed y", &sy);
            ImGui::InputFloat("speed z", &sz);
            ImGui::InputFloat("mass", &mass);

            // Dropdown de presets (from https://github.com/ocornut/imgui/issues/1658#issuecomment-774676329)
            {
                ImGui::Text("Choose an object");
                struct { const char* label; Vector3 initSpeed; float masse; } projectiles[] = {
                    {"Balles",          Vector3(10,     10, 0),     1.0f},
                    {"Boulets",         Vector3(5,      0,  0),     5.0f},
                    {"Laser",           Vector3(100,    10, 0),     0.1f},
                    {"Boule de feu",    Vector3(5,      5,  0),     1.5f},
                };
                static const char* current_projectile = NULL;

                if (ImGui::BeginCombo("Preset", current_projectile)) // The second parameter is the label previewed before opening the combo.
                {
                    for (int n = 0; n < IM_ARRAYSIZE(projectiles); n++)
                    {
                        bool is_selected = (current_projectile == projectiles[n].label); // You can store your selection however you want, outside or inside your objects
                        if (ImGui::Selectable(projectiles[n].label, is_selected)) {
                            current_projectile = projectiles[n].label;
                            sx = projectiles[n].initSpeed.GetX();
                            sy = projectiles[n].initSpeed.GetY();
                            sz = projectiles[n].initSpeed.GetZ();
                            mass = projectiles[n].masse;
                        }
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                    }
                    ImGui::EndCombo();
                }
            }

            if (ImGui::Button("Add")) // Add new particle to the simulator with the chosen parameters
            {
                if (!this->isSimulating && !this->isThreadActive) //Can only add if simulation is not running
                {
                    if (mass == 0) mass = 0.000001f;
                    Particle *p = new Particle(Vector3(px, py, pz), Vector3(sx, sy, sz), 1.0f/mass);
                    this->sim->AddParticle(p);
                    std::cout << "New particle added -> " << *p << std::endl;
                }
                else
                {
                    std::cout << "Simulation in progress..." << std::endl;
                }

            }

            if (ImGui::Button("Particles")) // Print all particles in the console
            {
                if (!this->isSimulating && !this->isThreadActive) // Only if simulation not running
                {
                    this->sim->Print();
                }
                else
                {
                    std::cout << "Simulation in progress..." << std::endl;
                }
            }

            if (ImGui::Button("Start Simulation")) // Start the simulation
            {
                if (!this->sim->GetParticles().empty())
                {
                    if (!this->isSimulating && !this->isThreadActive) // Can start only if not running already
                    {
                        this->simThread = std::thread{ &GUI::Simulate, this }; // Make new thread running the Simulate() function
                    }
                    else
                    {
                        std::cout << "Simulation in progress..." << std::endl;
                    }
                }
                else
                {
                    std::cout << "No particles" << std::endl;
                }

            }

            // Pause and resume simulation
            if (ImGui::Button("Pause"))
            {
                Pause();

            }

            // Stop simulation and clear particles
            if (ImGui::Button("Clear"))
            {
                Clear();
            }
            ImGui::Spacing();
            ImGui::TextWrapped(u8"HowToPlay ?");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Choisir une velocité de départ + une masse.");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Ajouter des particules à la position que vous souhaitez sur l'axe Z avec le click droit de la souris.");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Start Simulation.");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Bouger la première particule ajoutée via un click gauche sur la souris.");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Toutes les autres particules seront relié à cette première particule.");
            ImGui::Spacing();
            ImGui::TextWrapped(u8"Caméra Tips :");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Zoomer grâce à la molette de la souris");
            ImGui::Bullet(); ImGui::TextWrapped(u8"Changer l'orientation de la camera en maintenant appuyé la molette et en déplaçant la souris.");

            // ------------ Check mouse click & add particle -----------------------------
            ImGuiIO& io = ImGui::GetIO();
            Vector3 offsetPosition = Vector3(-(float)io.DisplaySize.x / 2.0f, (float)io.DisplaySize.y, 0);
            float ratio = 4.0f;
            if (ImGui::IsMouseClicked(1))// right click
            {
                if (mass == 0) mass = 0.000001f;
                Vector3 pos = Vector3((offsetPosition.GetX() + (float)io.MousePos.x) / ratio, (offsetPosition.GetY() - (float)io.MousePos.y) / ratio, 0);
                std::cout << pos << std::endl;
                Particle* p = new Particle(pos, Vector3(sx, sy, sz), 1.0f / mass);
                this->sim->AddParticle(p);
                std::cout << "Add particle " << *p << std::endl;
            }

            // ------------ Check mouse click & move first particle -----------------------------
            if (this->isSimulating && IsMouseOnWidgets() == false && ImGui::IsMouseDown(0)) // left click down
            {
                Vector3 pos = Vector3((offsetPosition.GetX() + (float)io.MousePos.x) / ratio, (offsetPosition.GetY() - (float)io.MousePos.y) / ratio, 0);

                Particle* p = this->sim->GetParticle(0);
                if (p != nullptr) p->SetPosition(pos);
            }

            ImGui::Spacing();
            ImGui::TextWrapped(u8"Simulator DeltaTime: %.2f ms", this->sim->dT * 1000.0f);
        }
        ImGui::End();
    }
}

bool GUI::IsMouseOnWidgets()
{
    return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);
}

/// <summary>
/// Call 3D render update
/// </summary>
void GUI::render3D()
{
    this->opengl->update();
}

/// <summary>
/// Update all particles of the simulator every 16.6ms
/// </summary>
void GUI::Simulate()
{
    float deltaTimeTarget = 16.6f;
    float deltaTime = 0.0f;
    this->isSimulating = true;
    this->isThreadActive = true;
    
    auto time = std::chrono::high_resolution_clock::now();

    while (this->isThreadActive)
    {
        auto now = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> deltaTimeDuration = now - time;
        deltaTime += deltaTimeDuration.count();
        time = now;
        
        if (deltaTime >= deltaTimeTarget || sim->isUpdated())
        {
            sim->Update(deltaTime / 1000.0f);
            deltaTime = 0.0f;
        }
    }

}

/// <summary>
/// Remove particles from the simulator and finish thread if possible
/// </summary>
void GUI::Clear()
{
    if (this->isThreadActive)
    {
        this->isSimulating = false;
        this->isThreadActive = false;
        if (this->simThread.joinable())
        {
            this->simThread.join();
        }
        std::cout << "Particles cleared" << std::endl;
    }
    sim->ClearParticles();
    this->sim->Resume(); // Set simulation back to unpaused if we cleared while it was paused
}

/// <summary>
/// Pause or resume simulation
/// </summary>
void GUI::Pause()
{
    if (this->isThreadActive)
    {
        if (this->isSimulating)
        {
            this->sim->Pause();
            this->isSimulating = false;
        }
        else
        {
            this->sim->Resume();
            this->isSimulating = true;
        }
        
    }
}