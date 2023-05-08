#pragma once

#include "Arduino.h"
#include "TrafficLight.h"

namespace TrafficMonitor
{
	enum ControlState
	{
		DISABLED = 0x0,
		NORMAL,
		BLINK_YELLOW,
		DEBUG
	};
	
	enum Direction
	{
		NORTH 	= 0,
		SOUTH 	= 1,
		EAST 	= 2,
		WEST 	= 3
	};
	
	class IntersectionControl
	{
	private:
		static constexpr byte NUM_DIRECTIONS = 4;
		ControlState state = DISABLED;
		
		// For DEBUG state
		TLState debugTLState = TLState::OFF;
		bool debugBlinkMode = false;
	
		struct _PedCrossing		// traffic light pairs (will be in sync)
		{
			TrafficLight *a;
			TrafficLight *b;
		};
					
		_PedCrossing *pedCtl[NUM_DIRECTIONS];	// pedestrian traffic lights
		TrafficLight *carCtl[NUM_DIRECTIONS];	// vehicle traffic lights
		
		// timers (in ms)
		int redTime = 6000;
		int greenTime = 3000;
		int yellowTime = 1500;
		long pedLastMillis[NUM_DIRECTIONS];
		long carLastMillis[NUM_DIRECTIONS];
	
	public:
		IntersectionControl();
		IntersectionControl(int redTime, int greenTime, int yellowTime);
		~IntersectionControl();
		
		void run();	// call inside loop
		
		bool addPedestrianCrossing(Direction dir, TrafficLight *a, TrafficLight *b);
		bool addVehicleTrafficLight(Direction dir, TrafficLight *tl);
		void changeState(ControlState state);
		void setDebugParams(TLState state, bool blinkMode);
		
	private:
		void runNormal();	// run with proper timing for each light
		void runSynced();	// run with all lights on at the same time
		void setAllLights(TLState state, bool blinkMode);
		
		// update lights based on timer (normal mode)
		void updateVehicleLight(byte index, long currentMillis);
		void updatePedLight(byte index, long currentMillis);
		
		void initNormalMode();	// starting point for normal mode
	};
	
}