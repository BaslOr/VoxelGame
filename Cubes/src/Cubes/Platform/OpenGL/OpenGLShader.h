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
		void SetUnifromInt(std::string name, int value) const override;
		void SetUniformFloat3(std::string name, glm::vec3 value) const override;
		void SetUniformFloat4(std::string name, glm::vec4 value) const override;


	private:
		uint32_t _rendererID;
	};

}
