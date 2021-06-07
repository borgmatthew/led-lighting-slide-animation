#ifndef LIBRARIES_SLIDEANIMATION_H
#define LIBRARIES_SLIDEANIMATION_H

#include <Animation.h>
#include <LedStrip.h>

class SlideAnimation : public Animation {

public:
    SlideAnimation(LedStrip *strip, unsigned int count, unsigned int speed, uint32_t colour);
    void turnOn();
    void turnOff();
    void loop();
    void resetAnimation();

    uint32_t getColour();
    void setColour(uint32_t colour);

    int getSpeed();
    void setSpeed(unsigned int speed);

private:
    enum AnimationState {
        TURNING_OFF = 0,
        TURNING_ON = 1,
        ON = 2,
        OFF = 3
    };

    AnimationState _state;
    unsigned int _speed;
    unsigned int _leftPosition;
    unsigned int _count;
    unsigned int _rightPosition;
    unsigned int _endPosition;
    unsigned long _lastMillis;
    LedStrip *_strip;
    uint32_t _colour;

    void handleTurningOn();
    void handleTurningOff();
};

#endif //LIBRARIES_SLIDEANIMATION_H
