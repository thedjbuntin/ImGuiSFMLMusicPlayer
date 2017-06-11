#include "MusicPlayer_Application.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Duncan Bunting's Music Player");
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	MusicPlayer application(window);
	application.Run();

	return EXIT_SUCCESS;

	/*
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	ImGui::SFML::Init(window);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);




	while (window.isOpen())	// Game Loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	
	return 0;*/
}