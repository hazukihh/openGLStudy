#pragma once
#ifndef _RENDER_H
#define _RENDER_H


#include "Utils.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
	//use the defalurt color(or the last seted) to clear
	void SetClearColor(float v0, float v1, float v2, float v3) const;
	// set ClearColor to vec4(v0,v1,v2,v3),then clear
	void Clear(unsigned int mask) const;
	// DrawElements
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	// DrawArrays
	void Draw(const VertexArray& va, const Shader& shader, int first, int count) const;
	
};


#endif // !_RENDER_H