#include <TrafficMonitor.h>

using namespace TrafficMonitor;

TrafficLight *tl[MAX_NUM_TL];
IntersectionControl ctl;

void setup() {
  tl[0] = new TrafficLight(13, 11, 12);  // car N
  tl[1] = new TrafficLight(10, 8, 9);  // car S
  tl[2] = new TrafficLight(7, 5, 6);  // car E
  tl[3] = new TrafficLight(4, 2, 3);  // car W

  ctl.addVehicleTrafficLight(Direction::NORTH,  tl[0]);
  ctl.addVehicleTrafficLight(Direction::SOUTH,  tl[1]);
  ctl.addVehicleTrafficLight(Direction::EAST,   tl[2]);
  ctl.addVehicleTrafficLight(Direction::WEST,   tl[3]);

  SerialHandler::begin(9600);
}

void loop() {
  SerialHandler::run(ctl);
  ctl.run();
}