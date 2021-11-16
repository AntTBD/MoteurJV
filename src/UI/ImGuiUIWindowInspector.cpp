#include "ImGuiUIWindowInspector.h"

ImGuiUIWindowInspector::ImGuiUIWindowInspector(bool show) : ImGuiUIWindow(show)
{
//	if (show)
//		this->show();
//	else
//		this->hide();
}

ImGuiUIWindowInspector::~ImGuiUIWindowInspector()
{}

void ImGuiUIWindowInspector::update()
{
    if(this->needShow())
    {
		if (this->begin("Inspector"))
		{
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            if (ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable))
            {
                auto listOfObectsInScene = EngineManager::getInstance().getScene()->getObjectsByCopy();
                // Iterate placeholder objects (all the same data)
                for (int obj_i = 0; obj_i < listOfObectsInScene.size(); obj_i++)
                {
                    this->ShowPlaceholderObject("Object", obj_i);
                    //ImGui::Separator();
                }
                ImGui::EndTable();
            }
            ImGui::PopStyleVar();
		}
		this->end();
	}
}

void ImGuiUIWindowInspector::ShowPlaceholderObject(const char* prefix, int uid)
{
    // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
    ImGui::PushID(uid);

    // Text and Tree nodes are less high than framed widgets, using AlignTextToFramePadding() we add vertical spacing to make the tree lines equal high.
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
    ImGui::TableSetColumnIndex(1);
    //ImGui::Text("my sailor is rich");

    if (node_open)
    {

        Vector3 objectPos = EngineManager::getInstance().getScene()->GetObject(uid)->GetPosition();
        Vector3 objectSpeed = EngineManager::getInstance().getScene()->GetObject(uid)->GetSpeed();
        float objectMass = 1.f/EngineManager::getInstance().getScene()->GetObject(uid)->GetinvMass();


        ImGui::PushID(0); // Use field index as identifier.
        //this->ShowVector3PlaceHolder(objectPos, uid, "Position");
        Vector3 newValuesPosition = this->ShowVector3PlaceHolder(objectPos, uid, "Position");
        if(newValuesPosition.GetX() != objectPos.GetX() || newValuesPosition.GetY() != objectPos.GetY() || newValuesPosition.GetZ() != objectPos.GetZ()){
            EngineManager::getInstance().getScene()->GetObject(uid)->SetPosition(newValuesPosition);
        }
        ImGui::PopID();

        ImGui::PushID(1); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid create multiple simulation
        //this->ShowVector3PlaceHolder(objectSpeed, uid, "Velocity");
        Vector3 newValuesVelocity = this->ShowVector3PlaceHolder(objectSpeed, uid, "Velocity");
        if(newValuesVelocity.GetX() != objectSpeed.GetX() || newValuesVelocity.GetY() != objectSpeed.GetY() || newValuesVelocity.GetZ() != objectSpeed.GetZ()){
            EngineManager::getInstance().getScene()->GetObject(uid)->SetPosition(newValuesVelocity);
        }
        ImGui::EndDisabled();
        ImGui::PopID();


        ImGui::PushID(2); // Use field index as identifier.
        //this->ShowVector3PlaceHolder(objectPos, uid, "Position");
        float newValuesMass = this->ShowVector3PlaceHolder(objectMass, uid, "Mass");
        newValuesMass==0 ? newValuesMass = 0.00000000001 : newValuesMass=newValuesMass; // hard code to avoide invMass = 1/0 = inf
        if(newValuesMass != objectMass){
            EngineManager::getInstance().getScene()->GetObject(uid)->SetInvMass(1.f/newValuesMass);
        }
        ImGui::PopID();

        ImGui::TreePop();
    }
    ImGui::PopID();

}

Vector3 ImGuiUIWindowInspector::ShowVector3PlaceHolder(Vector3 vector3, int uid, const char* type)
{
    static float vx = 0.0f;
    static float vy = 0.0f;
    static float vz = 0.0f;

    vx = vector3.GetX();
    vy = vector3.GetY();
    vz = vector3.GetZ();
    
    auto spacing = ImGui::GetStyle().ItemInnerSpacing.x;

    // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx(type, flags, "%s", type);//_%d", uid);
    ImGui::SameLine(0.0f, spacing);
    this->HelpMarker("(x, y, z)");

    ImGui::TableSetColumnIndex(1);

    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::PushItemWidth((ImGui::GetColumnWidth(1)-2*spacing) / 3.f);
    ImGui::DragFloat("##vx", &vx, 0.1f);

    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::PushItemWidth((ImGui::GetColumnWidth(1)-2*spacing) / 3.f);
    ImGui::SameLine(0.0f, spacing);
    ImGui::DragFloat("##vy", &vy, 0.1f);

    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::PushItemWidth((ImGui::GetColumnWidth(1)-2*spacing) / 3.f);
    ImGui::SameLine(0.0f, spacing);
    ImGui::DragFloat("##vz", &vz, 0.1f);

//                ImGui::InputFloat("pos x", &px);
//                ImGui::InputFloat("pos y", &py);
//                ImGui::InputFloat("pos z", &pz);

    ImGui::NextColumn();

    return Vector3(vx, vy, vz);
}

float ImGuiUIWindowInspector::ShowVector3PlaceHolder(float val, int uid, const char* type)
{
    static float v = 0.0f;

    v = val;

    // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx(type, flags, "%s", type);//_%d", uid);

    ImGui::TableSetColumnIndex(1);

    auto spacing = ImGui::GetStyle().ItemInnerSpacing.x;

    ImGui::SetNextItemWidth(-FLT_MIN);
    ImGui::DragFloat("##vx", &v, 0.1f);

    ImGui::NextColumn();

    return v;
}