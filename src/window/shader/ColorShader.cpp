//
// Created by thijs on 31-08-20.
//

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "ColorShader.h"
#include "../Camera.h"

void ColorShader::update(Window* handle, glm::vec3 &position) {
    // update MVP
    auto* camera = handle->getCamera();
    auto P = camera->getProjectionMatrix();
    auto V = camera->getViewMatrix();
    auto M = glm::mat4(1.0);
    M = glm::translate(M, position);

    auto MVP = P*V*M;
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

//    // bind texture in Texture Unit 0
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glUniform1i(attrID, 0);

}
