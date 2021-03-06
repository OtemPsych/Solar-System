#include "SolarSystem.h"
#include "Planet.h"

#include <SFML/Graphics/RectangleShape.hpp>

// Constructor
SolarSystem::SolarSystem(sf::RenderWindow& window)
	: mCelestialBodies()
	, mConnectorLines()
	, mWindow(window)
{
	setupSolarSystem(sf::Vector2f(window.getSize()));
	
	for (int i = 0; i < 50; i++) {
		std::unique_ptr<Planet> newPlanet(new Planet(CelestialBody(25.f, createRandomPlanetColor(),
			*mCelestialBodies.back() - 50.f), *mCelestialBodies.front()));
		addCelestialBody(std::move(newPlanet));
	}
}

// Private Methods
	// Setup Solar System
void SolarSystem::setupSolarSystem(sf::Vector2f windowBounds)
{
	std::unique_ptr<CelestialBody> Sun(new CelestialBody(125.f, sf::Color::Yellow,
		sf::Vector2f(windowBounds.x / 2, windowBounds.y / 2)));
	addCelestialBody(std::move(Sun));

	std::unique_ptr<Planet> Earth(new Planet(CelestialBody(25.f, createRandomPlanetColor(),
		*mCelestialBodies.front() - 680.f), *mCelestialBodies.front()));
	addCelestialBody(std::move(Earth));

	std::unique_ptr<Planet> Mercury(new Planet(CelestialBody(8.f, createRandomPlanetColor(),
		*mCelestialBodies.front() - 360.f), *mCelestialBodies.back()));
	addCelestialBody(std::move(Mercury));

	std::unique_ptr<Planet> Uranus(new Planet(CelestialBody(20.f, createRandomPlanetColor(),
		*mCelestialBodies.front() - 880.f), *mCelestialBodies.front()));
	addCelestialBody(std::move(Uranus));
}
	// Check Intersections
void SolarSystem::checkIntersections()
{
	sf::FloatRect screenRect(sf::Vector2f(mWindow.getView().getCenter().x - mWindow.getView().getSize().x / 2,
										  mWindow.getView().getCenter().y - mWindow.getView().getSize().y / 2),
										  mWindow.getView().getSize());

	mConnectorLines.checkIntersection(screenRect);
	for (const auto& body : mCelestialBodies)
		body->checkScreenRectIntersection(screenRect);
}
	// Add Celestial Body
void SolarSystem::addCelestialBody(std::unique_ptr<CelestialBody> celestialBody)
{
	mCelestialBodies.push_back(std::move(celestialBody));
}
	// Create Random Planet Color
sf::Color SolarSystem::createRandomPlanetColor()
{
	int max = 150,
		min = 100;
	int r = rand() % (max - min) + min,
		g = rand() % (max - min) + min,
		b = rand() % (max - min) + min;

	return sf::Color(r, g, b);
}

// Public Methods
	// Handle Celestial Connecting
void SolarSystem::handleCelestialConnecting(sf::Vector2f mousePos)
{
	for (const auto& body : mCelestialBodies)
		if (body->checkMouseIntersection(mousePos))
			mConnectorLines.setLineTarget(&(*body));
}
	// Update
void SolarSystem::update(sf::Time dt)
{
	for (auto& body : mCelestialBodies)
		if (Planet* ps = dynamic_cast<Planet*>(&(*body)))
			ps->update(dt);

	checkIntersections();
	mConnectorLines.adjustLineAmount();
}
	// Draw
void SolarSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mConnectorLines);
	for (const auto& body : mCelestialBodies)
		body->draw(target, states);
}