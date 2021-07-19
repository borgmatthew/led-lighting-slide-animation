#ifndef LIBRARIES_SLIDEANIMATION_H
#define LIBRARIES_SLIDEANIMATION_H

#include <Animation.h>
#include <LedStrip.h>
#include <ColourProvider.h>

class SlideAnimation : public Animation {

public:
    SlideAnimation(LedStrip *strip, unsigned int count, unsigned int speed);
    void turnOn(ColourProvider* colourProvider);
    void turnOff(ColourProvider* colourProvider);
    void loop(ColourProvider* colourProvider);
    void resetAnimation();

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

    void handleTurningOn(ColourProvider* colourProvider);
    void handleTurningOff(ColourProvider* colourProvider);
};

#endif //LIBRARIES_SLIDEANIMATION_H
