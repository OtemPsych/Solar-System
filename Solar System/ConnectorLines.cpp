#include "ConnectorLines.h"
#include "Planet.h"

#include <SFML/Graphics/RenderTarget.hpp>

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

	if (mLines.size() > 3000)
		mAddLines = false;
}

// Public Method(s)
	// Set Line Target
void ConnectorLines::setLineTarget(CelestialBody* body)
{
	static bool targetRotation = true;

	if (targetRotation) {
		mLines.clear();
		if (Planet* target1 = dynamic_cast<Planet*>(&(*mConnectingTargets.first)))
			target1->highlightOrbit(false);

		mConnectingTargets.first = body;

		if (Planet* target1 = dynamic_cast<Planet*>(&(*mConnectingTargets.first)))
			target1->highlightOrbit(true);

		if (Planet* target2 = dynamic_cast<Planet*>(&(*mConnectingTargets.second)))
			target2->highlightOrbit(false);

		targetRotation = false;
		mAddLines = false;
	}
	else if (!targetRotation) {
		mConnectingTargets.second = body;
		if (Planet* target2 = dynamic_cast<Planet*>(&(*mConnectingTargets.second)))
			target2->highlightOrbit(true);
		targetRotation = true;
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
		mLines.erase(mLines.begin());
}
	// Draw
void ConnectorLines::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& line : mLines)
		if (line.second)
			target.draw(line.first, states);
}