
#ifndef _VERTEX_ARRAY_H
#define _VERTEX_ARRAY_H



#include "VertexBuffer.h"
#include "VertexBufferLayout.hpp"

class VertexArray
{
private:
	unsigned m_RendererID;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

};

#endif // !_VERTEX_ARRAY_H