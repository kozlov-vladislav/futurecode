## Тест1

Какие вызовы этой функции могут привести к ошибке?

```c++

template<typename T>
T max(T a, T b) {
    T res = a;
    if (b > a) {
        res = b;
    }
    return res;
}

```

```c++
int x;
std::cin >> x;
int y;
std::cin >> y;
```


1: max(x, y)

2: max<int>(x, y);

`3: max<int&>(x, y);`

`4: max<const int&>(x, y);`



------


## Тест2

Программист написал такой код. Какую строчку из предложенных можно поправить так, чтобы код работал?

```c++

struct UserId { // L1
    unsigned long long id = 0; // L2

    void Print() { // L3
        std:сout << "ID is " << id << "\n"; // L4
    }

    void IsSame(const UserId& another) { // L5
        if (id != another.id) { // L6
            std::cout << "Different:\n"; // L7
            this->Print(); // L8
            another.Print(); // L9
        } else { // L10
            std::cout << "Same:\n"; // L11
            another.Print(); // L12
        } // L13
    } // L14
}

```

L1

Код работает корректно

`L3`

L4

L12


------


## Тест3

В С++ базовый operator += возвращает ссылку на объект, поэтому можно писать такой код:

```c++
int x = 2;
int y = 10;
int z = 20;
(x += y) = z;
std::cout << x << " " << y << " " << z << "\n";
// Вывелоь 20 10 20

```

Программист написал такой код:

```c++
struct Number { // L1
    int number = 0; // L2
    Number operator+=(const Point& another) { // L3
        number += another.number; // L4
        return *this; // L5
    } // L6
}; // L7

int main() {
    Number x = {2};
    Number y = {10};
    Number z = {20};
    (x += y) = z;
    std::cout << x.number << " " << y.number << " " << z.number << "\n";
    // Вывелоь 12 10 20
}
```

Но вывод не такой, как с обычными целыми числами.
Какую строчку ему нужно исправить, чтобы += работал правильно?

L1

L2

`L3`

L4

L5

