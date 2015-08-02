#include "ConnectorLines.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

// Constructor(s)
ConnectorLines::ConnectorLines(CelestialBody* target1, CelestialBody* target2)
	: mLines()
	, mConnectingTargets(target1, target2)
	, mAddLines(false)
{
}

// Private Method(s)
	// Add Line
void ConnectorLines::addLine()
{
	auto& targetShape1 = mConnectingTargets.first->mShape;
	auto& targetShape2 = mConnectingTargets.second->mShape;
	sf::Vector2f targetShapeCenter1(targetShape1.getPosition().x + targetShape1.getRadius(),
									targetShape1.getPosition().y + targetShape1.getRadius());
	sf::Vector2f targetShapeCenter2(targetShape2.getPosition().x + targetShape2.getRadius(),
								    targetShape2.getPosition().y + targetShape2.getRadius());

	sf::Vector2f distanceVec(targetShapeCenter2 - targetShapeCenter1);
	auto distance = sqrt(pow(distanceVec.x, 2) + pow(distanceVec.y, 2));
	auto angle = atan2f(distanceVec.y, distanceVec.x) * 180 / 3.14159265359 + 90.f;

	sf::RectangleShape line(sf::Vector2f(1.f, distance));
	line.setPosition(targetShapeCenter2);
	line.setFillColor(sf::Color::White);
	line.setRotation((float)angle);

	mLines.push_back(std::make_pair(line, true));

	if (mLines.size() > 1500)
		mAddLines = false;
}
	// Remove Lines
void ConnectorLines::removeLines()
{
	mLines.erase(mLines.begin());
	if (mLines.empty())
		mAddLines = true;
}
// Public Method(s)
	// Set Line Target
void ConnectorLines::setLineTarget(CelestialBody* body)
{
	if (mConnectingTargets.first == nullptr)
		mConnectingTargets.first = body;
	else if (mConnectingTargets.second == nullptr) {
		mConnectingTargets.second = body;
		mAddLines = true;
	}
}
	// Check Intersection
void ConnectorLines::checkIntersection(sf::FloatRect screenRect)
{
	for (auto& line : mLines)
		if (screenRect.intersects(line.first.getGlobalBounds()))
			line.second = true;
		else
			line.second = false;
}
	// Adjust Line Amount
void ConnectorLines::adjustLineAmount()
{
	if (mAddLines)
		addLine();
	else if (!mLines.empty())
		removeLines();
}
	// Draw
void ConnectorLines::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& line : mLines)
		if (line.second)
			target.draw(line.first, states);
}