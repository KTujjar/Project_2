#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>

// Owns one compiled+linked GLSL shader program (vertex + fragment stage).
// Like Window, this manages a GPU resource (the program handle), so it's a
// class: create in the constructor, glDeleteProgram in the destructor.
class Shader {
public:
    // Load the two GLSL source files from disk, compile each stage, and link
    // them into a program. On compile/link failure, fetch the driver's info
    // log (glGetShaderInfoLog / glGetProgramInfoLog) and throw with it —
    // shader typos are runtime errors, and that log is your only clue.
    Shader(const std::string& vertex_path, const std::string& fragment_path);

    // Free the GPU program object (glDeleteProgram).
    ~Shader();

    // Make this program the active one for subsequent draw calls (glUseProgram).
    // Call before setting uniforms or drawing.
    void use() const;

    // Upload a 4x4 matrix uniform by name (e.g. "uMVP").
    // Look up the location with glGetUniformLocation, then glUniformMatrix4fv.
    void set_mat4(const std::string& name, const glm::mat4& value) const;

    // Upload a float uniform by name (e.g. "uPointSize").
    void set_float(const std::string& name, float value) const;

private:
    GLuint program;   // GL handle to the linked program (0 = invalid)

    // Helper: read an entire text file into a string (the GLSL source).
    // static because it doesn't touch any member state.
    static std::string read_file(const std::string& path);

    // Helper: compile one stage (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
    // from source, check GL_COMPILE_STATUS, throw with the info log on error.
    // Returns the shader object handle for linking.
    static GLuint compile_stage(GLenum type, const std::string& source);
};
