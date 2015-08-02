#ifndef Orbit_H_
#define Orbit_H_

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/CircleShape.hpp>

class Orbit :public sf::Drawable
{
private:
	// Private Data Member(s)
	sf::CircleShape  mShape;
	bool			 mShapeVisible;
	sf::CircleShape& mOrbitalTarget;

private:
	// Private Method(s)
	sf::CircleShape createOrbit(sf::CircleShape& planet, sf::CircleShape& orbitalTarget);
public:
	// Constructor(s)
	Orbit(sf::CircleShape& planet, sf::CircleShape& orbitalTarget);
	// Public Method(s)
	void checkIntersection(sf::FloatRect screenRect);
	sf::CircleShape& getShape() { return mShape; }
	void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif