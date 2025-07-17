#pragma once

#include "Logger.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
public:
    unsigned int id;

    Shader() = default;

    Shader(const char *vertexPath, const char *fragmentPath) {
        // read shader files
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        IC_CORE_INFO("vertex path: {0} fragment path: {1}", vertexPath, fragmentPath);

        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure &e) {
            IC_CORE_ERROR("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n{0}", e.what());
        }

        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        // compile shaders
        unsigned int vertex, fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEXSHADER");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENTSHADER");

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        CheckCompileErrors(id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void Use() const { glUseProgram(id); }

    void BindUniformBuffer(const std::string &name, int index) const {
        unsigned int uniformBlockIndex = glGetUniformBlockIndex(id, name.c_str());
        glUniformBlockBinding(id, uniformBlockIndex, index);
    }

    void SetBool(const std::string &name, bool value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
    }

    void SetInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void SetFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void SetVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
    }

    void SetMat4(const std::string &name, const glm::mat4 &value) const {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

private:
    void CheckCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
                IC_CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{0}", infoLog);
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
                IC_CORE_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{0}", infoLog);
            }
        }
    }
};
