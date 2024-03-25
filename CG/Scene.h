#pragma once
#include "Actor.h"
#include <vector>
#include <list>

class Scene{


public:
	std::vector<Actor> actors;

	void add(const Actor& actor) { actors.push_back(actor); }
	void remove(const int& index) { actors.erase(actors.begin() + index); }
};

