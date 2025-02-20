#pragma once
#include "../Utility/Log.h"
#include <glm/glm.hpp>

namespace Cubes {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetUniformMat4(std::string name, glm::mat4 matrix) const = 0;

    static Ref<Shader> Create(std::string& vertexCode, std::string& fragmentCode);

    };

}