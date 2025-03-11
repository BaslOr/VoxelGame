#pragma once
#include "../../Core/Renderer/Shader.h"

namespace Cubes {

	class OpenGLShader :public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, std::string& vertexCode, std::string& fragmentCode);
		~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

		const inline std::string& GetName() const override { return _name; }

		//Unifroms
		void SetUniformMat4(std::string name, glm::mat4 matrix) const override;
		void SetUnifromInt(std::string name, int value) const override;
		void SetUniformFloat3(std::string name, glm::vec3 value) const override;
		void SetUniformFloat4(std::string name, glm::vec4 value) const override;

	private:
		std::string ReadShaderFile(const std::string& filePath);
		std::unordered_map<uint32_t, std::string> ProcessShaderFile(const std::string& filePath);

		void Compile(std::unordered_map<uint32_t, std::string>& sources);
		uint32_t CompileShader(uint32_t shaderType, const std::string& code);

	private:
		uint32_t _rendererID;
		std::string _name;
	};

}
