// подключаем библиотеку для работы с матричной клавиатурой
#include <AmperkaKB.h>

// создаём объект для работы с матричной клавиатурой
// указывая номера arduino подключенные к шлейфу клавиатуры
// начиная с первого вывода шлейфа
AmperkaKB KB(6, 5, 4, 3, 2, 1, 0);

void setup()
{
  // открываем монитор Serial порта
  Serial.begin(9600);
  // указываем тип клавиатуры
  KB.begin(KB4x3);
  // второй необзятельный параметр:
  // время длительного зажатия кнопки
  // по умолчанию 2000, изменим на 5000 мс
  // KB.begin(KB4x3, 5000);
}

void loop()
{
  // считывание данных с клавиатуры
  KB.read();
  // опеределяем клик кнопки
  if (KB.justPressed()) {
    // печатаем номер кнопки и её символ в последовательный порт
    Serial.print("Key is press ");
    Serial.print(KB.getNum);
    Serial.print(" = \"");
    Serial.print(KB.getChar);
    Serial.println("\"");
  }
  // определяем отжатие кнопки
  if (KB.justReleased()) {
    // печатаем номер кнопки и её символ в последовательный порт
    Serial.print("Key is release ");
    Serial.print(KB.getNum);
    Serial.print(" = \"");
    Serial.print(KB.getChar);
    Serial.println("\"");
  }
  // определяем зажатие кнопки на 3 секунды
  if (KB.isHold()) {
    // печатаем номер кнопки и её символ в последовательный порт
    Serial.print("Key on long press ");
    Serial.print(KB.getNum);
    Serial.print(" = \"");
    Serial.print(KB.getChar);
    Serial.println("\"");
  }
}
