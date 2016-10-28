#include "AmperkaKB.h"

AmperkaKB::AmperkaKB (uint8_t pin1KB, uint8_t pin2KB, uint8_t pin3KB, uint8_t pin4KB, uint8_t pin5KB, uint8_t pin6KB, uint8_t pin7KB, uint8_t pin8KB) {
	pinsKB[0] = pin1KB;
	pinsKB[1] = pin2KB;
	pinsKB[2] = pin3KB;
	pinsKB[3] = pin4KB;
	pinsKB[4] = pin5KB;
	pinsKB[5] = pin6KB;
	pinsKB[6] = pin7KB;
	pinsKB[7] = pin8KB;
}

// инициализация клавиатуры
void AmperkaKB::begin(uint8_t i) {
	typeKB = i;
	// определяем номер подмассива для вывода информации
	switch(typeKB) {
		case KB4x4: KB_item_ARR=2; break;
		case KB4x3: KB_item_ARR=2; break;
		case KB1x4: KB_item_ARR=1; break;
	}
	// устанавливаем выводы в соответствующие им состояния
	switch(typeKB) {
		case KB4x4:
		break;
		case KB4x3:
			pinMode(pinsKB[0], OUTPUT); digitalWrite(pinsKB[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
			pinMode(pinsKB[1], OUTPUT); digitalWrite(pinsKB[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
			pinMode(pinsKB[2], OUTPUT); digitalWrite(pinsKB[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
			pinMode(pinsKB[3], OUTPUT); digitalWrite(pinsKB[4], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
			pinMode(pinsKB[4], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
			pinMode(pinsKB[5], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
			pinMode(pinsKB[6], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
		break;
		case KB1x4:
			pinMode(pinsKB[0], OUTPUT); digitalWrite(pinsKB[0], HIGH);			//	переводим вывод в режим передачи и устанавливаем состояние «1»
			pinMode(pinsKB[1], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
			pinMode(pinsKB[2], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
			pinMode(pinsKB[3], INPUT_PULLUP);											//	переводим вывод в режим приёма с подтягивающим резистором
			pinMode(pinsKB[4], INPUT_PULLUP);	
		break;
	}
}

//		определение нажимаемой/отпускаемой/удерживаемой кнопки
bool AmperkaKB::check(uint8_t i) {
	bool n=false; numberKeyNow=255;
    //определяем номер кнопки нажатой в данный момент времени
	switch(typeKB) {
		case KB4x4:
		break;
		case KB4x3:
					for(uint8_t j=0; j<4; j++){	digitalWrite(pinsKB[j], LOW);						//	прижимаем один из выводов 0-3 к земле
					for(uint8_t k=0; k<3; k++){ if(!digitalRead(pinsKB[k+4])){numberKeyNow=j*4+k;}}	//	проверяем состояние выводов 4-6
												digitalWrite(pinsKB[j], HIGH);                     //	подтягиваем ранее прижатые выводы 0-3
					}
				break;
		case KB1x4:
            //  устанавливаем состояние вывода 0 «LOW»
			digitalWrite(pinsKB[0], LOW);
            // проверяем состояние вывода 1
			if (!digitalRead(pinsKB[1])) {
                numberKeyNow = 1;
            }
            // проверяем состояние вывода 2
			if (!digitalRead(pinsKB[2])) {
                numberKeyNow = 0;
            }
            //  проверяем состояние вывода 3
			if (!digitalRead(pinsKB[3])) {
                numberKeyNow = 3;
            }
            //  проверяем состояние вывода 4
			if (!digitalRead(pinsKB[4])) {
                numberKeyNow = 2;
            }
            // устанавливаем состояние вывода 0 «HIGH»
			digitalWrite(pinsKB[0], HIGH);
		break;
	}

    // определяем и выводим ответ
	switch(i) {
		case KEY_PRESS: n= numberKeyNow!=0xFF && numberKeyNow==numberKeyWas					?true:false; getNum=KB_nums_KB[KB_item_ARR][numberKeyNow]; getChar=KB_char_KB[KB_item_ARR][numberKeyNow]; break;
		case KEY_DOWN:  n= numberKeyNow!=0xFF && numberKeyNow!=numberKeyWas					?true:false; getNum=KB_nums_KB[KB_item_ARR][numberKeyNow]; getChar=KB_char_KB[KB_item_ARR][numberKeyNow]; break;
		case KEY_UP:    n= numberKeyNow==0xFF && numberKeyNow!=numberKeyWas && numberKeyWas<255	?true:false; getNum=KB_nums_KB[KB_item_ARR][numberKeyWas]; getChar=KB_char_KB[KB_item_ARR][numberKeyWas]; break;
	}	
    if(n){delay(20);} numberKeyWas=numberKeyNow; return n;
}
