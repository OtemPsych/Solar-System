#ifndef ConnectorLines_H_
#define ConnectorLines_H_

#include "CelestialBody.h"

#include <SFML/Graphics/RectangleShape.hpp>

class ConnectorLines :public sf::Drawable
{
private:
	// Private Data Member(s)
	std::vector<std::pair
		<sf::RectangleShape, bool>>			  mLines;
	std::pair<CelestialBody*, CelestialBody*> mConnectingTargets;
	bool									  mAddLines;

private:
	// Private Method(s)
	void addLine();
public:
	// Constructor(s)
	ConnectorLines(CelestialBody* target1 = nullptr, CelestialBody* target2 = nullptr);
	// Public Method(s)
	void setLineTarget(CelestialBody* body);
	void checkIntersection(sf::FloatRect screenRect);
	void adjustLineAmount();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif