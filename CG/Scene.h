#pragma once
#include "Actor.h"
#include <vector>
#include <list>

class Scene{


public:
	std::vector<Actor> actors;



	void add(const Actor& actor) { actors.push_back(actor); }
	std::vector<float> getPoints() {
		std::vector<float> vec;
		vec.reserve(1000);

		for (auto& i : actors)
			for (auto& j : i.getPoints())
				vec.push_back(j);
		return vec;
	}


	std::vector<unsigned int> getIndices() {
		std::vector<unsigned int> vec;
		vec.reserve(1000);

		int offsset{};

		for (auto& i : actors) {
			for (auto& j : i.getIndicies())
				vec.push_back(j);
		}
		return vec;
	}
};

