#include "Orbit.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Constructor(s)
Orbit::Orbit(sf::CircleShape& planet, sf::CircleShape& orbitalTarget)
	: mShape(createOrbit(planet, orbitalTarget))
	, mShapeVisible(true)
	, mOrbitalTarget(orbitalTarget)
{
}

// Private Method(s)
	// Create Orbit
sf::CircleShape Orbit::createOrbit(sf::CircleShape& planet, sf::CircleShape& orbitalTarget)
{
	sf::Vector2f orbitalCenter(orbitalTarget.getPosition().x + orbitalTarget.getRadius(),
							   orbitalTarget.getPosition().y + orbitalTarget.getRadius());

	sf::CircleShape orbit;
	orbit.setRadius(orbitalCenter.x - (planet.getPosition().x + planet.getRadius()));
	orbit.setPosition(orbitalCenter.x - orbit.getRadius(),
					  orbitalCenter.y - orbit.getRadius());
	orbit.setFillColor(sf::Color::Transparent);
	orbit.setOutlineColor(sf::Color::White);
	orbit.setOutlineThickness(3.f);

	return orbit;
}
// Public Method(s)
	// Check Intersection
void Orbit::checkIntersection(sf::FloatRect screenRect)
{
	if (screenRect.intersects(mShape.getGlobalBounds()))
		mShapeVisible = true;
	else
		mShapeVisible = false;

	//for (int i = 0; i < mOrbit.getPointCount(); i++) {
	//	sf::Vector2f point = mOrbit.getPoint(i);
	//	if (point.x - mOrbit.getRadius() >= screenRect.left
	//		&& point.x + mOrbit.getRadius() * 2 <= screenRect.width
	//		&& point.y - mOrbit.getRadius() >= screenRect.top
	//		&& point.y + mOrbit.getRadius() * 2 <= screenRect.height) {
	//		mOrbitVisible = true;
	//		break;
	//	}
	//	else
	//		mOrbitVisible = false;
	//}
}
	// Update
void Orbit::update(sf::Time dt)
{
	sf::Vector2f orbitalCenter(mOrbitalTarget.getPosition().x + mOrbitalTarget.getRadius(),
		mOrbitalTarget.getPosition().y + mOrbitalTarget.getRadius());
	mShape.setPosition((orbitalCenter.x - mShape.getRadius()),
		(orbitalCenter.y - mShape.getRadius()));
}
	// Draw
void Orbit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mShapeVisible)
		target.draw(mShape, states);
}