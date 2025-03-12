#include "cbpch.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>
#include <glad/glad.h>

namespace Cubes {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
    {
        int width, height, numChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &numChannels, 4);

        int internalFormat = 0, dataFormat = 0;
        if(numChannels == 4) { 
            dataFormat = GL_RGBA8;
            internalFormat = GL_RGBA;
        }
        else if (numChannels == 3) {
             dataFormat = GL_RGB8;
             internalFormat = GL_RGBA;
        }


        glGenTextures(1, &_rendererID);
        glBindTexture(GL_TEXTURE_2D, _rendererID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            _width = width;
            _height = height;
        }
        else {
            CB_CORE_LOG_ERROR("Failed to load texture form file");
        }


        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &_rendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _rendererID);
    }

}
