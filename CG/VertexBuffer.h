#pragma once

class VertexBuffer
{
	unsigned int ID;
	unsigned int getSize(int count, const unsigned int& gType);
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetBufferData(const void* data, unsigned int size);
	void setLayout(unsigned int* layout, unsigned int size);
};

