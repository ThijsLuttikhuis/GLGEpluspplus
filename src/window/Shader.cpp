//
// Created by thijs on 26-08-20.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Shader.h"
#include "../TEMP.h"

const uint &Shader::getVertexShaderID() const {
    return vertexShaderID;
}

const uint &Shader::getProgramID() const {
    return programID;
}

const uint &Shader::getFragmentShaderID() const {
    return fragmentShaderID;
}

bool Shader::loadShader(const std::string &vertexShaderLocation, const std::string &fragmentShaderLocation) {
    // create the shaders
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // get shader code
    std::string vertexShaderCode = getShaderCode(vertexShaderLocation);
    if (vertexShaderCode.empty()) {
        std::cout << "cannot load \"" << vertexShaderLocation << "\"!" << std::endl;
        return false;
    }
    std::string fragmentShaderCode = getShaderCode(fragmentShaderLocation);
    if (fragmentShaderCode.empty()) {
        std::cout << "cannot load \"" << fragmentShaderLocation << "\"!" << std::endl;
        return false;
    }

    GLint result = GL_FALSE;
    int logLength;

    compileShader(vertexShaderCode, vertexShaderID, result, logLength);
    compileShader(fragmentShaderCode, fragmentShaderID, result, logLength);

    programID = glCreateProgram();

    linkProgram(programID, vertexShaderID, fragmentShaderID, result, logLength);
}

std::string Shader::getShaderCode(const std::string &shader) {
    // Read the Vertex Shader code from the file
    std::string vertexShaderCode = {};
    std::ifstream vertexShaderStream(shader, std::ios::in);
    if (vertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    return vertexShaderCode;
}

void Shader::compileShader(const std::string &shaderCode, const int &shaderID, int &result, int &logLength) {

    // Compile Vertex Shader
    char const* VertexSourcePointer = shaderCode.c_str();
    glShaderSource(shaderID, 1, &VertexSourcePointer, nullptr);
    glCompileShader(shaderID);

    // Check Vertex Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    checkLog(shaderID, logLength);
}

void Shader::linkProgram(const uint &pID, const uint &vsID, const uint &fsID, int &result, int &logLength) {

    glAttachShader(pID, vsID);
    glAttachShader(pID, fsID);
    glLinkProgram(pID);

    // Check the program
    glGetProgramiv(pID, GL_LINK_STATUS, &result);
    glGetProgramiv(pID, GL_INFO_LOG_LENGTH, &logLength);
    checkLog(pID, logLength);

    glDetachShader(pID, vsID);
    glDetachShader(pID, fsID);

    glDeleteShader(vsID);
    glDeleteShader(fsID);
}

void Shader::checkLog(const int &shaderID, int &logLength) {
    if (logLength > 0) {
        std::vector<char> ProgramErrorMessage(logLength + 1);
        glGetProgramInfoLog(shaderID, logLength, nullptr, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
}

Shader::~Shader() {
    glDeleteProgram(programID);
    glDeleteTextures(1, &textureID);
}

void Shader::setUniformLocationMVP(const std::string &MVPName) {
    matrixID  = glGetUniformLocation(programID, MVPName.c_str());
}

void Shader::setUniformLocationTexture(const std::string &textureName) {
    textureID = glGetUniformLocation(programID, textureName.c_str());
}

void Shader::update(Window* handle) {
    // update MVP
    auto* camera = handle->getCamera();
    auto MVP = camera->getMVP();
    auto& MVPref = MVP[0][0];

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVPref);

    // bind texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);

}

void Shader::setTextureFromDDS(const std::string &fileName) {
    texture = TEMP::loadDDS(fileName.c_str());
}
