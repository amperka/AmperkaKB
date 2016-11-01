// подключаем библиотеку для работы с матричной клавиатурой
#include <AmperkaKB.h>

// создаём объект для работы с матричной клавиатурой
// указывая номера arduino подключенные к шлейфу клавиатуры
// начиная с первого вывода шлейфа
AmperkaKB KB(6, 5, 4, 3, 2);

void setup()
{
  // открываем монитор Serial порта
  Serial.begin(9600);
  // указываем тип клавиатуры
  KB.begin(KB1x4);
}

void loop()
{
  // определяем отжатие кнопки
  // KB.onRelease()
  // определяем зажатие кнопки
  // KB.isPressed()
  // опеределяем нажатие кнопки
  if (KB.onPress()) {
    // печатаем номер кнопки и её символ в последовательный порт
    Serial.print("Key is press ");
    Serial.print(KB.getNum);
    Serial.print(" = \"");
    Serial.print(KB.getChar);
    Serial.println("\"");
  }
}
