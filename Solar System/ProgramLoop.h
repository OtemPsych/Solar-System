#ifndef ProgramLoop_H_
#define ProgramLoop_H_

#include "SolarSystem.h"

class ProgramLoop
{
private:
	// Private Data Members
	sf::RenderWindow mWindow;
	sf::FloatRect	 mWindowBounds;
	SolarSystem      mSolarSystem;

private:
	// Private Methods
	void handleViewMovement();
	void handleZoom(int mouseWheelDelta);
	void processEvents();
	void update(sf::Time dt);
	void render();
public:
	// Constructor
	ProgramLoop();
	// Public Method
	void run();
};
#endif