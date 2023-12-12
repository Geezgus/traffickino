#include <Arduino.h>

#include <TrafficController.h>
#include <TrafficLightSystem.h>

TrafficController::TrafficController()
{
    trafficSystem = TrafficLightSystem();
}

void TrafficController::start()
{
    lastEventTime = millis();
    eventIndex = 0;
}

void TrafficController::processEvents()
{
    uint32_t milliseconds[] = {3000, 1000, 3000, 1000};

    unsigned long timeSinceLastEvent = millis() - lastEventTime;
    if (timeSinceLastEvent >= milliseconds[eventIndex])
        trafficSystem.nextStage();
    eventIndex++;
    if (eventIndex > 3)
        eventIndex = 0;
}
