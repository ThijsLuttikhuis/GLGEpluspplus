//
// Created by thijs on 26-08-20.
//

#ifndef GLGEPLUSPLUS_SHADER_H
#define GLGEPLUSPLUS_SHADER_H


#include <GL/glew.h>
#include <string>
#include <map>
#include "../../window/Window.h"


class Shader {
protected:
    // shaders
    uint shaderID;
    uint fragmentShaderID;
    uint programID;

    uint matrixID;
    uint attrID;

    static std::string getShaderCode(const std::string &shader);
    static void compileShader(const std::string &shaderCode, const int &shaderID, int &result, int &logLength);
    static void linkProgram(const uint &pID, const uint &vsID, const uint &fsID, int &result, int &logLength);
    static void checkLog(const int &shaderID, int &logLength);
public:
    Shader() = default;
    ~Shader();

    bool loadShader(const std::string &vertexShader, const std::string &fragmentShader);

    void setUniformLocationMVP(const std::string &MVPName);
    void setUniformLocationAttr(const std::string &textureName);

    virtual void setAttr(uint attr) = 0;

    virtual void update(Window* handle) = 0;

    static uint getTextureFromDDS(const std::string &fileName);

    void useShader();
};


#endif //GLGEPLUSPLUS_SHADER_H
