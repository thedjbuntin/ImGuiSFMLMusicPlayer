#pragma once

#include "sfml.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <sys/stat.h>
#include "Track.h"

//throwing exception
#include <stdexcept>
#include <cstdlib>
#include <iostream>

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
	sf::Clock deltaClock;
	Track MusicTrack;
	sf::Sprite TrackArt;
	int TrackArtID;
	std::vector<std::string> SongList;
	std::vector<sf::Texture> TrackArtTexture;
	ImGuiWindowFlags window_flags;

	const std::string MusicDirectory = "music";
	const char* cPlay = "Play";	//Play/Pause Button Text
	const char* cPause = "Pause";
	bool isVolume, isTrackList, isSeeker;
};