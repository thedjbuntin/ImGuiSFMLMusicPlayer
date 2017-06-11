#pragma once

#include "sfml.h"
#include "imgui.h"
#include "imgui-SFML.h"

class MusicPlayer
{
public:
	MusicPlayer(sf::RenderWindow&);
	~MusicPlayer();

	bool Run();
	void CleanUp();
	bool Update();
private:
	sf::RenderWindow& window_;
};