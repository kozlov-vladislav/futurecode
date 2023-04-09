## Тест1

Будет ли поймано исключение?

```c++

void LogicFunction() {
    unsigned int x = 6;
    throw x;
}

int main() {
    try {
        LogicFunction();
    } catch (int x) {
        std::cout << "catch " << x << "\n";
    }
}

```

Да

`Нет`


------


## Тест2

Будет ли поймано исключение?


```c++

void LogicFunction() {
    int x = 6;
    throw x;
}

int main() {
    try {
        LogicFunction();
    } catch (unsigned int x) {
        std::cout << "catch " << x << "\n";
    }
}

```

Да

`Нет`


------


## Тест3

Будет ли поймано исключение?


```c++

void InnerFunction() {
    int x = 6;
    throw x;
}

void LogicFunction() {
    InnerFunction();
}

int main() {
    try {
        LogicFunction();
    } catch (int x) {
        std::cout << "catch " << x << "\n";
    }
}

```

`Да`

Нет


--------------------

## Тест4

Будет ли поймано исключение?


```c++

struct ExceptionA {
};

struct ExceptionB {
};

void InnerFunction() {
    throw ExceptionB();
}

void LogicFunction() {
    try {
        InnerFunction();
    } catch (const ExceptionA& exceptionA) {
        std::cout << "catch A\n";
    }
}

int main() {
    try {
        LogicFunction();
    } catch (const ExceptionB& exceptionB) {
        std::cout << "catch B\n";
    }
}

```

`Да`

Нет


--------------------

## Тест5

Будет ли поймано исключение?


```c++


void LogicFunction() {
    const int BIG_INDEX = 100000000;
    std::vector<int> vec(5);
    vec[BIG_INDEX] = 1000;
}

int main() {
    try {
        LogicFunction();
    } catch (const std::out_of_range& exc) {
        std::cout << "catch\n";
    }
}

```

Да

`Нет`

