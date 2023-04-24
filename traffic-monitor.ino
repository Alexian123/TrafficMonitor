#include <TrafficLight.h>
#include <IntersectionControl.h>

using namespace TrafficMonitor;

TrafficLight tl(1, 2, 3);

void setup() {
  tl.setState(TLState::RED);
  tl.setBlinkMode(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  tl.run();
}
