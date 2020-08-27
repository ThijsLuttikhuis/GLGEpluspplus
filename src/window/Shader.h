//
// Created by thijs on 26-08-20.
//

#ifndef GLGEPLUSPLUS_SHADER_H
#define GLGEPLUSPLUS_SHADER_H


#include <GL/glew.h>
#include <string>
#include <map>
#include "Window.h"


class Shader {
private:
    // shaders
    uint vertexShaderID;
    uint fragmentShaderID;
    uint programID;

    uint matrixID;
    uint textureID;

    uint texture;

    static std::string getShaderCode(const std::string &shader);
    static void compileShader(const std::string &shaderCode, const int &shaderID, int &result, int &logLength);
    static void linkProgram(const uint &pID, const uint &vsID, const uint &fsID, int &result, int &logLength);
    static void checkLog(const int &shaderID, int &logLength);
public:
    Shader() = default;
    ~Shader();

    const uint &getVertexShaderID() const;
    const uint &getFragmentShaderID() const;
    const uint &getProgramID() const;

    bool loadShader(const std::string &vertexShader, const std::string &fragmentShader);

    void setUniformLocationMVP(const std::string &MVPName);
    void setUniformLocationTexture(const std::string &textureName);

    void update(Window* handle);

    void setTextureFromDDS(const std::string &fileName);
};


#endif //GLGEPLUSPLUS_SHADER_H
