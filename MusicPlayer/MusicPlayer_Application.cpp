#include "MusicPlayer_Application.h"

MusicPlayer::MusicPlayer(sf::RenderWindow& _window) :
	window_(_window)
{
	window_.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	std::cout << " \n" << "============= Storing File List =============" << " \n" << std::endl;
	StoreFileList(FileList, MusicDirectory);
	std::cout << " \n" << "========== END of Storing File List =========" << " \n" << std::endl;
	std::cout << " \n" << "======== Storing Artist and Song Names ======" << " \n" << std::endl;
	StoreMusicInfo(FileList);
	std::cout << " \n" << "==== END of Storing Artist and Song Names ===" << " \n" << std::endl;

	//if (!LoadMusic(FileList))
	//	throw std::runtime_error("Invalid File Name Detected, Exiting");	//Doesnt work

	// Initilize Values
	current_track = 0;
	isPlaying = false;
}

MusicPlayer::~MusicPlayer()
{ }

bool MusicPlayer::Run()
{
	Update();

	return 0;
}

void MusicPlayer::CleanUp()
{
	// Clean Up
}

bool MusicPlayer::Update()
{
	sf::Music music;
	if (!music.openFromFile("music/Harder Than You Think - Public Enemy.ogg"))
		return 0; // error
	static float volume = 50.f;
	
	while (window_.isOpen())	// Game Loop
	{
		sf::Event event;
		while (window_.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window_.close();
		}

		ImGui::SFML::Update(window_, deltaClock.restart());
		ImGui::ShowTestWindow();


		ImGui::Begin("Player"); // begin window
		
		ImGui::Text("Song Name");
		ImGui::Text("Artist Name");

		ImGui::Text("3:33"); ImGui::SameLine();
		ImGui::ProgressBar(0.5f, ImVec2(0.0f, 0.0f));
		ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::Text("6:66");

		if (ImGui::Button("|<"))	//Previous Song
		{
			if (current_track - 1 >= 0)
				current_track--;
			else
				current_track = FileList.size() - 1;
		} ImGui::SameLine();

		if (ImGui::Button("STOP"))	//Stop Playback
		{

		} ImGui::SameLine();
		
		if (ImGui::Button((isPlaying) ? (cPause) : (cPlay)))	// Play/Pause Playback
		{
			if (isPlaying)
				music.pause();
			else
				music.play();

			isPlaying = !isPlaying;	// Toggle Playing
		} ImGui::SameLine();

		if (ImGui::Button("Loop"))	//Loop Current Song
		{

		} ImGui::SameLine();

		if (ImGui::Button(">|"))	//Previous Song
		{
			if (current_track + 1 < FileList.size())
				current_track++;
			else
				current_track = 0;
		} 

		if (ImGui::Button("Volume"))	//Toggle Show Volume
		{
			isVolume = !isVolume;
		} ImGui::SameLine();

		if (ImGui::Button("Track List"))	//Toggle Track List Window
		{
			isTrackList = !isTrackList;
		}

		if (isVolume)
		{
			ImGui::SliderFloat("", &volume, 0.0f, 100.0f, "%.f");
		}

		ImGui::End(); // end player window

		if (isTrackList)
		{
			ImGui::Begin("Track List");	// Begin Track List Window

			/*
			Custom ListBox due to ImGui ListBox not supporting unlimited height.
			This ListBox will attack to the bottom of the window.
			Also makes use of vector instead of array since size of list may be unknown.
			*/
			if(ImGui::ListBoxHeader("", ImVec2(0.0f, -20.0f)))
			{
				// Assume all items have even height (= 1 line of text). If you need items of different or variable sizes you can create a custom version of ListBox() in your code without using the clipper.
				bool value_changed = false;
				ImGuiListClipper clipper(FileList.size(), ImGui::GetTextLineHeightWithSpacing());
				while (clipper.Step())
					for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
					{
						const bool item_selected = (i == current_track);
						const char* item_text = FileList[i].c_str();

						ImGui::PushID(i);
						if (ImGui::Selectable(item_text, item_selected))
						{
							current_track = i;
							value_changed = true;
						}
						ImGui::PopID();
					}
				ImGui::ListBoxFooter();
			}	// End Custom ListBox
			ImGui::End();	// End Track List Window
		}

		window_.clear();
		ImGui::Render();
		window_.display();
	}

	return 0;
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
void MusicPlayer::StoreFileList(std::vector<std::string> &out, const std::string &directory)	
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


		if (full_file_name.find('.mp3') != std::string::npos)
		{
			std::cout << "Oops! Looks like you're trying to use an .mp3 - Unfortunately SFML does not allow MP3s due to Patent issues.\nI recommend converting to and using .ogg for similar file size and audio quality" << std::endl;
		}
		else
		{
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
	}
	closedir(dir);
#endif
}

void MusicPlayer::StoreMusicInfo(std::vector<std::string> _FileList)
{
	for (unsigned int i = 0; i < _FileList.size(); i++)
	{
		// Position of dash seperating Song Name and Artist Name
		std::string::size_type pos = _FileList[i].find('-');

		// FILL ARTIST NAME VECTOR // 
		ArtistName.push_back(_FileList[i]);									// Push File Name into Artist Name Vector
		ArtistName[i] = ArtistName[i].substr(pos + 2);	// Get Artist Name from File Name
		ArtistName[i] = ArtistName[i].substr(0, ArtistName[i].size() - 4);	// Remove .ogg
		std::cout << "Storing Artist Name: " << ArtistName[i] << std::endl;

		// FILL SONG NAME VECTOR //
		SongName.push_back(_FileList[i]);
		SongName[i] = SongName[i].substr(0, pos);
		SongName[i] = SongName[i].substr(SongName[i].find('/') + 1);
		std::cout << "Storing Song Name: " << SongName[i] << std::endl;
	}// End _FileList.size() ForLoop
}