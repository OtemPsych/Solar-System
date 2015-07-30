#include "SolarSystem.h"
#include "Planet.h"

#include <SFML/Graphics/RectangleShape.hpp>

// Constructor
SolarSystem::SolarSystem(sf::RenderWindow& window)
	: mCelestialBodies()
	, mPlanetConnectorPos(-1)
	, mWindow(window)
{
	setupSolarSystem(sf::Vector2f(window.getSize()));
}

// Private Methods
	// Setup Solar System
void SolarSystem::setupSolarSystem(sf::Vector2f windowBounds)
{
	std::unique_ptr<CelestialBody> Sun(new CelestialBody(125.f, sf::Color::Yellow,
		sf::Vector2f(windowBounds.x / 2, windowBounds.y / 2)));
	addCelestialBody(std::move(Sun));

	std::unique_ptr<Planet> Earth(new Planet(CelestialBody(25.f, sf::Color::Blue,
		*mCelestialBodies.front() - 680.f), *mCelestialBodies.front()));
	addCelestialBody(std::move(Earth));

	std::unique_ptr<Planet> Mercury(new Planet(CelestialBody(8.f, sf::Color::Green,
		*mCelestialBodies.front() - 160.f), *mCelestialBodies.front()));
	addCelestialBody(std::move(Mercury));

	std::unique_ptr<Planet> Uranus(new Planet(CelestialBody(20.f, sf::Color::Cyan,
		*mCelestialBodies.front() - 880.f), *mCelestialBodies.front()));
	addCelestialBody(std::move(Uranus));
}
	// Add Celestial Body
void SolarSystem::addCelestialBody(std::unique_ptr<CelestialBody> celestialBody)
{
	mCelestialBodies.push_back(std::move(celestialBody));
}

// Public Methods
	// Handle Planet Connecting
void SolarSystem::handleCelestialConnecting(sf::Vector2f mousePos)
{
	for (size_t i = 0; i < mCelestialBodies.size(); i++)
		if (Planet* ps = dynamic_cast<Planet*>(&(*mCelestialBodies[i])))
			if (ps->checkMouseIntersection(mousePos))
				ps->setConnectingTarget(*ps);
}
	// Update
void SolarSystem::update(sf::Time dt)
{
	for (auto& body : mCelestialBodies)
		if (Planet* ps = dynamic_cast<Planet*>(&(*body)))
			ps->update(dt);
}
	// Draw
void SolarSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect screenRect(sf::Vector2f(mWindow.getView().getCenter().x - mWindow.getView().getSize().x / 2,
										  mWindow.getView().getCenter().y - mWindow.getView().getSize().y / 2),
										  mWindow.getView().getSize());
	for (const auto& body : mCelestialBodies) {
		body->checkScreenRectIntersection(screenRect);
		body->draw(target, states);
	}
}