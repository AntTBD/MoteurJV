#pragma once

#include "../UI/MainWindow.h"

class InputManager {

public:
    InputManager();
    ~InputManager();

    void update(MainWindow* mainWindow);
};
