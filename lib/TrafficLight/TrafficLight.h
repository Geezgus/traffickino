#pragma once

#ifndef _TRAFFIC_LIGHT_H
#define _TRAFFIC_LIGHT_H

#include <Arduino.h>

enum TrafficLightState
{
    GO,
    WAIT,
    STOP
};

class TrafficLight
{
  private:
    char id;
    uint8_t greenPin;
    uint8_t yellowPin;
    uint8_t redPin;

  public:
    TrafficLight(char id, uint8_t greenPin, uint8_t yellowPin, uint8_t redPin);
    void setState(TrafficLightState state);
};

#endif // _TRAFFIC_LIGHT_H