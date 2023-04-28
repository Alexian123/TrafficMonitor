#include "IntersectionControl.h"

using namespace TrafficMonitor;

IntersectionControl::IntersectionControl()
{
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		pedCtl[i] = nullptr;
		carCtl[i] = nullptr;
	}
}

IntersectionControl::~IntersectionControl()
{
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		delete pedCtl[i];
	}
}

bool IntersectionControl::addPedestrianCrossing(Direction dir, TrafficLight *a, TrafficLight *b)
{
	if (a && b && pedCtl[dir] == nullptr) {
		pedCtl[dir] = new _PedCrossing();
		pedCtl[dir]->a = a;
		pedCtl[dir]->b = b;
		return true;
	}
	return false;
}

bool IntersectionControl::addVehicleTrafficLight(Direction dir, TrafficLight *tl)
{
	if (tl && carCtl[dir] == NULL) {
		carCtl[dir] = tl;
		return true;
	}
	return false;
}