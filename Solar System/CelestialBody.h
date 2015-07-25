#ifndef CelestialBody_H_
#define CelestialBody_H_

#include <SFML/Graphics/CircleShape.hpp>

class CelestialBody :public sf::Drawable
{
	friend class Planet;
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
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif