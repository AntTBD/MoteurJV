//#version 330
//
//layout (location = 0) in vec3 aPosition;// the position variable has attribute position 0
//layout (location = 1) in vec4 aColor;
//
//out vec4 vColor;// specify a color output to the fragment shader
//
//void main()
//{
//    vColor = aColor;
//    gl_Position = vec4(aPosition, 1.0);
//}

//#version 330 core
//layout (location = 0) in vec3 aPos;
//uniform float size;
//void main()
//{
//   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);
//}

#version 330 core
uniform mat4 ProjMtx;
in vec2 Position;
in vec2 UV;
in vec4 Color;
out vec2 Frag_UV;
out vec4 Frag_Color;
void main()
{
    Frag_UV = UV;
    Frag_Color = Color;
    gl_Position = ProjMtx * vec4(Position.xy,0,1);
}