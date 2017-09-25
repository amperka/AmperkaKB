#ifndef _AMPERKA_KB_H_
#define _AMPERKA_KB_H_

#include <Arduino.h>

// нажатие кнопки 
#define ON_PRESS        1
// кнопка удерживается нажатой	
#define ON_PRESS_LONG   2
// отпускаие кнопки
#define ON_RELEASE      3

// типы клавиатур
#define	KB1x4       0
#define KB4x3       1
#define KB4x4       2

class AmperkaKB
{
public:
    AmperkaKB(uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255);
    // инициализация клавиатуры
    void begin(uint8_t typeKB, uint32_t timeHold = 2000);
    // считывание данных с кнопки
    void read();
    // определение нажатой кнопки
    bool justPressed() const;
    // определение отжатой кнопки
    bool justReleased() const;
    // определение зажатие кнопки
    bool isHold() const;
    // цифровое обозначение кнопки
    uint8_t	getNum = 0;
    // буквенное обозначение номера кнопки
    char getChar = 0;
private:
    // тип подключённой клавиатуры
    uint8_t _typeKB;
    // номера выводов к которым подключена клавиатура
    uint8_t	_pinsKB[8];
    // время длительного зажатия кнопки
    uint32_t _timeHold;
    // состояние системы
    uint8_t _state;
    // номер сейчас нажатой кнопки
    uint8_t	_numberKeyNow;
    // номер ранее нажатой кнопки
    uint8_t	_numberKeyWas = 255;
    // время нажатия кнопки
    uint32_t _msNumberKeyState;
    // длинное нажатие
    uint8_t _numberKeyNowLong;
    // номер подмассива для вывода информации
    uint8_t	_massItem;
    // массив цифровых обозначений номера кнопки для переменной getNum
    uint8_t	_massNumberKey[3][16] =	{
        {0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
        {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xE, 0x0, 0xF, 0x0, 0x0, 0x0, 0x0},
        {0x1, 0x2, 0x3, 0xA, 0x4, 0x5, 0x6, 0xB, 0x7, 0x8, 0x9, 0xC, 0xE, 0x0, 0xF, 0xD}
    };
    // массив буквенных обозначений номера кнопки для переменной getChar
    char _massCharKey[3][16] = {
        {'1', '2', '3', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '0', '#', '0', '0', '0', '0'},
        {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'}
    };
    // определение номера кнопки нажатой в данный момент времени
    void _findPressKeyNow();
};

#endif