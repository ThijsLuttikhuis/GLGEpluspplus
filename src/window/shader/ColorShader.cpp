//
// Created by thijs on 31-08-20.
//

#include <GL/glew.h>
#include "ColorShader.h"

void ColorShader::update(Window* handle) {
    // update MVP
    auto* camera = handle->getCamera();
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &camera->getMVP()[0][0]);

//    // bind texture in Texture Unit 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glUniform1i(attrID, 0);

}
