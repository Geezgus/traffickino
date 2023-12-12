#include <TrafficController.h>

TrafficController controller;

void setup()
{
    controller = TrafficController();
    controller.start();
}

void loop()
{
    controller.processEvents();
}