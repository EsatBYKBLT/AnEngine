#pragma once
class IndexBuffer
{
	unsigned int ID;
public:
	IndexBuffer();
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();
	void SetBufferData(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
};

