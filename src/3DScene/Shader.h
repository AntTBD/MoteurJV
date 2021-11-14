#ifndef Shader_H_
#define Shader_H_
#include "../ImGuiIncludes.h"
#include "../ClassIncludes.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// from Learn OpenGL
// https://learnopengl.com/Getting-started/Shaders
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
// add set Vec3 + Mat4 functions
#include "../../Vector3.h"

class Shader {
public:
    // the program ID
    GLuint ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    ~Shader();
    // use/activate the shader
    void use();
    void unUse();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, const Vector3& vector3) const;        // +
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;


private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif // Shader_H_