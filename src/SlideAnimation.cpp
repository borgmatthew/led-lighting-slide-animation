#include "SlideAnimation.h"

SlideAnimation::SlideAnimation(LedStrip *strip, unsigned int count, unsigned int speed, uint32_t colour) {
    _state = SlideAnimation::OFF;
    _count = count;
    _leftPosition = 0;
    _endPosition = count - 1;
    _rightPosition = _endPosition;
    _speed = speed;
    _lastMillis = millis();
    _strip = strip;
    _colour = colour;
}

void SlideAnimation::turnOn() {
    if (_state == SlideAnimation::OFF || _state == SlideAnimation::TURNING_OFF) {
        _state = SlideAnimation::TURNING_ON;
    }
};

void SlideAnimation::turnOff() {
    if (_state == SlideAnimation::ON || _state == SlideAnimation::TURNING_ON) {
        _state = SlideAnimation::TURNING_OFF;
    }
};

void SlideAnimation::loop() {
    if (_state == SlideAnimation::TURNING_ON) {
        handleTurningOn();
    } else if (_state == SlideAnimation::TURNING_OFF) {
        handleTurningOff();
    }
};

void SlideAnimation::handleTurningOn() {
    unsigned long currentMillis = millis();
    if (currentMillis > (_lastMillis + _speed)) {
        _strip -> setPixelColour(_leftPosition, _colour);
        _strip -> setPixelColour(_rightPosition, _colour);
        _strip -> update();

        if (_leftPosition == _rightPosition -1) {
            _state = SlideAnimation::ON;
        }

        if (_leftPosition <= _rightPosition -1) {
            _leftPosition++;
        }

        if (_rightPosition > _leftPosition +1) {
            _rightPosition--;
        }

        _lastMillis = currentMillis;
    }
}

void SlideAnimation::handleTurningOff() {
    unsigned long currentMillis = millis();
    if (currentMillis > (_lastMillis + _speed)) {
        _strip -> setPixelColour(_leftPosition, 0);
        _strip -> setPixelColour(_rightPosition, 0);
        _strip -> update();

        if (_leftPosition == 0 && _rightPosition == _endPosition) {
            _state = SlideAnimation::OFF;
        }

        if (_leftPosition > 0) {
            _leftPosition--;
        }

        if (_rightPosition < _endPosition) {
            _rightPosition++;
        }

        _lastMillis = currentMillis;
    }
}

void SlideAnimation::resetAnimation() {
    _strip -> clear();
    _leftPosition = 0;
    _rightPosition = _endPosition;
    _state = SlideAnimation::OFF;
}

void SlideAnimation::setSpeed(unsigned int speed) {
    _speed = speed;
}

int SlideAnimation::getSpeed() {
    return _speed;
}

void SlideAnimation::setColour(uint32_t colour) {
    _colour = colour;
}

uint32_t SlideAnimation::getColour() {
    return _colour;
}