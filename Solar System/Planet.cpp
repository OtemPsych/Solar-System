#include "Planet.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>

// Constructor
Planet::Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget)
	: CelestialBody(std::move(celestialBody))
	, mOrbit(mShape, orbitalTarget.mShape)
	, mConnectorLines()
{	
}

// Public Methods
	// Set Connecting Target
void Planet::setConnectingTarget(CelestialBody& body)
{
	mConnectorLines.setLineTarget(body);
}
	// Check Screen Rect Intersection
void Planet::checkScreenRectIntersection(sf::FloatRect screenRect)
{
	mOrbit.checkIntersection(screenRect);

	CelestialBody::checkScreenRectIntersection(screenRect);
}
	// Check Mouse Intersection
bool Planet::checkMouseIntersection(sf::Vector2f mousePos)
{
	sf::FloatRect mouseBounds(mousePos, mousePos);
	if (mShape.getGlobalBounds().intersects(mouseBounds))
		return true;

	return false;
}
	// Update
void Planet::update(sf::Time dt)
{
	mOrbit.update(dt);
	sf::Vector2f orbitCenter(mOrbit.getShape().getPosition().x + mOrbit.getShape().getRadius(),
							 mOrbit.getShape().getPosition().y + mOrbit.getShape().getRadius());
	sf::Vector2f planetCenter(mShape.getPosition().x + mOrbit.getShape().getRadius(),
							  mShape.getPosition().y + mOrbit.getShape().getRadius());

	float rotationSpeed = 250 / (mOrbit.getShape().getRadius() / 2);
	sf::Transform rotation;
	rotation.rotate(rotationSpeed, orbitCenter.x - mShape.getRadius(),
									orbitCenter.y - mShape.getRadius());
	mShape.setPosition(rotation.transformPoint(mShape.getPosition()));
}
	// Draw
void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mOrbit);
	target.draw(mConnectorLines);
	CelestialBody::draw(target, states);
}