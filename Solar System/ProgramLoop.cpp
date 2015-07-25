#include "ProgramLoop.h"

#include <SFML/Window/Event.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

// Constructor
ProgramLoop::ProgramLoop()
	: mWindow(sf::VideoMode(800, 600), "Solar System", sf::Style::Close | sf::Style::Titlebar,
			  sf::ContextSettings(0, 0, 16))
	, mWindowBounds(0.f, 0.f, (float)mWindow.getSize().x, (float)mWindow.getSize().y)
	, mSolarSystem(mWindow)
{
}

// Private Methods
	// Set Zoom At
void ProgramLoop::setZoomAt(bool direction)
{
	sf::View view = mWindow.getView();
	if (direction)
		view.zoom(0.9f);
	else
		view.zoom(1.1f);

	mWindow.setView(view);
}
	// Process Events
void ProgramLoop::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
		switch (event.type)
		{
		case sf::Event::MouseWheelMoved:
			if (event.mouseWheel.delta > 0)
				setZoomAt(true);
			else if (event.mouseWheel.delta < 0)
				setZoomAt(false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
}
	// Update
void ProgramLoop::update(sf::Time dt)
{
	mSolarSystem.update(dt);
}
	// Render
void ProgramLoop::render()
{
	mWindow.clear();
	mWindow.draw(mSolarSystem);
	mWindow.display();
}

// Public Method
	// Run
void ProgramLoop::run()
{
	sf::Clock clock;
	sf::Time TimeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		TimeSinceLastUpdate += clock.restart();
		while (TimeSinceLastUpdate > TimePerFrame)
		{
			TimeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}