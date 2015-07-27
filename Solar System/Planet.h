#ifndef Planet_H_
#define Planet_H_

#include "CelestialBody.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Planet :public CelestialBody
{
	friend class SolarSystem;
private:
	// Private Data Members
	CelestialBody&					mOrbitalTarget;
	sf::CircleShape					mOrbit;
	bool							mOrbitVisible;
	float							mRotationSpeed;
	std::vector<std::pair
		<sf::RectangleShape, bool>> mLines;
	CelestialBody&					mLinesTarget;
	bool						    mAddLines;

private:
	// Private Methods
	sf::CircleShape createOrbit();
	void checkOrbitIntersection(sf::FloatRect screenRect);
	void checkLinesIntersection(sf::FloatRect screenRect);
	void addLine(sf::Time dt);
	void removeLines();
public:
	// Constructor
	Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget,
		   CelestialBody& linesTarget, bool addLines = false);
	// Public Methods
	virtual void checkScreenRectIntersection(sf::FloatRect screenRect);
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif