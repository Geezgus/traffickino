#pragma once

#ifndef _TRAFFIC_LIGHT_SYSTEM_H
#define _TRAFFIC_LIGHT_SYSTEM_H

#include <Arduino.h>
#include <TrafficLight.h>

class TrafficLightSystem
{
  private:
    bool active = false;
    uint8_t stage = 0;
    TrafficLight *semaphoreA;
    TrafficLight *semaphoreB;

  public:
    void nextStage();
    void toggle();
};

#endif // _TRAFFIC_LIGHT_SYSTEM_H
