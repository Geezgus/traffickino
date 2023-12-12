#pragma once

#ifndef _TRAFFIC_CONTROLLER_H
#define _TRAFFIC_CONTROLLER_H

#include <Arduino.h>

#include <TrafficLightSystem.h>

class TrafficController
{
  private:
    TrafficLightSystem trafficSystem;
    unsigned long lastEventTime;
    uint8_t eventIndex;

  public:
    TrafficController();
    void start();
    void processEvents();
};

#endif // _TRAFFIC_CONTROLLER_H