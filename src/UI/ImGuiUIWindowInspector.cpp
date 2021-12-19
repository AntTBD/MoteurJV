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
                    this->ShowPlaceholderObject((listOfObectsInScene.at(obj_i)->body->GetName() == nullptr ? "Object" : listOfObectsInScene.at(obj_i)->body->GetName()), obj_i);
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
        int i = 0;

        Vector3 objectPos = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetPosition();
        Vector3 objectVelocity = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetVelocity();
        Vector3 objectAngularVelocity = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetAngularVelocity();
        Vector3 objectOrientation = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetOrientation().ToEulerInDegrees();
        float objectMass = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetMass();
        Vector3 objectDimensions = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetDimensions();
        RigidBody::ShapeType objectShapeType = EngineManager::getInstance().getScene()->GetObject(uid)->body->GetShapeType();


        // ============================= Position =================================
        ImGui::PushID(i); // Use field index as identifier.
        //this->ShowVector3PlaceHolder(objectPos, uid, "Position");
        Vector3 newValuesPosition = this->ShowVector3PlaceHolder(objectPos, uid, "Position");
        if(newValuesPosition != objectPos){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetPosition(newValuesPosition);
        }
        ImGui::PopID();
        i++;

        // ============================= Orientation =================================
        ImGui::PushID(i); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid change during simulation
        //this->ShowVector3PlaceHolder(objectOrientation, uid, "Orientation");
        Vector3 newValuesOrientation = this->ShowVector3PlaceHolder(objectOrientation, uid, u8"Orientation °");
        if(newValuesOrientation != objectOrientation){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetOrientation(Quaternion::EulerInDegreesToQuaternion(newValuesOrientation));
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        i++;

        // ============================= Velocity =================================
        ImGui::PushID(i); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid change during simulation
        //this->ShowVector3PlaceHolder(objectVelocity, uid, "Velocity");
        Vector3 newValuesVelocity = this->ShowVector3PlaceHolder(objectVelocity, uid, "Velocity");
        if(newValuesVelocity != objectVelocity){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetVelocity(newValuesVelocity);
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        i++;

        // ============================= Angular Velocity =================================
        ImGui::PushID(i); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid change during simulation
        //this->ShowVector3PlaceHolder(objectAngularVelocity, uid, "Angular Velocity");
        Vector3 newValuesAngularVelocity = this->ShowVector3PlaceHolder(objectAngularVelocity, uid, "Angular Velocity");
        if(newValuesAngularVelocity != objectAngularVelocity){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetAngularVelocity(newValuesAngularVelocity);
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        i++;

        // ============================= Mass =================================
        ImGui::PushID(i); // Use field index as identifier.
        //this->ShowVector3PlaceHolder(objectMass, uid, "Position");
        float newValuesMass = this->ShowVector3PlaceHolder(objectMass, uid, "Mass");
        if(newValuesMass != objectMass){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetMass(newValuesMass);
        }
        ImGui::PopID();
        i++;

        // ============================= Dimensions =================================
        ImGui::PushID(i); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid change during simulation
        //this->ShowVector3PlaceHolder(objectDimensions, uid, "Dimensions");
        Vector3 newValuesDimensions = this->ShowVector3PlaceHolder(objectDimensions, uid, "Dimensions\nfrom center\nto exterior");
        if(newValuesDimensions != objectDimensions){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetDimensions(newValuesDimensions);
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        i++;

        // ============================= Shape =================================
        ImGui::PushID(i); // Use field index as identifier.
        ImGui::BeginDisabled(EngineManager::getInstance().getPhysicEngine()->isRunning()); // avoid change during simulation
        //this->ShowVector3PlaceHolder(objectShapeType, uid, "Shape");
        auto newValuesShapeType = this->ShowDropdownPlaceHolder<RigidBody::ShapeType>(objectShapeType, {"Sphere", "Cube", "Cylinder", "Plan"}, uid, "Shape");
        if(int(newValuesShapeType) != int(objectShapeType)){
            EngineManager::getInstance().getScene()->GetObject(uid)->body->SetShapeType(newValuesShapeType);
        }
        ImGui::EndDisabled();
        ImGui::PopID();
        i++;

        // =====================================================================
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

template<typename T>
T ImGuiUIWindowInspector::ShowDropdownPlaceHolder(T enumeration, std::vector<const char *> enumerationList, int uid, const char* type){

    static T _enum;
    static std::vector<const char *> enumList = {};
    enumList = enumerationList;
    _enum = enumeration;

    // Here we use a TreeNode to highlight on hover (we could use e.g. Selectable as well)
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
    ImGui::TreeNodeEx(type, flags, "%s", type);//_%d", uid);

    ImGui::TableSetColumnIndex(1);


    static const char* current_enum = NULL;
    current_enum = enumList.at(enumeration);
    ImGui::SetNextItemWidth(-FLT_MIN);
    if (ImGui::BeginCombo("", current_enum))
    {
        for(int i=0; i < enumList.size(); i++)
        {
            bool is_selected = (current_enum == enumList[i]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(enumList[i], is_selected)) {
                current_enum = enumList[i];
                _enum = (T) i;
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    ImGui::NextColumn();

    return _enum;
}