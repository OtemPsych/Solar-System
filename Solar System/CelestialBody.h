#ifndef CelestialBody_H_
#define CelestialBody_H_

#include <SFML/Graphics/CircleShape.hpp>

#include <SFML/System/Time.hpp>

class CelestialBody :public sf::Drawable
{
	friend class Planet;
	friend class ConnectorLines;
private:
	// Private Data Members
	sf::CircleShape mShape;
	bool			mShapeVisible;

public:
	// Constructor
	CelestialBody(float radius, sf::Color color,
				  sf::Vector2f position);
	// Destructor
	virtual ~CelestialBody() {}
	// Public Methods
	virtual void checkScreenRectIntersection(sf::FloatRect screenRect);
	sf::Vector2f operator-(float xPos);
	CelestialBody& operator=(const CelestialBody& body);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif