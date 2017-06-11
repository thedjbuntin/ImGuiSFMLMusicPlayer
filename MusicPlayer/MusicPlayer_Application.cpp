#include "MusicPlayer_Application.h"

// DEBUGGING 
#include <iostream>

MusicPlayer::MusicPlayer(sf::RenderWindow& _window) :
	window_(_window)
{ 
}

MusicPlayer::~MusicPlayer()
{ }

bool MusicPlayer::Run()
{
	std::cout << "Init in MusicPlayer.CPP" << std::endl;
	
	Update();

	return 0;
}

void MusicPlayer::CleanUp()
{

}

bool MusicPlayer::Update()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	// let's use char array as buffer, see next part
	// for instructions on using std::string with ImGui
	char windowTitle[255] = "ImGui + SFML = <3";

	window_.setTitle(windowTitle);
	window_.resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.


	sf::Clock deltaClock;
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

		ImGui::Begin("Sample window"); // begin window

									   // Background color edit
		if (ImGui::ColorEdit3("Background color", color)) {
			// this code gets called if color value changes, so
			// the background color is upgraded automatically!
			bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
			bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
			bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
		}

		// Window title text edit
		ImGui::InputText("Window title", windowTitle, 255);

		if (ImGui::Button("Update window title")) {
			// this code gets if user clicks on the button
			// yes, you could have written if(ImGui::InputText(...))
			// but I do this to show how buttons work :)
			window_.setTitle(windowTitle);
		}
		ImGui::End(); // end window

		window_.clear();
		window_.draw(shape);
		ImGui::Render();
		window_.display();
	}

	return 0;
}