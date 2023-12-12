#include "TrafficLight.h"

TrafficLight::TrafficLight(char id, uint8_t greenPin, uint8_t yellowPin, uint8_t redPin)
    : id(id), greenPin(greenPin), yellowPin(yellowPin), redPin(redPin)
{
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
}

void TrafficLight::setState(TrafficLightState state)
{
    Serial.print("semaphore ");
    Serial.print(id);
    Serial.print(" ");
    Serial.print("set state to ");
    switch (state)
    {
    case GO:
        Serial.println("GO");
        digitalWrite(greenPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, LOW);
        break;
    case WAIT:
        Serial.println("WAIT");
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, LOW);
        break;
    case STOP:
        Serial.println("STOP");
        digitalWrite(greenPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(redPin, HIGH);
        break;
    }
}