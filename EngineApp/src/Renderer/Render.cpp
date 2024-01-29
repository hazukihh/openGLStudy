#include "Render.h"

void Renderer::SetClearColor(float v0, float v1, float v2, float v3) const
{
	GLCall(glClearColor(v0, v1, v2, v3));
}

void Renderer::Clear(unsigned int mask) const
{
	
	GLCall(glClear(mask));
	
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

	
}


void Renderer::Draw(const VertexArray& va,  const Shader& shader , int first,int count ) const
{
	shader.Bind();
	va.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, first,count));


}
