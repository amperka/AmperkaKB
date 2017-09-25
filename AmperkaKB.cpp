#include "AmperkaKB.h"

AmperkaKB::AmperkaKB(uint8_t pin1KB, uint8_t pin2KB, uint8_t pin3KB, uint8_t pin4KB, uint8_t pin5KB, uint8_t pin6KB, uint8_t pin7KB, uint8_t pin8KB) {
    _pinsKB[0] = pin1KB;
    _pinsKB[1] = pin2KB;
    _pinsKB[2] = pin3KB;
    _pinsKB[3] = pin4KB;
    _pinsKB[4] = pin5KB;
    _pinsKB[5] = pin6KB;
    _pinsKB[6] = pin7KB;
    _pinsKB[7] = pin8KB;
}

// инициализация клавиатуры
void AmperkaKB::begin(uint8_t typeKB, uint32_t timeHold) {
    _timeHold = timeHold;
    _typeKB = typeKB;
    // определяем номер подмассива для вывода информации
    switch (_typeKB) {
        case KB1x4:
            _massItem = 0;
        break;
        case KB4x3:
            _massItem = 1;
        break;
        case KB4x4:
            _massItem = 2;
        break;
    }
    // устанавливаем выводы в соответствующие им состояния
    switch (_typeKB) {
        case KB1x4:
            // переводим вывод в режим передачи и устанавливаем состояние «1»
            pinMode(_pinsKB[0], OUTPUT);
            digitalWrite(_pinsKB[0], HIGH);
            // переводим выводы в режим приёма с подтягивающим резистором
            pinMode(_pinsKB[1], INPUT_PULLUP);
            pinMode(_pinsKB[2], INPUT_PULLUP);
            pinMode(_pinsKB[3], INPUT_PULLUP);
            pinMode(_pinsKB[4], INPUT_PULLUP);
        break;
        case KB4x3:
            // переводим выводы в режим передачи и устанавливаем состояние «1»
            pinMode(_pinsKB[0], OUTPUT);
            pinMode(_pinsKB[1], OUTPUT);
            pinMode(_pinsKB[2], OUTPUT);
            pinMode(_pinsKB[3], OUTPUT);
            digitalWrite(_pinsKB[0], HIGH);
            digitalWrite(_pinsKB[1], HIGH);
            digitalWrite(_pinsKB[2], HIGH);
            digitalWrite(_pinsKB[3], HIGH);
            // переводим вывод в режим приёма с подтягивающим резистором
            pinMode(_pinsKB[4], INPUT_PULLUP);
            pinMode(_pinsKB[5], INPUT_PULLUP);
            pinMode(_pinsKB[6], INPUT_PULLUP);
        break;
        case KB4x4:
            // переводим выводы в режим передачи и устанавливаем состояние «1»
            pinMode(_pinsKB[0], OUTPUT);
            pinMode(_pinsKB[1], OUTPUT);
            pinMode(_pinsKB[2], OUTPUT);
            pinMode(_pinsKB[3], OUTPUT);
            digitalWrite(_pinsKB[0], HIGH);
            digitalWrite(_pinsKB[1], HIGH);
            digitalWrite(_pinsKB[2], HIGH);
            digitalWrite(_pinsKB[3], HIGH);
            // переводим вывод в режим приёма с подтягивающим резистором
            pinMode(_pinsKB[4], INPUT_PULLUP);
            pinMode(_pinsKB[5], INPUT_PULLUP);
            pinMode(_pinsKB[6], INPUT_PULLUP);
            pinMode(_pinsKB[7], INPUT_PULLUP);
        break;
    }
}

// считывание состояние кнопки
void AmperkaKB::read() {
    _state = false;
    //определяем номер кнопки нажатой в данный момент времени
    _findPressKeyNow();
    if (_numberKeyNow != 255 && _numberKeyNow != _numberKeyWas) {
        // определяем номер кнопки нажатой в данный момент времени
        getNum =  _massNumberKey[_massItem][_numberKeyNow];
        getChar = _massCharKey[_massItem][_numberKeyNow];
        _numberKeyNowLong = _numberKeyNow;
        _msNumberKeyState = millis();
        _state = ON_PRESS;
    }

    if (_numberKeyNow == 255 && _numberKeyNow != _numberKeyWas && _numberKeyWas != 255 && _numberKeyNowLong != 255) {
        // определяем номер зажатой кнопки в данный момент времени
        getNum = _massNumberKey[_massItem][_numberKeyWas];
        getChar =_massCharKey[_massItem][_numberKeyWas];
        _state = ON_RELEASE;
    }

    if (_numberKeyNow != 255 && _numberKeyNowLong != 255 && millis() - _msNumberKeyState > _timeHold) {
        // определяем номер кнопки отжатой в данный момент времени
        getNum = _massNumberKey[_massItem][_numberKeyNow];
        getChar = _massCharKey[_massItem][_numberKeyNow];
        _numberKeyNowLong = 255;
        _msNumberKeyState = millis();
        _state = ON_PRESS_LONG;
    }
    // запоминаем нажатую кнопку
    _numberKeyWas = _numberKeyNow;
}

// определение нажимаемой кнопки
bool AmperkaKB::justPressed() const {
    return _state == ON_PRESS ? 1 : 0;
}

// определение отжимаемой кнопки
bool AmperkaKB::justReleased() const {
    return _state == ON_RELEASE ? 1 : 0;
}

// определение отжимаемой кнопки
bool AmperkaKB::isHold() const {
    return _state == ON_PRESS_LONG  ? 1 : 0;
}

// определяем номер кнопки нажатой в данный момент времени
void AmperkaKB::_findPressKeyNow() {
    _numberKeyNow = 255;
    //определяем номер кнопки нажатой в данный момент времени
    switch (_typeKB) {
        case KB1x4:
            // устанавливаем состояние вывода 0 «LOW»
            digitalWrite(_pinsKB[0], LOW);
            // проверяем состояние вывода 1
            if (!digitalRead(_pinsKB[1])) {
                _numberKeyNow = 1;
            }
            // проверяем состояние вывода 2
            if (!digitalRead(_pinsKB[2])) {
                _numberKeyNow = 0;
            }
            //  проверяем состояние вывода 3
            if (!digitalRead(_pinsKB[3])) {
                _numberKeyNow = 3;
            }
            //  проверяем состояние вывода 4
            if (!digitalRead(_pinsKB[4])) {
                _numberKeyNow = 2;
            }
            // устанавливаем состояние вывода 0 «HIGH»
            digitalWrite(_pinsKB[0], HIGH);
        break;
        case KB4x3:
            for (uint8_t i = 0; i < 4; i++) {
                // прижимаем один из выводов 0-3 к земле
                digitalWrite(_pinsKB[i], LOW);
                for (uint8_t j = 0; j < 3; j++) {
                    // проверяем состояние выводов 4-6
                    if (!digitalRead(_pinsKB[j + 4])) {
                        _numberKeyNow = i * 3 + j;
                    }
                }
                // подтягиваем ранее прижатые выводы 0-3
                digitalWrite(_pinsKB[i], HIGH);
            }
        break;
        case KB4x4:
            for (uint8_t i = 0; i < 4; i++) {
                // прижимаем один из выводов 0-3 к земле
                digitalWrite(_pinsKB[i], LOW);
                for (uint8_t j = 0; j < 4; j++) {
                    // проверяем состояние выводов 4-7
                    if (!digitalRead(_pinsKB[j + 4])) {
                        _numberKeyNow = i * 4 + j;
                    }
                }
                // подтягиваем ранее прижатые выводы 0-3
                digitalWrite(_pinsKB[i], HIGH);
            }
        break;
    }
}
