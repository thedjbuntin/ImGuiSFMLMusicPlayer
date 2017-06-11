#include "MusicPlayer_Application.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Duncan Bunting's Music Player");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	MusicPlayer application(window);

	try 
	{
		application.Run();
	}
	catch (const std::exception &e)	//doesnt work
	{
		std::cout << e.what() << std::endl;
		std::cout << "Please Exit Application" << std::endl;
		while (true) { }	//FIXME - Improvement: have check for input (ie Esc) for exiting instead of infinite loop.
		return EXIT_FAILURE;
	}

	application.CleanUp();
	return EXIT_SUCCESS;
}