#ifndef SolarSystem_H_
#define SolarSystem_H_

#include "CelestialBody.h"
#include "ConnectorLines.h"

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

class SolarSystem :public sf::Drawable, private sf::NonCopyable
{
private:
	// Private Data Member(s)
	std::vector<std::unique_ptr<CelestialBody>> mCelestialBodies;
	ConnectorLines								mConnectorLines;
	sf::RenderWindow&							mWindow;

private:
	// Private Method(s)
	void setupSolarSystem(sf::Vector2f windowBounds);
	void checkIntersections();
	void addCelestialBody(std::unique_ptr<CelestialBody> celestialBody);
	sf::Color createRandomPlanetColor();
public:
	// Constructor(s)
	SolarSystem(sf::RenderWindow& window);
	// Public Method(s)
	void handleCelestialConnecting(sf::Vector2f mousePos);
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif