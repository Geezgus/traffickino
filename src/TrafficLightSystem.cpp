#include <Arduino.h>
#include <TrafficLight.h>
#include <TrafficLightSystem.h>

TrafficLightSystem::TrafficLightSystem()
{
    Serial.println("Setting up semaphore A...");
    semaphoreA = new TrafficLight('A', 2, 3, 4);
    Serial.println("Setting up semaphore B...");
    semaphoreB = new TrafficLight('B', 8, 9, 10);
}

void TrafficLightSystem::nextStage()
{
    if (this->active)
    {
        stage++;

        if (stage == 1)
        {
            semaphoreA->setState(TrafficLightState::GO);
            semaphoreB->setState(TrafficLightState::STOP);
        }
        else if (stage == 2)
        {
            semaphoreA->setState(TrafficLightState::WAIT);
        }
        else if (stage == 3)
        {
            semaphoreA->setState(TrafficLightState::STOP);
            semaphoreB->setState(TrafficLightState::GO);
        }
        else if (stage == 4)
        {
            semaphoreB->setState(TrafficLightState::WAIT);
            stage = 0;
        }
    }
}

void TrafficLightSystem::toggle()
{
    this->active = !this->active;
    if (this->active)
        Serial.println("TrafficLightController activated");
    else
        Serial.println("TrafficLightController deactivated");
}
