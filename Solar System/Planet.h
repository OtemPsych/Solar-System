#ifndef Planet_H_
#define Planet_H_

#include "CelestialBody.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Planet :public CelestialBody
{
private:
	// Private Data Members
	CelestialBody&					mOrbitalTarget;
	sf::CircleShape					mOrbit;
	bool							mOrbitVisible;
	float							mRotationSpeed;
	std::vector<sf::RectangleShape> mLines;
	CelestialBody&					mLinesTarget;
	bool						    mAddLines;

private:
	// Private Methods
	sf::CircleShape createOrbit();
	void addLine();
public:
	// Constructor
	Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget,
		   float rotationSpeed, CelestialBody& linesTarget, bool addLines = false);
	// Public Methods
	virtual void checkScreenRectIntersection(sf::FloatRect screenRect);
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif