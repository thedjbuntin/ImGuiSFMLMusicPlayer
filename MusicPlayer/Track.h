#pragma once

#include "sfml.h"
#include <iostream>
#include "dirent.h"
#include <sys/stat.h>
#include <vector>
#include <memory>

class Track
{
public:
	Track();
	~Track();

	void PlayPause();
	void Loop();
	void Stop();
	void Next();
	void Prev();

	void Update();	//Called Every Frame

	float Volume() const { return volume_; }
	void Volume(const float _volume) { volume_ = _volume; MusicTrack[CurrentTrackID_]->setVolume(_volume); }

	// Returns Current Tracks Current Time (/Play Offeset) as Seconds.
	float CurrentTime() const { return MusicTrack[CurrentTrackID_]->getPlayingOffset().asSeconds(); }
	void SetCurrentTime(const float _seek_time) { MusicTrack[CurrentTrackID_]->setPlayingOffset(sf::seconds(_seek_time)); }

	// Returns Current Tracks Duration as Seconds.
	float Duration() const { return MusicTrack[CurrentTrackID_]->getDuration().asSeconds(); }
	
	int CurrentTrackID() const { return CurrentTrackID_; }
	void SetTrackID(const int _trackID) { StartNew(_trackID); }

	bool isPlaying() const { return isPlaying_; }

	std::string Artist() const { return ArtistName[CurrentTrackID_]; }
	std::string Name() const { return SongName[CurrentTrackID_]; }
	sf::Texture Art() const { return ArtTexture[CurrentTrackID_]; }
	std::string ArtPath() const { return ArtPath_[CurrentTrackID_]; }
	std::string ArtPath(const int TrackID) const { return ArtPath_[TrackID]; }

	std::vector<std::string> List() const { return SongName; }

	void Import(const std::string &directory);	//Possibly move to constructor?
private:
	void StoreFileList(std::vector<std::string> &out, const std::string &directory);
	void StoreInfo();
	bool LoadSFMLMusic();
	// CleanUp Current Track and Start New - Moved to own function since near-duplicated in Prev() and Next()
	//isNext = true if next track, false if previous track
	void StartNew(bool isNext);
	void StartNew(int NewTrackID);

	float volume_;
	bool isPlaying_, isAutoPlay;

	int CurrentTrackID_;

	//Stores the location and name of the placeholder image
	const std::string PlaceholderArtPath = "music/placeholder.jpg";
	//Initialized on start to load placeholder texture - avoids reloading image.
	sf::Texture PlaceholderTexture;
	bool isPlaceholderTextureLoaded;

	std::vector<std::string> FileList;
	std::vector<std::string> SongName;		//Store Song Names	- Mainly for future development, would like to implement by Artist/Sortable Lists.
	std::vector<std::string> ArtistName;	//Store Artist Names
	std::vector<std::unique_ptr<sf::Music>> MusicTrack;		//unique_ptr instead of standard sf::Music vector as Music is NonCopyable - https://en.sfml-dev.org/forums/index.php?topic=18043.0
	std::vector<sf::Texture> ArtTexture;	//Store ArtTexture in a vector for now, not used currently since texture is destroyed when StoreInfo() finishes. Possibly useful for future development.
	std::vector<std::string> ArtPath_;		//Store the ArtTexture Path as a temporary fix around the problem of Texture's being untransferable, instead Application asks for path and loads itself.

};