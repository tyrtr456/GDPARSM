#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int CURRENT_OBJECTS;
	static const float SPACING;
	static const float ROW_SPACING;
	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;

	BaseRunner();
	void run();

private:
	
	sf::RenderWindow		window;
	
	void render();
	void processEvents();
	void update(sf::Time elapsedTime);

	int fps = 0;
	int nObjects = 0; //how many objects have been spawned

	float nextSpaceX = 0.0f;
	float nextSpaceY = 0.0f;
};


