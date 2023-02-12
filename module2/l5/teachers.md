План занятия
=====

Занятие целиком посвящено сортировке данных. Начиная с ручной сортировки и функции `std::sort`, заканчивая `std::set` и `std::map`


## Задача сортировки

Написать сортировку пузырьком. Посчитать ассимптитоку.

Как вариант, реализовать такую функцию:

```c++
void Sort(std::vector<int>::iterator first, std::vector<int>::iterator last);
```

Которая проводит `inplace` сортировку вектора `int`

Можно обсудить и другие алгоритмы, если позволяет время.

## std::sort

Синтаксис и использование с контейнерами и массивами

```c++
int a[N];
std::sort(a, a + 50);
```

```c++
std::vector<int> a(50);
std::sort(a.begin(), a.end());
```

Запустить на больших данных свою сортировку и `std::sort`. Сравнить время

Ассимптотика $O(n*log(n))$

### Кастомная сортировка

Сортировка собственных структур данных требует либо написание `operator <`, либо передавать в `std::sort` 3 аргументом компаратор.

```c++
struct MyStruct {
    int x = 0;
};

// main

std::vector<MyStruct> a(50);
std::sort(a.begin(), a.end());
```

Пример выше не компилируется

#### operator<

```c++
struct MyStruct {
    int x = 0;
    bool operator<(const MyStruct& another) const {
        return x * x < another.x * another.x;
    }
};

// main

std::vector<MyStruct> a(50);
std::sort(a.begin(), a.end());
```

Если написать `operator<`, то всё заработает. Писать нужно именно для знака `<`, а не любых других остальных.

#### функция-компаратор

```c++
struct MyStruct {
    int x = 0;
};

bool compFunction(const MyStruct& left, const MyStruct& right) {
    return left.x * left.x < right.x * right.x;
}

// main

std::vector<MyStruct> a(50);
std::sort(a.begin(), a.end(), compFunction);
```

#### Класс-компаратор

```c++
struct MyStruct {
    int x = 0;
};

class CompClass {
public:
    bool operator()(const MyStruct& left, const MyStruct& right) const {
        return left.x * left.x < right.x * right.x;
    }
};

// main

std::vector<MyStruct> a(50);
CompClass comparatorIntance;
std::sort(a.begin(), a.end(), comparatorIntance);
```

Здесь особое внимание уделить `CompClass`. Это функциональный класс, у него мы перегрузили `operator()`. Стоит показать примеры, как он используется, а именно в таком духе:

```c++
MyStruct a{5};
MyStruct b{6};
CompClass comparatorIntance;
std::cout << comparatorIntance(b, a) << "\n";
```




## set, multiset

Как `std::set` хранит свои элементы, можно примерно рассказать, как он устроен, достаточно будет сказать, что он реализован в виде дерева.

Синтаксис и методы

1. insert(x)
2. erase(x)
3. erase(iter)
4. find(x)
5. begin()
6. end()

Всё это работает за $O(log_2(n))$

Перебор всех элементов работает за $O(n)$, а не $O(n*log_2(n))$

Также рассказать про итераторы, они умеют совсем немногое, почти как в std::list.


### шаблонные параметры-компараторы
std::less<T>, std::greater<T>, а также свои шаблонные параметры-компараторы для собственных структур

```c++
struct MyStruct {
    int x = 0;
};

std::set<MyStruct> st;
st.insert(MyStruct());
```

Как и с `std::sort` такой код не будет работать. Пишем либо `operator<`, либо компаратор, только передаем его, как шаблон

```c++
struct MyStruct {
    int x = 0;
};

class CompClass {
public:
    bool operator()(const MyStruct& left, const MyStruct& right) const {
        return left.x * left.x < right.x * right.x;
    }
};

std::set<MyStruct, CompClass> st;
st.insert(MyStruct());
```

### multiset 

`std::multiset` это `std::set` с возможностью хранить дубликаты. Просто продемонстрировать его работу




## map

Принципиально `std::map` мало отличается от `std::set`. Просто элементы `std::set` теперь становятся `keys`, а за ними закреплены `values`.

Рассказать идею `keys` и `values`, продемонстрировать примеры работы.


`std::map` хранит свои элементы в такой паре:

```c++
std::pair<const KeyType, ValueType>
```

Поэтому в частности, в таком `for`

```c++
for (auto pr : myMap)
```

`pr` будет парой

```c++
for (auto& pr : myMap)
```

Так, изменение `pr.second` будет менять значения в самом `std::map`

Синтаксис и методы:

_пару можно создавать с помощью {}_

1. insert({k, v})
2. erase({k, v})
3. erase(iter)
4. find({k, v})
5. begin()
6. end()

Всё это работает за $O(log_2(n))$

Перебор всех элементов работает за $O(n)$, а не $O(n*log_2(n))$

Отдельно про operator[]

По ключу можно сразу получать значение с помощью []. При этом, если такой ключ раньше не встречался, то он автоматически будет создан, и в него будет помещено дефолтное значение ValueType.

```c++
std::map<int, int> mp;
mp[100] = 100*100;
std::cout << mp[100] << "\n";

std::cout << mp[5] << "\n";

const std::map<int, int>& constRef = mp;

// Если раскомментировать, будет CE, тк может создать новый элемент в const объекте
// std::cout << constRef[6] << "\n"; 
```

## multimap


`std::multimap` это `std::map` с возможностью хранить дубликаты. Просто продемонстрировать его работу


## priority_queue

Синтаксис и методы, их ассимптотика. 


1. push(x)  --  $O(log_2(n))$
2. pop()  --  $O(log_2(n))$
3. front()  --  $O(1)$

Используется, когда нам достаточно получать только самый маленький/большой элемент, удалять его и добавлять новые элементы. 





