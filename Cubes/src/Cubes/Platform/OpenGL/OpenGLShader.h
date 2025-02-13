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
	};

}
