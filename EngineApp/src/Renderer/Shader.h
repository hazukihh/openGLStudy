#ifndef _SHADER_H
#define _SHADER_H

#include "Utils.h"
#include <unordered_map>
#include <glm/glm.hpp>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetInt(const std::string& name, int value);
	void SetFloat(const std::string& name, float value);

	void SetVec3(const std::string& name, const glm::vec3& value);
	void SetVec3(const std::string& name, float x, float y, float z);
	void SetVec4(const std::string& name, float v0,float v1,float v2 ,float v3);
	void SetVec4(const std::string& name, const glm::vec4& value);

	//default: unsigned char transpose = GL_FALSE = 0 ，传入数据为列主序，不需要转置矩阵
	void SetMat4(const std::string& name, const glm::mat4& mat, unsigned char transpose = GL_FALSE);
	void SetMat4(const std::string& name, const float* value, unsigned char transpose = GL_FALSE);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};




#endif // !_SHADER_H




