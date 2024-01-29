
#ifndef _VERTEX_BUFFER_LAYOUT_H
#define _VERTEX_BUFFER_LAYOUT_H


#include <vector>
#include "Utils.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:	return sizeof(unsigned char);
			default:
				break;
		}
		ASSERT(false);
		return 0;
		
	}
};

class VertexBufferLayout
{
private:

	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:

	VertexBufferLayout()
		:m_Stride(0) {}
	/*~VertexBufferLayout()
	{}*/

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);

	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);

	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);

	}

	template<typename T>
	void Skip(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Skip<float>(unsigned int count)
	{
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	// (const std::vector<VertexBufferElement>) : 返回值不可修改
	inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

#endif // !_VERTEX_BUFFER_LAYOUT_H