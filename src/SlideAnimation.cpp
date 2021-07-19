#include "SlideAnimation.h"

SlideAnimation::SlideAnimation(LedStrip *strip, unsigned int count, unsigned int speed) {
    _state = SlideAnimation::OFF;
    _count = count;
    _leftPosition = 0;
    _endPosition = count - 1;
    _rightPosition = _endPosition;
    _speed = speed;
    _lastMillis = millis();
    _strip = strip;
}

void SlideAnimation::turnOn(ColourProvider* colourProvider) {
    if (_state == SlideAnimation::OFF || _state == SlideAnimation::TURNING_OFF) {
        _state = SlideAnimation::TURNING_ON;
    }
};

void SlideAnimation::turnOff(ColourProvider* colourProvider) {
    if (_state == SlideAnimation::ON || _state == SlideAnimation::TURNING_ON) {
        _state = SlideAnimation::TURNING_OFF;
    }
};

void SlideAnimation::loop(ColourProvider* colourProvider) {
    if (_state == SlideAnimation::TURNING_ON) {
        handleTurningOn(colourProvider);
    } else if (_state == SlideAnimation::TURNING_OFF) {
        handleTurningOff(colourProvider);
    }
};

void SlideAnimation::handleTurningOn(ColourProvider* colourProvider) {
    unsigned long currentMillis = millis();
    if (currentMillis > (_lastMillis + _speed)) {
        _strip -> setPixelColour(_leftPosition, colourProvider -> getColour(_leftPosition));
        _strip -> setPixelColour(_rightPosition, colourProvider -> getColour(_rightPosition));
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

void SlideAnimation::handleTurningOff(ColourProvider* colourProvider) {
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