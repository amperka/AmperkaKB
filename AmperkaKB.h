#ifndef _AMPERKA_KB_H_
#define _AMPERKA_KB_H_

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// кнопка удерживается нажатой			
#define	KEY_PRESS	0
// кнопка впервые нажата (после предыдущего вызова функции begin)
#define	KEY_DOWN	1
// кнопка впервые отпущена (после предыдущего вызова функции begin)
#define	KEY_UP		2
// типы клавиатур
#define	KB4x4		0
#define	KB2			1
#define	KB4x3		2
#define	KB1x4		3
class AmperkaKB
{
public:
    AmperkaKB (uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255, uint8_t = 255);
    // инициализация клавиатуры (тип клавиатуры)
    void begin (uint8_t);
    // определение кнопки (реагировать на)
    bool check	(uint8_t = KEY_PRESS);
    uint8_t	getNum = 0;
    char getChar = 32;
private:
    // тип подключённой клавиатуры
    uint8_t typeKB;
    // номера выводов к которым подключена клавиатура
    uint8_t	pinsKB[10];
    // номер сейчас нажатой кнопки
    uint8_t	numberKeyNow;
    // номер ранее  нажатой кнопки
    uint8_t	numberKeyWas = 255;
    // номер подмассива для вывода информации
    uint8_t	KB_item_ARR;
    // цифровое обозначение номера кнопки для переменной getNum
    uint8_t	KB_nums_KB[3][16] =	{
        {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF},
        {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x0},
        {0x1, 0x2, 0x3, 0xA, 0x4, 0x5, 0x6, 0xB, 0x7, 0x8, 0x9, 0xC, 0xE, 0x0, 0xF, 0xD}
    };
    // буквенное обозначение номера кнопки для переменной getChar
    char KB_char_KB[3][16] = {
        {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '0'},
        {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'}
    };
};

#endif