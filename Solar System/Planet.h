#ifndef Planet_H_
#define Planet_H_

#include "Orbit.h"
#include "ConnectorLines.h"

#include <SFML/Graphics/RectangleShape.hpp>

class Planet :public CelestialBody
{
private:
	// Private Data Member(s)
	Orbit		   mOrbit;
	ConnectorLines mConnectorLines;

public:
	// Constructor(s)
	Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget);
	// Public Method(s)
	void setConnectingTarget(CelestialBody& body);
	virtual void checkScreenRectIntersection(sf::FloatRect screenRect);
	bool checkMouseIntersection(sf::Vector2f mousePos);
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif