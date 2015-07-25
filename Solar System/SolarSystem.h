#ifndef SolarSystem_H_
#define SolarSystem_H_

#include "CelestialBody.h"

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

class SolarSystem :public sf::Drawable
{
private:
	// Private Data Members
	std::vector<std::unique_ptr<CelestialBody>> mCelestialBodies;
	sf::RenderWindow&							mWindow;

private:
	// Private Methods
	void setupSolarSystem(sf::Vector2f windowBounds);
	void addCelestialBody(std::unique_ptr<CelestialBody> celestialBody);
public:
	// Constructor
	SolarSystem(sf::RenderWindow& window);
	// Public Methods
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif