#include "Track.h"

Track::Track()
{
	volume_ = 50.0f;
	isPlaying_ = false;
	isAutoPlay = true;	//Added just for further customization, defaulting to true - possible future development would add option to disable autoplay.
	isPlaceholderTextureLoaded = false;
}

Track::~Track()
{}

void Track::Update()
{
	if (isAutoPlay && !MusicTrack[CurrentTrackID_]->getLoop())	//if autoplay enabled(true by default) and not set to loop
	{
		if (MusicTrack[CurrentTrackID_]->getPlayingOffset().asSeconds() >= MusicTrack[CurrentTrackID_]->getDuration().asSeconds() - 0.5f)
		{
			Next();
		}
	}
}

void Track::PlayPause()
{
	if (!isPlaying_)
	{
		MusicTrack[CurrentTrackID_]->play();
		isPlaying_ = true;
	}
	else
	{
		MusicTrack[CurrentTrackID_]->pause();
		isPlaying_ = false;
	}
}

void Track::Loop()
{
	if(!MusicTrack[CurrentTrackID_]->getLoop())
		MusicTrack[CurrentTrackID_]->setLoop(true);
	else
		MusicTrack[CurrentTrackID_]->setLoop(false);
}

void Track::Stop()
{
	MusicTrack[CurrentTrackID_]->stop();
	isPlaying_ = false;
}

void Track::StartNew(bool isNext)
{
	if(MusicTrack[CurrentTrackID_]->getLoop())
		MusicTrack[CurrentTrackID_]->setLoop(false);
	MusicTrack[CurrentTrackID_]->stop();
	
	if (isNext)
	{	// Next Track
		if (CurrentTrackID_ == MusicTrack.size() - 1)
			CurrentTrackID_ = 0;
		else
			CurrentTrackID_++;
	}
	else
	{	// Previous Track
		if (CurrentTrackID_ == 0)
			CurrentTrackID_ = MusicTrack.size() - 1;
		else
			CurrentTrackID_--;
	}
	// Prepare and Start New Track
	MusicTrack[CurrentTrackID_]->setVolume(volume_);	//Keep Same Volume Level
	MusicTrack[CurrentTrackID_]->stop();				//Ensure Starting from Start
	if(isPlaying_)									//Only if user has set to play
		MusicTrack[CurrentTrackID_]->play();				//Play New Track
}

void Track::Next()
{ StartNew(true); }

void Track::Prev()
{ StartNew(false); }

////// IMPORTING AND STORING ///////

void Track::Import(const std::string &directory)
{
	std::cout << " \n" << "============= Storing File List =============" << " \n" << std::endl;
	StoreFileList(FileList, directory);
	std::cout << " \n" << "========== END of Storing File List =========" << " \n" << std::endl;
	std::cout << " \n" << "======== Storing Artist and Song Names ======" << " \n" << std::endl;
	StoreInfo();
	std::cout << " \n" << "==== END of Storing Artist and Song Names ===" << " \n" << std::endl;
	std::cout << " \n" << "=========== Loading Music via SFML ==========" << " \n" << std::endl;
	if (!LoadSFMLMusic())
		std::cout << "Critical Failure: Bad File - " << std::endl;	//FIXME add filename
	std::cout << " \n" << "======== END of Loading Music via SFML =======" << " \n" << std::endl;
}

/*
Source https://stackoverflow.com/questions/306533/how-do-i-get-a-list-of-files-in-a-directory-in-c

Edits:
- Added std::
- Convert string -> const char*
- printing file_name before push
- added check to ensure file name is correct format (Song Name - Artist Name)
- Added check to ensure not mp3.

Other Notes:
- will not work with Unicode enabled, see link for hack

*/
void Track::StoreFileList(std::vector<std::string> &out, const std::string &directory)
{
#ifdef WINDOWS
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return; /* No files found */

	do {
		const std::string file_name = file_data.cFileName;
		const std::string full_file_name = directory + "/" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		std::cout << "Storing: " << file_name << std::endl;

		out.push_back(file_name);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
#else
	DIR *dir;
	class dirent *ent;
	class stat st;

	dir = opendir(directory.c_str());
	while ((ent = readdir(dir)) != NULL) {
		const std::string file_name = ent->d_name;
		const std::string full_file_name = directory + "/" + file_name;

		if (file_name[0] == '.')
			continue;

		if (stat(full_file_name.c_str(), &st) == -1)
			continue;

		const bool is_directory = (st.st_mode & S_IFDIR) != 0;

		if (is_directory)
			continue;

		std::string MP3_String = ".mp3";
		if (full_file_name.find(MP3_String) != std::string::npos)
		{
			std::cout << "Oops! Looks like you're trying to use an .mp3 - Unfortunately SFML does not allow MP3s due to Patent issues.\nI recommend converting to and using .ogg for similar file size and audio quality" << std::endl;
		}
		else
		{
			std::string OGG_String = ".ogg";
			if (full_file_name.find(OGG_String) != std::string::npos)
			{
				std::cout << full_file_name << " ___ APPROVED FOR OGG" << std::endl;
				if (full_file_name.find('-') == std::string::npos)	// Check if correct Name Format
				{
					// ERROR - Skip Adding This Song
					std::cout << "Error Loading: " << full_file_name << "- Skipping.\nPlease Ensure File Names are in the following format: Song Name - Artist Name" << std::endl;
				}
				else
				{
					std::cout << "Storing: " << file_name << std::endl;

					out.push_back(full_file_name);
				}
			}
			else
			{
				std::cout << "Ignoring non-OGG file: " << full_file_name << std::endl;
			}
		}
	}
	closedir(dir);
#endif
}

void Track::StoreInfo()
{
	for (unsigned int i = 0; i < FileList.size(); i++)
	{
		// Position of dash seperating Song Name and Artist Name
		std::string::size_type pos = FileList[i].find('-');

		// FILL ARTIST NAME VECTOR // 
		ArtistName.push_back(FileList[i]);									// Push File Name into Artist Name Vector
		ArtistName[i] = ArtistName[i].substr(pos + 2);	// Get Artist Name from File Name
		ArtistName[i] = ArtistName[i].substr(0, ArtistName[i].size() - 4);	// Remove .ogg
		std::cout << "Storing Artist Name: " << ArtistName[i] << std::endl;

		// FILL SONG NAME VECTOR //
		SongName.push_back(FileList[i]);
		SongName[i] = SongName[i].substr(0, pos);
		SongName[i] = SongName[i].substr(SongName[i].find('/') + 1);
		std::cout << "Storing Song Name: " << SongName[i] << std::endl;


		std::string File_Name = FileList[i].substr(0, FileList[i].find('.'));
		sf::Texture texture;
		if (!texture.loadFromFile(File_Name + ".png"))
		{
			std::cout << "Failed To Find PNG Art for " << File_Name << std::endl;
			if (!texture.loadFromFile(File_Name + ".jpg"))
			{
				std::cout << "Failed To Find JPG Art for " << File_Name << "\n - Attempting to insert Placeholder Art." << std::endl;

				if (!isPlaceholderTextureLoaded)
				{
					if (!PlaceholderTexture.loadFromFile(PlaceholderArtPath))
					{
						std::cout << "Critical Failure: Failed to load PlaceHolder Art..." << std::endl;
					}
					else
					{
						std::cout << "Storing: Placeholder Texture" << std::endl;
						isPlaceholderTextureLoaded = true;
					}
				}

				if (isPlaceholderTextureLoaded)
				{
					ArtTexture.push_back(PlaceholderTexture);
					ArtPath_.push_back(PlaceholderArtPath);
					std::cout << "To add Track Art, place a PNG or JPG file with the exact same name as the Track file in the same location as the track." << std::endl;
				}
				else
				{
					std::cout << "Critical Failure: Placeholder Art was not loaded, ensure file music/placeholder.jpg exists" << std::endl;
				}
			}
			else
			{	//Successfully loaded JPG
				std::cout << "Storing Art For: " << File_Name << std::endl;
				ArtTexture.push_back(texture);
				ArtPath_.push_back(File_Name + ".jpg");
			}
		}
		else
		{	//Successfully loaded PNG
			std::cout << "Storing Art For: " << File_Name << std::endl;
			ArtTexture.push_back(texture);
			ArtPath_.push_back(File_Name + ".png");
		}
	}// End _FileList.size() ForLoop
}

bool Track::LoadSFMLMusic()
{
	for (unsigned int i = 0; i < FileList.size(); i++)
	{
		auto ptr = std::make_unique<sf::Music>();
		if (!ptr->openFromFile(FileList[i]))
		{
			// ERROR
			std::cout << "Critical Failure: File - " << FileList[i] << " Failed To Load" << std::endl;
			return false;
		}

		MusicTrack.push_back(std::move(ptr));
		MusicTrack[i]->setVolume(volume_);	//set volume to default volume for all tracks initially
		std::cout << "Loaded: " << FileList[i] << std::endl;

		/* // Does not work as sf::Music is NonCopyable
		sf::Music TempTrack;
		if (!TempTrack.openFromFile(FileList[i]))
			return false; // Error
		else
			MusicTrack.push_back(TempTrack);	//Success*/
	}
	return true;
}