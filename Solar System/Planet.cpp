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
	// Check Orbit Intersection
void Planet::checkOrbitIntersection(sf::FloatRect screenRect)
{
	sf::Vector2f orbitalTargetCenter(mOrbitalTarget.mShape.getPosition().x + mOrbitalTarget.mShape.getRadius(),
								     mOrbitalTarget.mShape.getPosition().y + mOrbitalTarget.mShape.getRadius());

	sf::Vector2f distanceFromOrbit(orbitalTargetCenter.x - (mShape.getPosition().x + mShape.getRadius()),
								   orbitalTargetCenter.y - (mShape.getPosition().x + mShape.getRadius()));
	sf::Vector2f distanceFromScreen(orbitalTargetCenter.x - screenRect.left,
									orbitalTargetCenter.y - screenRect.top);

	float orbitDistance = sqrt(pow(distanceFromOrbit.x, 2) + pow(distanceFromOrbit.y, 2));
	float screenDistance = sqrt(pow(distanceFromScreen.x, 2) + pow(distanceFromScreen.y, 2));

	if (orbitDistance < screenDistance)
		mOrbitVisible = true;
	else
		mOrbitVisible = false;
}
	// Check Lines Intersection
void Planet::checkLinesIntersection(sf::FloatRect screenRect)
{
	for (auto& line : mLines)
		if (screenRect.intersects(line.first.getGlobalBounds()))
			line.second = true;
		else
			line.second = false;
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
	line.setRotation((float)angle);

	mLines.push_back(std::make_pair(line, true));

	if (mLines.size() > 1500)
		mAddLines = false;
}
	// Remove Lines
void Planet::removeLines()
{
	if (mLines.size() == 1)
		mAddLines = true;
	mLines.erase(mLines.begin());
}

// Public Methods
	// Check Screen Rect Intersection
void Planet::checkScreenRectIntersection(sf::FloatRect screenRect)
{
	checkOrbitIntersection(screenRect);
	checkLinesIntersection(screenRect);

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
	else if (!mLines.empty())
		removeLines();
}
	// Draw
void Planet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& line : mLines)
		if (line.second)
			target.draw(line.first, states);

	if (mOrbitVisible)
		target.draw(mOrbit, states);
	CelestialBody::draw(target, states);
}