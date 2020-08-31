//
// Created by thijs on 31-08-20.
//

#ifndef GLGEPLUSPLUS_TEXTURESHADER_H
#define GLGEPLUSPLUS_TEXTURESHADER_H

#include "Shader.h"

class TextureShader : public Shader {
private:
    uint texture;

public:
    TextureShader() : Shader(), texture() {};

    void setAttr(uint attr) override;

    void update(Window* handle) override;
};


#endif //GLGEPLUSPLUS_TEXTURESHADER_H
