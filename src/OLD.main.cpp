#include <Arduino.h>

#define LED 13

class Clock
{
  private:
    unsigned long time = 0;

  public:
    unsigned long stamp()
    {
        this->time = millis();
        return time;
    }

    unsigned long timeSinceLastTimestamp()
    {
        return millis() - this->time;
    }
};

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
    TrafficLightState state;
    uint8_t greenPin;
    uint8_t yellowPin;
    uint8_t redPin;

  public:
    void setState(TrafficLightState state)
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

  public:
    TrafficLight(char id, TrafficLightState initialState, uint8_t greenPin, uint8_t yellowPin, uint8_t redPin)
        : id(id), state(initialState), greenPin(greenPin), yellowPin(yellowPin), redPin(redPin)
    {
        pinMode(greenPin, OUTPUT);
        pinMode(yellowPin, OUTPUT);
        pinMode(redPin, OUTPUT);
        setState(initialState);
    }

    void nextState()
    {
        switch (this->state)
        {
        case TrafficLightState::GO:
            setState(TrafficLightState::WAIT);
            break;
        case TrafficLightState::WAIT:
            setState(TrafficLightState::STOP);
            break;
        case TrafficLightState::STOP:
            setState(TrafficLightState::GO);
            break;
        }
    }
};

class TrafficLightController
{
  private:
    bool active = false;
    uint8_t counter = 0;
    TrafficLight *semaphoreA;
    TrafficLight *semaphoreB;

  public:
    TrafficLightController()
    {
        Serial.println("Setting up semaphore A...");
        semaphoreA = new TrafficLight('A', TrafficLightState::GO, 2, 3, 4);
        Serial.println("Setting up semaphore B...");
        semaphoreB = new TrafficLight('B', TrafficLightState::STOP, 8, 9, 10);
    }

    void update()
    {
        if (this->active)
        {
            counter++;

            if (counter == 1)
            {
                semaphoreA->setState(TrafficLightState::GO);
                semaphoreB->setState(TrafficLightState::STOP);
            }
            else if (counter == 4)
            {
                semaphoreA->setState(TrafficLightState::WAIT);
            }
            else if (counter == 5)
            {
                semaphoreA->setState(TrafficLightState::STOP);
                semaphoreB->setState(TrafficLightState::GO);
            }
            else if (counter == 8)
            {
                semaphoreB->setState(TrafficLightState::WAIT);
                counter = 0;
            }
        }
    }

    void toggle()
    {
        this->active = !this->active;
        if (this->active)
            Serial.println("TrafficLightController activated");
        else
            Serial.println("TrafficLightController deactivated");
    }
};

unsigned long time;
TrafficLightController controller;
Clock clock = Clock();

void setup()
{
    Serial.begin(9600);
    Serial.println("System initializing...");
    controller = TrafficLightController();
    controller.toggle();

    time = millis();
    Serial.println("System initialized successfully");
}

void loop()
{
    if (clock.timeSinceLastTimestamp() >= 1000)
    {
        controller.update();
        clock.stamp();
    }
}