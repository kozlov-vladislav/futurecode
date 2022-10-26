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

// TODO
