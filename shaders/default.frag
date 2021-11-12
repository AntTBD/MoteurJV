//#version 330
//
//in vec4 vColor;// the input variable from the vertex shader (same name and same type)
//
//out vec4 FragColor;
//
//void main()
//{
//    FragColor = vColor;
//}

//#version 330 core
//out vec4 FragColor;
//uniform vec4 color;
//void main()
//{
//   FragColor = color;
//}

#version 330 core
precision mediump float;

in vec2 Frag_UV;
in vec4 Frag_Color;
layout (location = 0) out vec4 Out_Color;

void main()
{
    Out_Color = Frag_Color * vec4(1, 1, 0, 1); // For sanity, mask out the blue channel so we know the shader is being used.
}