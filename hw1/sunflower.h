#include "group.h"

class SunFlower : public Group {
protected:
	Circle seeds1;
	Circle seeds2;
	Flower petals1;
	Flower petals2;
public:
	static float constexpr NUMBER_OF_PETALS = 12;
	static float constexpr RADIUS = 100;
	static float constexpr INNER_SEEDS_RADIUS = 30;
	static float constexpr OUTER_SEEDS_RADIUS = 40;
	SunFlower(float scl = 1, float rotation = 0, Point *translation = new Point({0, 0}));
};
