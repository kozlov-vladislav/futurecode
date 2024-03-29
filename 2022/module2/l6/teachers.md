План занятия
=====

# Функциональные классы

Они уже встречались на предыдущих занятиях, но на этом их будет особенно много. Поэтому неплохо повторить, как они работают.

Как пример, функциональный класс, многочлен степени 2: $a*x^2 + b*x + c$

```c++

class FunctionalClass {
    int a;
    int b;
    int c;
public:
    FunctionalClass(int a, int b, int c) : a(a), b(b), c(c) {};
    int operator()(int x) const {
        return a * x * x + b * x + c;
    }
};

```

В конструктор передаем `a`, `b`, `c`. А затем пользуемся классом как обычной функцией

Построим функцию $func(x) = x^2 + 2x + 1 = (x + 1)^2$ и спроcим $func(5)$.
```c++
FunctionalClass func(1, 2, 1);
std::cout << func(5);
```


# Рандом в C

### Функции rand и srand



`rand` в `C` выглядел так:

```c
static unsigned long int next = 1;

int rand()
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}
```

Причем next можно задавать с помощью `srand`.

Позже функцию чуть улучшили, но у нее по-прежнему много недостатков. Это плохое распределение чисел, и их относительно небольшой размер(до `32768`);

Проблемы решают тем, что вызывают функцию несколько раз, и всячески сдвигают битово результаты, например так:

```c++
unsigned long long MyRand() {
    unsigned long long res = rand();
    res = (res << 15) | rand();
    res = (res << 15) | rand();
    res = (res << 15) | rand();
    res = (res << 15) | rand();
    return res;
}
```


# Рандом в C++
`#include <random>`
`#include <ctime>`


Речь пойдет про рандом из `stl`

# std::mt19937

Это функциональный класс, его конструктором является `seed`. Намного лучше, чем обычный rand из языка `C`.

Он возвращает числа `uint32`.

```c++
std::mt19937 myRand;
std::mt19937 myRand(237);
```

Также можно в качестве `seed` брать текущее время.

--------

_Если вы пользуетесь `unix` системой, или хотя бы компилятор у вас не `MinGW`, то пользуются_

```c++
std::random_device myDevice;
```

Тоже функциональный класс, но нам он будет нужен только чтобы получать `seed` .

```c++
std::mt19937 myRand;
std::mt19937 myRand(237);
std::mt19937 myRand(myDevice());
std::mt19937 myRand(std::random_device{}());
```

Если же объект уже есть, то `seed` у него можно задавать с помощью одноименного метода

```c++
myRand.seed(237);
myRand.seed(myDevice());
myRand.seed(std::random_device{}());
```

Пример работы

```c++
const int ITERATIONS = 1000000;
const unsigned long long MAX_NUMBER = 1000000;
std::mt19937 myRand(std::random_device{}());

unsigned long long sum = 0;
for (int iter = 0; iter < ITERATIONS; ++iter) {
    sum += myRand() % MAX_NUMBER;
}
std::cout << "average number is " << 1.0 * sum / ITERATIONS;
```

Среднее должно быть близко к $10^6 / 2$


--------

_Если вы на `Windows` и компилятор у вас `MinGW`, то пользуются_

```c++
std::time(nullptr);
```

И его подставляют в качестве seed вместо `random_device`.

Это так, потому что на момент написания текста `MinGW` на `Windows` так нормально и не реализовали `random_device`

------

В `stl` есть еще несколько подобных функций. Они отличаются распределением, из которого берутся числа. Так глубоко копать мы не будем.


-----

# unordered_map

`#include <unordered_map>`

Проще всего воспринимать контейнер как массив, который позволяет хранить индексы любых размеров и даже типов(с небольшой оговоркой).

Например задача. На вход подаются числа, причем довольно большие(до $10^{18}$). Также иногда приходят запросы, сколько раз встречается то или ионе число. Её удобно решать с помощью `std::unordered_map`.

Как обычно, синтаксис и методы

```c++
std::unordered_map<KeyType, ValueType> ump;
```

1. insert({k, v})
2. erase({k, v})
3. erase(iter)
4. find({k, v})
5. begin()
6. end()

Контейнер отличается от `std::map` всего в одном слове, а на деле различия между ними колоссальные.

Все методы `std::unordered_map` работают за $O(1)$. Более того он не хранит элементы в отсортированном порядке. Реализация у них совершенно разная.

------

`std::unordered_map` также зовут хеш-таблицей. Внутри он работает следующим образом:

У него есть `N` списков, в которых он хранит элементы.

Чтобы найти или вставить элемент, контейнер делает следующее:

1. Считает хеш объекта `H`
2. Берет его по модулю `N`, `index` = $H\mod N$
3. Идет в список `index` и там ищет/вставляет/удаляет элемент

Почему же ассимптотикой считается $O(1)$, если длина списка может быть большой? Ответ -- не может. Когда списки становятся большими, контейнер перебалансируется, увеличивая `N` подобно `std::vector`. Но все равно это занимает определенное время и ассимптотика $O(1)$ не совсем честная. Скорее $O^{*}(1)$ -- вероятностный вариант ассимптотики.

-------

Так вот, работа контейнера напрямую зависит от качества хеша.

Это обсудим подробнее(что такое хеш, какие основные свойства)

-----

Какие типы могут использоваться в качестве `KeyType`.

На самом деле все, для которых определен или может быть определен хэш.

```c++
template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    ...
>
class unordered_map;
```


По умолчанию `std::unordered_map` использует `std::hash`. Это функциональный класс. Он определен для разных типов, можно посмотреть, что он выводит для `std::string`

```c++
std::hash<std::string> defHash;
std::cout << defHash("abc");
```

Для типа `std::pair<int, int>` такого `std::hash` нет.

```c++
std::unordered_map<std::pair<int, int>, int> ump;
```

Такая строчка приведет к ошибке компиляции.

Есть два пути, как это исправить. 

Первый -- расширить функциональность самого `std::hash`. Мы не прошли язык настолько, чтобы дети осознали, как это работает. Это сложный вариант, но показать можно



```c++
namespace std {
    template<>
    class hash<std::pair<int, int>> {
    public:
        size_t operator()(const std::pair<int, int>& value) const {
            size_t a = value.first;
            size_t b = value.second;
            return (a << 32) | b;
        }
    };
}

std::unordered_map<std::pair<int, int>, int> ump;
```

А можно просто написать свой хеш и передать его как шаблонный параметр

```c++
class MyHash {
public:
    size_t operator()(const std::pair<int, int>& value) const {
        unsigned long long a = value.first;
        unsigned long long b = value.second;
        return (a << 32) | b;
    }
};

std::unordered_map<std::pair<int, int>, int, MyHash> ump;
```

-------

`#include <unordered_set>`

Переход к `unordered_set` аналогичен переходу от `map` к `set`. `set` хранит только ключи, без значений. В остальном он работает также. 

По классике рассказать про синтаксис и методы.


