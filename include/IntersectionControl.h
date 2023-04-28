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
	
		struct _PedCrossing		// traffic light pairs (will be in sync)
		{
			TrafficLight *a;
			TrafficLight *b;
		};
					
		_PedCrossing *pedCtl[NUM_DIRECTIONS];	// pedestrian traffic lights
		TrafficLight *carCtl[NUM_DIRECTIONS];	// vehicle traffic lights
	
	public:
		IntersectionControl();
		~IntersectionControl();
		
		bool addPedestrianCrossing(Direction dir, TrafficLight *a, TrafficLight *b);
		bool addVehicleTrafficLight(Direction dir, TrafficLight *tl);
	};
	
}