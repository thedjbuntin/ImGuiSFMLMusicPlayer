#include "MusicPlayer_Application.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Duncan Bunting's Music Player");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	MusicPlayer application(window);
	application.Run();

	return EXIT_SUCCESS;
}