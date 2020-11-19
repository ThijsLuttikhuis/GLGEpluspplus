//
// Created by thijs on 31-08-20.
//

#ifndef GLGEPLUSPLUS_COLORSHADER_H
#define GLGEPLUSPLUS_COLORSHADER_H

#include "Shader.h"

class ColorShader : public Shader {
private:

public:
    ColorShader() : Shader() {};

    void setAttr(uint attr) override {};

    void update(Window* handle,  glm::vec3 &position) override;
};


#endif //GLGEPLUSPLUS_COLORSHADER_H
