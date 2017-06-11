#pragma once

#include "sfml.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <dirent.h>
#include <sys/stat.h>

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

	// Load Song List from directory defined "SongDirectory" using Dirent.h
	void StoreFileList(std::vector<std::string> &out, const std::string &directory);
	void StoreMusicInfo(std::vector<std::string> _FileList);

	const std::string MusicDirectory = "music";
	std::vector<std::string> FileList;
	std::vector<std::string> SongName;	//Store Song Names	- Mainly for future development, would like to implement by Artist/Sortable Lists.
	std::vector<std::string> ArtistName;	//Store Artist Names
	const char* cPlay = "Play";
	const char* cPause = "Pause";
	bool isPlaying, isVolume, isTrackList;
	int current_track;
};