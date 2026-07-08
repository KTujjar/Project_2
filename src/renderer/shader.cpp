#include <renderer/shader.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
#include <sstream>

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path){
    std::string vertex_source = read_file(vertex_path);
    std::string fragment_source = read_file(fragment_path);
     
    GLuint vs = compile_stage(GL_VERTEX_SHADER, vertex_source);
    GLuint fs = compile_stage(GL_FRAGMENT_SHADER, fragment_source);

    program = glCreateProgram();

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    
    glLinkProgram(program);

    GLint ok;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if(!ok){
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        throw std::runtime_error(std::string("Shader link failed: ") + log);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader(){
    glDeleteProgram(program);
}


void Shader::use() const{
    glUseProgram(program);
}

void Shader::set_mat4(const std::string& name, const glm::mat4& value) const{
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_float(const std::string& name, float value) const{
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

std::string Shader::read_file(const std::string& path){
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("could not open shader file: " + path);
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compile_stage(GLenum type, const std::string& source){
    GLuint s = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if(!ok){
        char log[1024];
        glGetShaderInfoLog(s, sizeof(log), nullptr, log);
        throw std::runtime_error(std::string("Shader compile failed: ") + log);
    }
    return s;
}
