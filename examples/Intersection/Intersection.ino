#include <TrafficMonitor.h>

TrafficLight *tl[MAX_NUM_TL];
IntersectionControl ctl;

void setup() {
  tl[0] = new TrafficLight(13, 11, 12);  // car N
  tl[1] = new TrafficLight(10, 8, 9);  // car S
  tl[2] = new TrafficLight(7, 5, 6);  // car E
  tl[3] = new TrafficLight(4, 2, 3);  // car W
  tl[4] = new TrafficLight(0, 0, 0);  // ped N a
  tl[5] = new TrafficLight(0, 0, 0);  // ped N b
  tl[6] = new TrafficLight(0, 0, 0); // ped S a
  tl[7] = new TrafficLight(0, 0, 0);  // ped S b
  tl[8] = new TrafficLight(0, 0, 0);  // ped E a
  tl[9] = new TrafficLight(0, 0, 0);  // ped E b
  tl[10] = new TrafficLight(0, 0, 0);  // ped W a
  tl[11] = new TrafficLight(0, 0, 0);  // ped W b
  
  // cars
  ctl.addVehicleTrafficLight(Direction::NORTH,  tl[0]);
  ctl.addVehicleTrafficLight(Direction::SOUTH,  tl[1]);
  ctl.addVehicleTrafficLight(Direction::EAST,   tl[2]);
  ctl.addVehicleTrafficLight(Direction::WEST,   tl[3]);

  // pedestrians
  ctl.addPedestrianCrossing(Direction::NORTH,   tl[5], tl[6]);
  ctl.addPedestrianCrossing(Direction::SOUTH,   tl[7], tl[8]);
  ctl.addPedestrianCrossing(Direction::EAST,    tl[9], tl[10]);
  ctl.addPedestrianCrossing(Direction::WEST,    tl[11], tl[12]);

  // start in normal mode
  ctl.changeState(ControlState::NORMAL);
}

void loop() {
  ctl.run();
}