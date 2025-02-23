#include "cbpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include "../../Core.h"
#include <glm/gtc/type_ptr.hpp>


namespace Cubes {

	OpenGLShader::OpenGLShader(std::string& vertexCode, std::string& fragmentCode)
	{
		const char* cVertexCode = vertexCode.c_str();
		const char* cFragmentCode = fragmentCode.c_str();

		int success = 0;

		uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &cVertexCode, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			int lenght = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &lenght);

			std::vector<char> errorLog(lenght);
			glGetShaderInfoLog(vertexShader, lenght, &lenght, &errorLog[0]);

			glDeleteShader(vertexShader);

			CB_CORE_ERROR("{0}", errorLog.data());
			CB_CORE_ASSERT(false, "Failed to compile Vertex Shader");
		}

		uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &cFragmentCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			int lenght = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &lenght);

			std::vector<char> errorLog(lenght);
			glGetShaderInfoLog(fragmentShader, lenght, &lenght, &errorLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CB_CORE_ERROR("{0}", errorLog.data());
			CB_CORE_ASSERT(false, "Failed to compile Fragment Shader");
		}

		_rendererID = glCreateProgram();
		glAttachShader(_rendererID, vertexShader);
		glAttachShader(_rendererID, fragmentShader);
		glLinkProgram(_rendererID);
		glGetProgramiv(_rendererID, GL_LINK_STATUS, (int*)&success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_rendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(_rendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			CB_CORE_ASSERT(false, "Failed to Link ShaderProgram");
			CB_CORE_ERROR("{0}", infoLog.data());
		}

		glDetachShader(_rendererID, vertexShader);
		glDetachShader(_rendererID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_rendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(_rendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformMat4(std::string name, glm::mat4 matrix) const
	{
		glUseProgram(_rendererID);
		int location = glGetUniformLocation(_rendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUnifromInt(std::string name, int value) const
	{
		glUseProgram(_rendererID);
		int location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformFloat3(std::string name, glm::vec3 value) const
	{
		glUseProgram(_rendererID);
		int location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniformFloat4(std::string name, glm::vec4 value) const
	{
		glUseProgram(_rendererID);
		int location = glGetUniformLocation(_rendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.a);
	}

}
