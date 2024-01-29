#pragma once
#ifndef _VERTEX_BUFFER_H
#define _VERTEX_BUFFER_H



class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	
	void Bind() const;
	void Unbind() const;


};

#endif // !_VERTEX_BUFFER_H