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



        glGenTextures(1, &_rendererID);
        glBindTexture(GL_TEXTURE_2D, _rendererID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            _width = width;
            _height = height;
        }
        else {
            CB_CORE_ERROR("Failed to load texture form file");
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
