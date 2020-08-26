//
// Created by thijs on 26-08-20.
//

#ifndef GLGEPLUSPLUS_SHADER_H
#define GLGEPLUSPLUS_SHADER_H


#include <GL/glew.h>
#include <string>


class Shader {
private:
    uint vertexShaderID;
    uint fragmentShaderID;
    uint programID;

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
};


#endif //GLGEPLUSPLUS_SHADER_H
