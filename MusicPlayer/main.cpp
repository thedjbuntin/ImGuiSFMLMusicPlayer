/*
Author: Duncan John Bunting - 2017
GitHub Repo: https://github.com/thedjbuntin/ImGuiSFMLMusicPlayer/
Website: http://duncanbunting.com/
*/

#include "MusicPlayer_Application.h"

//Memory Leak Dumping	- There are memory leaks detected but cannot find anywhere in my code that would cause memory leak, for some reason will not tell where leaks are detected from- possibly imgui, sfml or dirent.
//#define _CRTDBG_MAP_ALLOC
//#include <cstdlib>
//#include <crtdbg.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "Duncan Bunting's Music Player");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	MusicPlayer application(window);
	application.Run();

	/*try 
	{
		//application.Run();	// If uncommented remember to comment the other Run() call.
	}
	catch (const std::exception &e)	//messages don't work
	{
		std::cout << e.what() << std::endl;
		std::cout << "Please Exit Application" << std::endl;
		while (true) { }	//FIXME - Improvement: have check for input (ie Esc) for exiting instead of infinite loop.
		return EXIT_FAILURE;
	}*/

	application.CleanUp();
	//_CrtDumpMemoryLeaks();
	return EXIT_SUCCESS;
}