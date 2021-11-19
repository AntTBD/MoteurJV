#include "ImGuiUIWindowRender.h"

ImGuiUIWindowRender::ImGuiUIWindowRender(bool show): ImGuiUIWindow(show)
{
    //add shaders
    //this->shader = new Shader("./data/shaders/default.vert", "./data/shaders/default.frag");


    // first framebuffer configuration
    this->framebuffer = 0;
    glGenFramebuffers(1, &this->framebuffer);
    glGenTextures(1, &this->textureColorbuffer);

    // variables
    this->play = false;
    this->pause = false;
}

ImGuiUIWindowRender::~ImGuiUIWindowRender()
{
    /// TODO: delete buffers
    //delete this->shader;
    glDeleteFramebuffers(1, &this->framebuffer);
    glDeleteTextures(1, &this->textureColorbuffer);
}

void ImGuiUIWindowRender::update()
{
    if(this->needShow())
    {
		if (this->begin("Render")) {
            ImGuiIO &io = ImGui::GetIO();
            // Top buttons
            {
                this->HelpMarker(
                        u8"- Click (Mouse left) on this window to interact wind objects.\n"
                        "- Bouger la première particule ajoutée (Mouse right).\n"
                        "Toutes les autres particules seront relié à cette première particule.\n"
                        "Zoomer grâce à la molette de la souris\n"
                        "Changer l'orientation de la camera en maintenant appuyé la molette et en déplaçant la souris.");

                ImGui::SetWindowFontScale(1.2);
                // espace pour centrer les boutons
                int nbrButtons = 3;
                auto windowWidth = ImGui::GetWindowSize().x;
                auto spacing = ImGui::GetStyle().ItemInnerSpacing.x;
                auto buttonSize = ImVec2(ImGui::GetStyle().ItemInnerSpacing.y + ImGui::GetFontSize(),
                                         ImGui::GetStyle().ItemInnerSpacing.y + ImGui::GetFontSize());
                ImGui::SameLine(windowWidth / 2.f - spacing / 2.f * (nbrButtons - 1) - buttonSize.x * nbrButtons / 2.f);
                // Start button
                ImGui::BeginDisabled(this->play); // avoid create multiple simulation
                if (ImGui::Button(ICON_FA_PLAY, buttonSize)) {
                    // Start the simulation
                    EngineManager::getInstance().getPhysicEngine()->startSimulation();
                    this->play = true;
                    this->pause = false;
                }
                ImGui::EndDisabled();
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Start");

                // Pause button
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::Button(ICON_FA_PAUSE, buttonSize)) {
                    // Pause the simulation
                    EngineManager::getInstance().getPhysicEngine()->togglePause();
                    this->pause = !pause;
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip((this->pause ? "Resume": "Pause"));

                // Stop button
                ImGui::SameLine(0.0f, spacing);
                if (ImGui::Button(ICON_FA_STOP, buttonSize)) {
                    // Stop the simulation
                    EngineManager::getInstance().getPhysicEngine()->stop();
                    this->play = false;
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Stop");

                ImGui::SetWindowFontScale(1.f);
            }

            // Using a Child allow to fill all the space of the window
            ImGui::BeginChild("GameRender");
            {
                // mouse drag/scroll rotate/zoom scene
                if (ImGui::IsWindowHovered()) {
                    // mouse wheel zoom
                    if (io.MouseWheel != 0)
                        EngineManager::getInstance().getScene()->getCamera()->SetDistance(EngineManager::getInstance().getScene()->getCamera()->GetDistance() + (float) io.MouseWheel * 10.f);
                    //move cam on wheel clicked
                    if (ImGui::IsMouseDown(2)) {
                        EngineManager::getInstance().getScene()->getCamera()->Add(0, -(float) io.MouseDelta.y, (float) io.MouseDelta.x); // set default position
                    }
                }
                // Get the size of the child (i.e. the whole draw size of the windows).
                ImVec2 wsize = ImGui::GetWindowSize();

                // resize cam
                if (EngineManager::getInstance().getScene()->getCamera()->getWidth() != wsize.x || EngineManager::getInstance().getScene()->getCamera()->getHeight() != wsize.y) {
                    this->newSize(wsize.x, wsize.y);
                }

                this->checkToAddParticles();

                this->render3D();

                // Because I use the texture from OpenGL, I need to invert the V from the UV.
                ImGui::Image((ImTextureID) this->textureColorbuffer, wsize, ImVec2(0, 1), ImVec2(1, 0));
            }
            ImGui::EndChild();


		}
		this->end();
	}
}

void ImGuiUIWindowRender::newSize(float width, float height){

    EngineManager::getInstance().getScene()->getCamera()->setSize(width, height);
    // https://learnopengl.com/code_viewer_gh.php?code=src/4.advanced_opengl/5.1.framebuffers/framebuffers.cpp
    // framebuffer configuration
    // -------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
    glEnable(GL_DEPTH_TEST);
    // create a color attachment texture
    glBindTexture(GL_TEXTURE_2D, this->textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->textureColorbuffer, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    /*unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glDeleteBuffers(1, &rbo);
    */
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ImGuiUIWindowRender::render3D() {

//https://learnopengl.com/Advanced-OpenGL/Framebuffers
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    //this->shader->use();

    EngineManager::getInstance().getScene()->draw();

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    //this->shader->unUse();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ImGuiUIWindowRender::checkToAddParticles()
{
    // Get the size of the child (i.e. the whole draw size of the windows).
    ImVec2 wsize = ImGui::GetWindowSize();
    ImGuiIO &io = ImGui::GetIO();

    ImVec2 mousePositionInChild(io.MousePos.x - ImGui::GetWindowPos().x,io.MousePos.y - ImGui::GetWindowPos().y);

    static float px = 0.0f;
    static float py = 5.0f;
    static float pz = 0.0f;
    static float sx = 0.0f;
    static float sy = 0.0f;
    static float sz = 0.0f;
    static float mass = 10.0f;

    // -------------------- Check mouse click & add particle if not in simulation -----------------------------
    Vector3 offsetPosition = Vector3(-(float)wsize.x / 2.0f, (float)wsize.y, 0);
    float ratio = 4.0f;
    if (this->play == false && ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))// right click if not in simulation
    {
        Vector3 pos = Vector3((offsetPosition.GetX() + (float)mousePositionInChild.x) / ratio, (offsetPosition.GetY() - (float)mousePositionInChild.y) / ratio, 0);
        std::cout << pos << std::endl;
        auto obj = new RigidBody(mass, pos);
        EngineManager::getInstance().getScene()->addObject(*obj);
        //std::cout << "Add particle " << *p << std::endl;
        EngineManager::getInstance().console.logSuccess("Add particle %d: %s\n",EngineManager::getInstance().getScene()->getObjectsByCopy().size()-1,obj->toString().c_str());
    }

    // --------------------------- Check mouse click & move first particle -------------------------------------
    if (this->play && !this->pause && ImGui::IsWindowFocused() && ImGui::IsMouseDown(1)) // right click down
    {
        Vector3 pos = Vector3((offsetPosition.GetX() + (float)mousePositionInChild.x) / ratio, (offsetPosition.GetY() - (float)mousePositionInChild.y) / ratio, 0);

        auto obj = EngineManager::getInstance().getScene()->GetObject(0);
        if (obj != nullptr) {

            // d = xa - xb
            Vector3 d = (obj->GetPosition() - pos);
            // f = - k * ( |d| - l0) * d.normalized
            obj->AddForce(-1 * d.Magnitude() * d.Normalized() * (1.0f / obj->GetInvMass()));
            //p->SetPosition(pos);
        }
    }
}