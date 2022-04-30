//
// Created by thijs on 26-08-20.
//

#include <iostream>
#include <vector>
#include <GL/glew.h>
#include "Shader.h"
#include "../../TEMP.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

bool Shader::loadShader(const std::string &vertexShaderLocation, const std::string &fragmentShaderLocation) {
    // create the shaders
    shaderID = glCreateShader(GL_VERTEX_SHADER);
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

    compileShader(vertexShaderCode, shaderID, result, logLength);
    compileShader(fragmentShaderCode, fragmentShaderID, result, logLength);

    programID = glCreateProgram();

    linkProgram(programID, shaderID, fragmentShaderID, result, logLength);
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

void Shader::setUniformLocationMVP(const std::string &MVPName) {
    matrixID = glGetUniformLocation(programID, MVPName.c_str());
}

void Shader::setUniformLocationAttr(const std::string &textureName) {
    attrID = glGetUniformLocation(programID, textureName.c_str());
}

uint Shader::getTextureFromDDS(const std::string &fileName) {
    unsigned char header[124];
    FILE* fp;

    /* try to open the file */
    fp = fopen(fileName.c_str(), "rb");
    if (fp == NULL) {
        std::cout << "[Shader::getTextureFromDDS] file " << fileName << " could not be opened!" << std::endl;
        getchar();
        return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*) &(header[8]);
    unsigned int width = *(unsigned int*) &(header[12]);
    unsigned int linearSize = *(unsigned int*) &(header[16]);
    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
    unsigned int fourCC = *(unsigned int*) &(header[80]);


    unsigned char* buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*) malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1) width = 1;
        if (height < 1) height = 1;
    }

    free(buffer);

    return textureID;
}

void Shader::useShader() {
    glUseProgram(programID);
}

Shader::~Shader() {
    glDeleteProgram(programID);
    glDeleteTextures(1, &attrID);
}

