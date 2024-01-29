//TODO: a lot of details need to add and alter

#include "Utils.h"
#include <string>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Channels; // m_BPP ? Bit Per Pixel ? / nrChannels ?颜色通道的个数?
	unsigned int m_type;
public:
	Texture(const std::string& path, unsigned int type = GL_TEXTURE_2D);
	~Texture();

	void Bind(unsigned int slot =0 ) const;
	void UNbind() const;

	inline int GetWidth() const { return m_Width; };
	inline int GetHeight() const { return m_Height; };
	inline int GetType() const { return m_type; };

};

