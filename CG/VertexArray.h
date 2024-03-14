#pragma once
class VertexArray
{
	unsigned int ID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
};

