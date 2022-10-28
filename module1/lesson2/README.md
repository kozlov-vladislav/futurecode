1.2 Логические и битовые операции. Разветвления хода выполнения программы
=============

__Логические операции__
Речь пойдет про операторы сравнения и `&&`, `||`, `!`.



```c++
#include <iostream>

int main() {
    bool a = 5 < 6; // 1
    bool b = 5.5 > 17; // 0
    bool c = 'z' <= 'a'; // 0
    bool d = 'a' >= 'a'; // 1
    std::cout << a << " " << b << " " << c << " " << d << "\n";
    return 0;
}
```

```c++
#include <iostream>

int main() {
    bool a = 'a' == 'a'; // 1
    bool b = 'a' != 'b'; // 1
    bool c = 3 != 3.14; // 0
    bool d = 3 == 3.0; // 1
    std::cout << a << " " << b << " " << c << " " << d << "\n";
    return 0;
}
```

Далее про `&&`, `||`, `!`.


```c++
#include <iostream>

int main() {
    bool t = true;
    bool f = false;
    bool a = f && t; // 0
    bool b = f && f; // 0
    bool c = t && t; // 1

    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}
```

```c++
#include <iostream>

int main() {
    bool t = true;
    bool f = false;
    bool a = f || t; // 1
    bool b = f || f; // 0
    bool c = t || t; // 1

    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}
```

```c++
#include <iostream>

int main() {
    bool t = true;
    bool f = false;
    bool a = !f; // 1
    bool b = !t; // 0

    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}
```


Стоит заметить, что эти операторы предполагают тип `bool`, но можно писать и числовые типы данных
```c++
#include <iostream>

int main() {
    bool a = 5;
    bool b = -6;
    bool c = 3.14;
    std::cout << a << " " << b << " " << c << "\n";
    return 0;
}
```

```c++
#include <iostream>

int main() {
    bool a = !5
    bool b = !(-1);
    bool c = !0;
    std::cout << a << " " << b << " " << c << "\n"; // 0 0 1
    return 0;
}
```
Также про порядок операторов

https://en.cppreference.com/w/cpp/language/operator_precedence

А именно
```c++
#include <iostream>

int main() {
    int x;
    int y;
    std::cin >> x >> y;
    std::cout << x == y; // Так нельзя
    std::cout << (x == y); // Так можно
    std::cout << x && y; // Так нельзя
    std::cout << (x && y); // Так можно
    // и т.д.

    bool f = x == y || x == 5 && y == 6;
    bool g = (x == y || x == 5) && y == 6;
    // f и g -- разные величины
    return 0;
}
```


__Битовые операции__

Речь пойдет про операторы  `&`, `|`, `^`, `~`, `<<` , `>>`.

Эти операторы работают с битами чисел, поэтому детям нужно рассказать, как хранятся числа в целых типах. В частности, они работают только с целыми типами данных, т.е. условно с `double` их не получится использовать.


_`z = x & y`_: берет соответствующие биты `x` и `y` и их логическое `и` записывает в бит числа `z`

_`z = x | y`_: берет соответствующие биты `x` и `y` и их логическое `или` записывает в бит числа `z`

_`z = x ^ y`_: берет соответствующие биты `x` и `y` и их `xor` записывает в бит числа `z`

_`z = ~x`_: инвертирует биты `x` и записывает их в `z`

_`z = x << k`_: сдвигает биты `x` влево на k и записывает результат в `z`

_`z = x >> k`_: сдвигает биты `x` вправо на k и записывает результат в `z`


```c++
#include <iostream>
#include <bitset>

int main() {
    int x, y;
    std::cin >> x >> y;
    //         x = 5 = 00000000000000000000000000000101
    //        y = 11 = 00000000000000000000000000001011
    int a = x & y;  // 00000000000000000000000000000001
    int b = x ^ y;  // 00000000000000000000000000001010
    int c = x | y;  // 00000000000000000000000000001111
    int d = ~x;     // 11111111111111111111111111111010
    int e = x << 5; // 00000000000000000000000010100000
    int d = y >> 1; // 00000000000000000000000000000101
    return 0;
}
```


Для того чтобы показывать результат выполнения операторов, удобно выводить числа в двоичном виде.

Это можно сделать, например, так:


```c++
#include <iostream>
#include <bitset>

int main() {
    int y;
    std::cin >> y;
    std::bitset<32> x(y);
    std::cout << x;
    return 0;
}
```
`std::bitset` -- шаблонный класс, его параметр - количество бит, в примере их 32. Детям необязательно понимать, как он работает, более того, им необязательно будет им пользоваться. Пока это просто волшебный синтаксис

```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    int y;
    std::cin >> x >> y;
    int z = x & y; // битовое и
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```
Интересное применение, узнать четность числа:

```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    int z = x & 1
    std::cout << z; // 1 - если нечетно, 0 - если четно
    return 0;
}
```

```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    int y;
    std::cin >> x >> y;
    int z = x | y; // битовое или
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```
```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    int y;
    std::cin >> x >> y;
    int z = x ^ y; // битовый xor
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```
Про xor (`^`) стоит отдельно рассказать, что это обратимая операция, а именно a ^ b ^ a = b

```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    std::cin >> x;
    int z = ~x; // инверсия битов
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```
Теперь про `<<` и `>>`

`x << k` Сдвигает у числа x биты влево на k позиций, аналогично `>>` -- вправо на k

```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    std::cin >> x;
    int z = x << 2;
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```

```c++
#include <iostream>
#include <bitset>

int main() {
    int x;
    std::cin >> x;
    int z = x >> 2;
    std::bitset<32> bits(z);
    std::cout << bits;
    return 0;
}
```
Более того, смещение не влияет на знак числа, нужно это отдельно показать.

Вообще, эти операторы полезны вот в чем, `x >> 1` по сути -- деление на 2 нацело, и в целом `x >> k` деление на 2 в k-ой степени. Аналогично с `x << 1` - умножение на 2, `x << k`, умножение на 2 в k-ой. Причем это работает намного быстрее, чем обычные арифметические `*` и `/`. Это и нужно рассказать детям.

Например, как быстро получить число 2 в степени k? Это всего лишь `1 << k`.

---
_Задача_: Узнать k-ый бит числа

_Решение_:
```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    int k;
    std::cin >> k;
    bool bit = (x >> k) & 1
    std::cout << bit;
    return 0;
}
```
---

_Задача_: Инвертировать k-ый бит числа

_Решение_:
```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    int k;
    std::cin >> k;
    int ans = x ^ (1 << k);
    std::cout << ans;
    return 0;
}
```
---


__Разветвления хода выполнения программы__
Речь пойдет про `if`, `else` и `switch`.

```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    if (x < 0) {
        x *= -1;
    }
    std::cout << x; // Выводит модуль числа
    return 0;
}
```

Рассказать, что в круглых скобках `if` можно писать любое выражение, которое приводимо к `bool` так, как обсуждалось ранее.
```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    if (x & 1) {
        x *= 2;
    }
    std::cout << x; // Нечетные числа умножает на 2
    return 0;
}
```
Более того, фигурные скобки можно не писать, если в теле `if` стоит одно выражение, и нужно писать, если их несколько.
```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    if (x > 0) { // ok
        x *= 2;
    }
    if (x > 0) // ok
        x *= 2;

    if (x == 6) { // ok
        int y;
        std::cin >> y;
        std::cout << 2 * y;
    }
    if (x == 6) // не ok
        int y;
        std::cin >> y;
        std::cout << 2 * y;
    
    return 0;
}
```

Рассказать, про `else` и `else if`

```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    if (x > 0) { // ok
        x *= 2;
    }
    else if (x < 0) { // ok
        x *= 2;
    } else {
        x = 100;
    }
    
    return 0;
}
```
Правила для фигурных скобках такие же

Пример `switch`:
```c++
#include <iostream>

int main() {
    int x;
    std::cin >> x;
    switch (x) {
        case 0:
            std::cout << x;
            break;
        case 1:
            x *= 5;
            std::cout << x;
            break;
        default:
            x = 100;
            break;
    }
    
    return 0;
}
```
Как работает switch.

В скобках указана переменная `x`.

Далее он пробегается по `case` сверху вниз пока не встретит значение, равное этому `x`. Если в очередном `case` он его встретит, то зайдет в блок `case` и будет выполнять указанные там инструкции. В конце, если есть слово `break` то он выйдет из конструкции `switch` целиком, а если оно не указано, то продолжит идти дальше.

Если он дойдет до слова `default`, то обязательно войдет в его конструкцию. При этом default писать не обязательно, и писать можно в любом месте.

Также, если не стоит `break` в конце `case` то это явно намек на ошибку, тк в реальности мало случаев, когда его не ставят(см пример из классной).

_Уточнение_:
1. `x` - должна быть целочисленна, либо явно приводиться к целому типу.
2. Значения в case должны быть константными, т.е. точно не переменные.
3. Все значения в case приводятся к типу `x`
4. В блоке `case` нельзя инициализировать переменные


Далее `switch` с несколькими ошибками
```c++
#include <iostream>

int main() {
    char x;
    std::cin >> x;
    char y = 'b';
    const char z = 'z';
    switch (x) {
        case 3.14: // нельзя приводить double к char
            std::cout << x;
            break;
        case y: // y - не константа
            x = y;
            std::cout << x;
            break;
        case z: // так можно
            x = y;
            std::cout << x;
            break; 
        case z:
            int n = 15; // а так нельзя
            break; 
        default:
            x = 100;
            break;
    }
    
    return 0;
}
```

```c++
#include <iostream>

int main() {
    char x = 5;
    switch (x) {
        case 261: // тут явно UB, тк 261 в char не помещается
            std::cout << 1;
            break;
    }
    
    return 0;
}
```
И еще пример, который компилируется, но отсутствие `break` все ломает
```c++
#include <iostream>

int main() {
    int x = 5;
    switch (x) {
        case 5:
            std::cout << 1;
        default:
            std::cout << 2;
    }
    // Выведет 12
    return 0;
}
```
