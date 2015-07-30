#include "ProgramLoop.h"

#include <SFML/Window/Event.hpp>

const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

// Constructor
ProgramLoop::ProgramLoop()
	: mWindow(sf::RenderWindow(sf::VideoMode(1920, 1080), "SolarSystem"))
	, mWindowBounds(0.f, 0.f, (float)mWindow.getSize().x, (float)mWindow.getSize().y)
	, mSolarSystem(mWindow)
{
	auto mStyleFlag = sf::Style::Default | sf::Style::Fullscreen;
	std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();

	mWindow.create(VModes.front(), "Solar System", mStyleFlag, sf::ContextSettings(0, 0, 16));
	//mWindow.setVerticalSyncEnabled(true);
}

// Private Methods
	// Handle View Movement
void ProgramLoop::handleViewMovement()
{
	sf::View view = mWindow.getView();

	static bool dragging = false;
	static sf::Vector2i startPos(0, 0);
	sf::Vector2i pos = sf::Mouse::getPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!dragging)
			startPos = pos;
		dragging = true;
	}
	else
		dragging = false;

	if (dragging)
		view.move(-(float)((pos.x - startPos.x) / 100), -(float)((pos.y - startPos.y) / 100));

	mWindow.setView(view);
}
	// Handle Zoom
void ProgramLoop::handleZoom(int mouseWheelDelta)
{
	sf::View view = mWindow.getView();
	if (mouseWheelDelta > 0)
		view.zoom(0.9f);
	else if (mouseWheelDelta < 0)
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
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				mSolarSystem.handleCelestialConnecting(mWindow.mapPixelToCoords(sf::Mouse::getPosition()));
			break;
		case sf::Event::MouseWheelMoved:
			handleZoom(event.mouseWheel.delta);
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
				mWindow.close();
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
		handleViewMovement();
		TimeSinceLastUpdate += clock.restart();
		while (TimeSinceLastUpdate > TimePerFrame)
		{
			TimeSinceLastUpdate -= TimePerFrame;
			processEvents();
			handleViewMovement();
			update(TimePerFrame);
		}
		render();
	}
}