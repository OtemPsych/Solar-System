#include "Planet.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <cmath>

// Constructor
Planet::Planet(CelestialBody celestialBody, CelestialBody& orbitalTarget,
			   float rotationSpeed, CelestialBody& linesTarget, bool addLines)
	: CelestialBody(std::move(celestialBody))
	, mOrbitalTarget(orbitalTarget)
	, mOrbit(createOrbit())
	, mOrbitVisible(true)
	, mRotationSpeed(rotationSpeed)
	, mLines()
	, mLinesTarget(linesTarget)
	, mAddLines(addLines)
{
}

// Private Method
	// Create Orbit
sf::CircleShape Planet::createOrbit()
{
	const auto& targetShape = mOrbitalTarget.mShape;

	sf::CircleShape orbit;
	orbit.setRadius((mShape.getPosition().x + mShape.getRadius()) - (targetShape.getPosition().x + targetShape.getRadius()));
	orbit.setPosition(targetShape.getPosition().x + targetShape.getRadius() - orbit.getRadius(),
					  targetShape.getPosition().y + targetShape.getRadius() - orbit.getRadius());
	orbit.setFillColor(sf::Color::Transparent);
	orbit.setOutlineColor(sf::Color::White);
	orbit.setOutlineThickness(2.f);

	return orbit;
}
	// Add Line
void Planet::addLine()
{
	auto distanceVec(sf::Vector2f((mShape.getPosition().x + mShape.getRadius()) 
								   - (mLinesTarget.mShape.getPosition().x + mLinesTarget.mShape.getRadius()),
								  (mShape.getPosition().y + mShape.getRadius()) 
								   - (mLinesTarget.mShape.getPosition().y + mLinesTarget.mShape.getRadius())));
	auto distance = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));
	auto angle = atan2f(distanceVec.y, distanceVec.x) * 180 / 3.14159265359 + 90.f;

	sf::RectangleShape line(sf::Vector2f(1.f, distance));
	line.setPosition(mShape.getPosition().x + mShape.getRadius(), mShape.getPosition().y + mShape.getRadius());
	line.setFillColor(sf::Color::White);
	line.setRotation(angle);

	mLines.push_back(line);
}

// Public Methods
	// Check Screen Rect Intersection
void Planet::checkScreenRectIntersection(sf::FloatRect screenRect)
{
	auto distanceFromOrbit(sf::Vector2f(std::abs(mOrbit.getPosition().x - mOrbitalTarget.mShape.getPosition().x - mOrbitalTarget.mShape.getRadius()),
										std::abs(mOrbit.getPosition().y - mOrbitalTarget.mShape.getPosition().y - mOrbitalTarget.mShape.getRadius())));
	auto distanceFromScreen(sf::Vector2f(std::abs(mOrbitalTarget.mShape.getPosition().x - mOrbitalTarget.mShape.getRadius() - screenRect.width),
										 std::abs(mOrbitalTarget.mShape.getPosition().y - mOrbitalTarget.mShape.getRadius() - screenRect.height)));
	auto orbitDistance = sqrt(pow(distanceFromOrbit.x, 2) + pow(distanceFromOrbit.y, 2));
	auto screenDistance = sqrt(pow(distanceFromScreen.x, 2) + pow(distanceFromScreen.y, 2));

	if (orbitDistance < screenDistance)
		mOrbitVisible = true;
	else {
		mOrbitVisible = false;
		//std::cout << "Not Visible\n";
	}

	CelestialBody::checkScreenRectIntersection(screenRect);
}
	// Update
void Planet::update(sf::Time dt)
{
	sf::Transform rotation;
	rotation.rotate(mRotationSpeed, mOrbitalTarget.mShape.getPosition().x + mOrbitalTarget.mShape.getRadius() - mShape.getRadius(),
						 mOrbitalTarget.mShape.getPosition().y + mOrbitalTarget.mShape.getRadius() - mShape.getRadius());
	mShape.setPosition(rotation.transformPoint(mShape.getPosition()));

	if (mAddLines)
		addLine();
}
	// Draw
void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& line : mLines)
		target.draw(line, states);

	if (mOrbitVisible)
		target.draw(mOrbit, states);
	CelestialBody::draw(target, states);
}