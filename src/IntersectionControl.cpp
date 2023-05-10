#include "IntersectionControl.h"

using namespace TrafficMonitor;

IntersectionControl::IntersectionControl()
{
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		pedCtl[i] = nullptr;
		pedLastMillis[i] = 0;
		carCtl[i] = nullptr;
		carLastMillis[i] = 0;
	}
}

IntersectionControl::IntersectionControl(int redTime, int greenTime, int yellowTime)
	: redTime(redTime), greenTime(greenTime), yellowTime(yellowTime)
{
	IntersectionControl();
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
	if (tl && carCtl[dir] == nullptr) {
		carCtl[dir] = tl;
		return true;
	}
	return false;
}

void IntersectionControl::run()
{
	if (state == NORMAL) {
		runNormal();
	} else {
		runSynced();
	}
}

void IntersectionControl::changeState(ControlState state)
{
	this->state = state;
	switch (state) {
		case NORMAL:
			setAllLights(TLState::OFF, false);
			initNormalMode();
			break;
		case DISABLED:
			setAllLights(TLState::OFF, false);
			break;
		case BLINK_YELLOW:
			setAllLights(TLState::YELLOW, true);
			break;
		case DEBUG:
			setAllLights(debugTLState, debugBlinkMode);
			break;
	}
}

void IntersectionControl::setDebugTLState(TLState state)
{
	this->debugTLState = state;
}

void IntersectionControl::setDebugBlinkMode(bool blinkMode)
{
	this->debugBlinkMode = blinkMode;
}

bool IntersectionControl::getDebugBlinkMode() const
{
	return this->debugBlinkMode;
}

void IntersectionControl::runNormal()
{
	long currentMillis = millis();
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		if (carCtl[i] != nullptr) {
			updateVehicleLight(i, currentMillis);
			carCtl[i]->run();
		}
		if (pedCtl[i] != nullptr) {
			updatePedLight(i, currentMillis);
			pedCtl[i]->a->run();
			pedCtl[i]->b->run();
		}
	}
}

void IntersectionControl::runSynced()
{
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		if (carCtl[i] != nullptr) {
			carCtl[i]->run();
		}
		if (pedCtl[i] != nullptr) {
			pedCtl[i]->a->run();
			pedCtl[i]->b->run();
		}
	}
}

void IntersectionControl::setAllLights(TLState state, bool blinkMode)
{
	for (byte i = 0; i < NUM_DIRECTIONS; ++i) {
		if (carCtl[i] != nullptr) {
			carCtl[i]->setBlinkMode(blinkMode);
			carCtl[i]->setState(state);
		}
		if (pedCtl[i] != nullptr) {
			pedCtl[i]->a->setBlinkMode(blinkMode);
			pedCtl[i]->a->setState(state);
			pedCtl[i]->b->setBlinkMode(blinkMode);
			pedCtl[i]->b->setState(state);
		}
	}
}

void IntersectionControl::updateVehicleLight(byte index, long currentMillis)
{
	TrafficLight *tl = carCtl[index];
	switch (tl->getState()) {
		case TLState::RED:
			if (currentMillis - carLastMillis[index] >= redTime) {
				tl->setState(TLState::GREEN);
				carLastMillis[index] = currentMillis;
			}
			break;
		case TLState::GREEN:
			if (currentMillis - carLastMillis[index] >= greenTime) {
				tl->setState(TLState::YELLOW);
				carLastMillis[index] = currentMillis;
			}
			break;
		case TLState::YELLOW:
			if (currentMillis - carLastMillis[index] >= yellowTime) {
				tl->setState(TLState::RED);
				carLastMillis[index] = currentMillis;
			}
			break;
		default:
			break;
	}
}

void IntersectionControl::updatePedLight(byte index, long currentMillis)
{
	_PedCrossing *ped = pedCtl[index];
	switch (ped->a->getState()) {
		case TLState::RED:
			if (currentMillis - pedLastMillis[index] >= redTime) {
				ped->a->setState(TLState::GREEN);
				ped->b->setState(TLState::GREEN);
				pedLastMillis[index] = currentMillis;
			}
			break;
		case TLState::GREEN:
			if (currentMillis - pedLastMillis[index] >= (greenTime + yellowTime)) {
				ped->a->setState(TLState::RED);
				ped->b->setState(TLState::RED);
				pedLastMillis[index] = currentMillis;
			}
			break;
		default:
			break;
	}
}

void IntersectionControl::initNormalMode()
{
	/* N/S: cars - GREEN, peds - RED;
	   E/W: cars - RED, peds - GREEN; */
	carCtl[NORTH]->setState(TLState::GREEN);
	carCtl[SOUTH]->setState(TLState::GREEN);
	carCtl[EAST]->setState(TLState::RED);
	carCtl[WEST]->setState(TLState::RED);
	
	pedCtl[NORTH]->a->setState(TLState::RED);
	pedCtl[SOUTH]->a->setState(TLState::RED);
	pedCtl[EAST]->a->setState(TLState::GREEN);
	pedCtl[WEST]->a->setState(TLState::GREEN);
	
	pedCtl[NORTH]->b->setState(TLState::RED);
	pedCtl[SOUTH]->b->setState(TLState::RED);
	pedCtl[EAST]->b->setState(TLState::GREEN);
	pedCtl[WEST]->b->setState(TLState::GREEN);
}