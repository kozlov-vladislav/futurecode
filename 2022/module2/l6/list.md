## Тест1

Зачем нужен seed в функциях, дающих случайные числа?

Чтобы увеличить степень разброса чисел

Это граница снизу, т.е. все числа должны быть не меньше seed

`Чтобы функция работала одинаково(детерминированно) на разных компьютерах и разных запусках с одним и тем же seed `


------


## Тест2

Какие хэши точно написаны НЕправильно?

1:

```c++

class MyHash {
public:
    size_t operator()(const std::pair<int, int>& value) const {
        unsigned long long a = value.first;
        unsigned long long b = value.second;
        return (a << 32) | b;
    }
};

```

2:

```c++

class MyHash {
public:
    size_t operator(const std::pair<int, int>& value) const {
        unsigned long long a = value.first;
        unsigned long long b = value.second;
        return (a << 32) | b;
    }
};

```

3:

```c++

class MyHash {
public:
    size_t operator()(const std::pair<int, int>& value) const {
        std::mt19937 rnd(std::random_device{}());
        return (a + b) * rnd();
    }
};

```

1

`2`

`3`



------



## Тест3

Отметьте верные утверждения про std::unordered_set

Хранит свои элементы в отсортированном порядке

`Хранит свои элементы в произвольном порядке`

`Можно за O(1) проверить, что элемент лежит в std::unordered_set`

Можно за O(log(n)) проверить, что элемент лежит в std::unordered_set

Позволяет хранить несколько одинаковых элементов

Можно обращаться по индексу за O(log(n))

Можно обращаться по индексу за O(1)

`Нельзя обращаться по индексу`






