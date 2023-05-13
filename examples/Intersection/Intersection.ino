#include <TrafficMonitor.h>

using namespace TrafficMonitor;

TrafficLight *tl[MAX_NUM_TL];
IntersectionControl ctl;

void setup() {
  // car traffic lights
  tl[0] = new TrafficLight(13, 12, 11);  // W
  tl[1] = new TrafficLight(13, 12, 11);  // E
  tl[2] = new TrafficLight(10, 9, 8);  // N
  tl[3] = new TrafficLight(10, 9, 8);  // S
  
  // pedestrian crossing light
  tl[4] = new TrafficLight(7, 6, 5);  // N a
  tl[5] = new TrafficLight(7, 6, 5);  // N b
  tl[6] = new TrafficLight(4, 3, 2);  // S a
  tl[7] = new TrafficLight(4, 3, 2);  // S b
  tl[8] = new TrafficLight(A0, A1, A2);  // W a
  tl[9] = new TrafficLight(A0, A1, A2);  // W b
  tl[10] = new TrafficLight(A3, A4, A5);  // E a
  tl[11] = new TrafficLight(A3, A4, A5);  // E b
  
  ctl.addVehicleTrafficLight(Direction::WEST, tl[4]);
  ctl.addVehicleTrafficLight(Direction::EAST, tl[1]);
  ctl.addVehicleTrafficLight(Direction::NORTH, tl[2]);
  ctl.addVehicleTrafficLight(Direction::SOUTH, tl[3]);
  
  ctl.addPedestrianCrossing(Direction::NORTH, tl[4], tl[5]);
  ctl.addPedestrianCrossing(Direction::SOUTH, tl[6], tl[7]);
  ctl.addPedestrianCrossing(Direction::WEST, tl[8], tl[9]);
  ctl.addPedestrianCrossing(Direction::EAST, tl[10], tl[11]);

  SerialHandler::begin(9600);
}

void loop() {
  SerialHandler::run(ctl);
  ctl.run();
}