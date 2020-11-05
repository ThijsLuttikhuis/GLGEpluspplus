//
// Created by thijs on 31-08-20.
//

#include <GL/glew.h>
#include "TextureShader.h"
#include "../Camera.h"

void TextureShader::update(Window* handle) {
    // update MVP
    auto* camera = handle->getCamera();
    auto MVP = camera->getMVP();
    auto &MVPRef = MVP[0][0];

    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVPRef);

    // bind texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(attrID, 0);

}

void TextureShader::setAttr(uint attr) {
    texture = attr;
}
