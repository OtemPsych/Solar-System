#include "Planet.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>

// Constructor
Planet::Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget)
	: CelestialBody(std::move(celestialBody))
	, mOrbit(mShape, orbitalTarget.mShape)
{
}

// Public Methods
	// Check Screen Rect Intersection
void Planet::checkScreenRectIntersection(sf::FloatRect screenRect)
{
	mOrbit.checkIntersection(screenRect);

	CelestialBody::checkScreenRectIntersection(screenRect);
}
	// Highlight Orbit
void Planet::highlightOrbit(bool state)
{
	if (state)
		mOrbit.getShape().setOutlineColor(sf::Color::Cyan);
	else
		mOrbit.getShape().setOutlineColor(sf::Color::White);
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
	CelestialBody::draw(target, states);
}