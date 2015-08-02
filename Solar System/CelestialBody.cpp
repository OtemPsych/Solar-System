#include "CelestialBody.h"

#include <SFML/Graphics/RenderTarget.hpp>

// Constructor
CelestialBody::CelestialBody(float radius, sf::Color color,
						     sf::Vector2f position)
	: mShape(radius)
	, mShapeVisible(true)
{
	mShape.setPosition(position.x - radius, position.y - radius);
	mShape.setFillColor(color);
}

// Public Methods
	// Check Screen Rect Intersection
void CelestialBody::checkScreenRectIntersection(sf::FloatRect screenRect)
{
	if (screenRect.intersects(mShape.getGlobalBounds()))
		mShapeVisible = true;
	else
		mShapeVisible = false;
}
	// Check Mouse Intersection
bool CelestialBody::checkMouseIntersection(sf::Vector2f mousePos)
{
	sf::FloatRect mouseBounds(mousePos, mousePos);
	if (mShape.getGlobalBounds().intersects(mouseBounds))
		return true;

	return false;
}
	// Operator-
sf::Vector2f CelestialBody::operator-(float xPos)
{
	sf::Vector2f relPos(mShape.getPosition().x + mShape.getRadius() - xPos,
						mShape.getPosition().y + mShape.getRadius());
	return relPos;
}
	// Operator=
CelestialBody& CelestialBody::operator=(const CelestialBody& body)
{
	mShape = body.mShape;
	mShapeVisible = body.mShapeVisible;

	return *this;
}
	// Draw
void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mShapeVisible)
		target.draw(mShape, states);
}