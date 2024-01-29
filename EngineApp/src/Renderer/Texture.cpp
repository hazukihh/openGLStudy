#include "Texture.h"


#include "stb_image/stb_image.h"
#include <iostream>


Texture::Texture(const std::string& path,unsigned int type )
	:m_RendererID(0),m_FilePath(path),m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_Channels(0), m_type(type)
{
	stbi_set_flip_vertically_on_load(true);

	
	GLCall(glGenTextures(1, &m_RendererID));

	//TODO: Expand  type of texture (2d,3d)
	GLCall(glBindTexture(type, m_RendererID));

	//TODO: set lots of Parameter
	//设置 s,t轴 环绕方式 :
	// GL_REPEAT , GL_MIRRORED_REPEAT , 
	// GL_CLAMP_TO_EDGE , GL_CLAMP_TO_BORDER
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置过滤方式 :
	// GL_NEAREST ,GL_LINEAR 
	//or:
	// GL_NEAREST_MIPMAP_NEAREST , GL_NEAREST_MIPMAP_LINEAR
	// GL_LINEAR_MIPMAP_NEAREST , GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//TODO: ???  set desired_channels to 4
	m_LocalBuffer = stbi_load(path.c_str(),
		&m_Width, &m_Height, &m_Channels, 4);
	
	if (m_LocalBuffer)
	{
		//TODO: Expand 参数的设置 internalformat , format
		glTexImage2D(type, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(type);
		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot ) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_type, m_RendererID);
}


void Texture::UNbind() const
{
	GLCall(glBindTexture(m_type, 0));
}
