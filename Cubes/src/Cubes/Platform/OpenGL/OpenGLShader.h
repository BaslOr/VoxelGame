#pragma once
#include "../../Renderer/Shader.h"

namespace Cubes {

	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(std::string& vertexCode, std::string& fragmentCode); //TODO: Later get per file
		~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		void SetUniformMat4(std::string name, glm::mat4 matrix) const override;

	private:
		uint32_t _rendererID;
	};

}
