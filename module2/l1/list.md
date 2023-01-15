## Тест1

Что выведет такой код?

```c++
#include <iostream>

struct S {
    int intField;
    double doubleField = 3.14;
};

int main() {
    S myStructure;
    std::cout << myStructure.intField;
}
```

## Ответ:

0

3.14

CE - ошибка компиляции

`UB - вывод неоднозначен`


------


## Тест2

Что выведет такой код?

```c++
#include <iostream>

struct PasswordChecker {
    int password = 123456789;
    void setPassword(int newPas) {
        password = newPas;
    }
    bool checkPassword(int pass) {
        return password == pass;
    }
};

int main() {
    PasswordChecker checker1;
    PasswordChecker checker2;
    checker1.setPassword(15);
    bool same = checker2.checkPassword(15);
    std::cout << same << "\n";
}
```

## Ответ:

`0`

1

CE - ошибка компиляции

UB - вывод неоднозначен


------


## Тест3

Что выведет такой код?

```c++
#include <iostream>
#include <string>

struct StrangeStruct {
    std::string someString = "";

    StrangeStruct& returnMeRef() {
        return *this;
    }
    StrangeStruct* returnMePtr() {
        return this;
    }
    StrangeStruct returnMeCopy() {
        return *this;
    }
};

int main() {
    StrangeStruct str;
    str.returnMeRef().someString += "The ";
    str.returnMePtr()->someString += "World";
    str.returnMeCopy().someString += "OH";
    std::cout << str.someString << "\n";
}
```

## Ответ:

Пустая строка

`The World`

The WorldOH

WorldOH

CE - ошибка компиляции

UB - вывод неоднозначен


------


## Тест4

Выберите верные утверждения:

`Во время создания структуры всегда вызывается конструктор`

Во время создания структуры конструктор вызывается, только если он явно реализован в коде

`Во время удаления структуры всегда вызывается деструктор`

Во время удаления структуры деструктор вызывается, только если он явно реализован в коде

`У структуры может быть реализовано несколько конструкторов`

У структуры может быть реализовано несколько деструкторов



------


## Тест5

Выберите верные утверждения:

Во время создания структуры, сначала вызывается конструктор самой структуры, а затем создаются её поля

`Во время создания структуры, сначала создаются её поля, а затем вызывается конструктор самой структуры`

`Во время удаления структуры, сначала вызывается деструктор самой структуры, а затем удаляются её поля`

Во время удаления структуры, сначала удаляются её поля, а затем вызывается деструктор самой структуры



------

