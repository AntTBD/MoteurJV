#ifndef InputManager_H_
#define InputManager_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"

#include "../UI/MainWindow.h"
#include "../Demos/CarCollision.h"
#include "../Demos/Blob.h"

class InputManager {

public:
    InputManager();
    ~InputManager();

    void update(MainWindow* mainWindow);
};

#endif // InputManager_H_