#pragma once
#include <cstdint>

class Image
{
public:

	int width{};
	int height{};
	uint32_t* data{};

	Image() {}

	Image(int width, int height) : width{ width }, height{ height } {
		data = new uint32_t[width * height];
	}
	
	void create(int width, int height) {
		if (data) delete data;
		data = new uint32_t[width * height];
		this->width = width;
		this->height = height;
	}

	void fill(uint32_t color) {
		for (uint32_t* i = data; i < data + width*height; i++)
			*i = color;
		
	}

	uint8_t& at(int x, int y, int z) {
		return *((uint8_t*)(data + y + x * width) + z);
	}
	uint32_t& at(int x, int y) {
		return *(data + y + x * width);
	}


	~Image() {
		delete data;
		data = nullptr;
	}

};
