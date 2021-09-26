#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


class OpenGL3
{
public:
	OpenGL3();
	void create3dModels();


	void createTriangle();

	void draw3Dplan();

	void renderScene(void);


	GLuint* textureSceneRendered;
};

