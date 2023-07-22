# Исключения

Исключения в С++ используются для обработки ошибок и неожиданных ситуаций, которые могут возникнуть во время выполнения программы. Они позволяют перехватывать ошибки и обрабатывать их в специальном блоке кода, что позволяет избежать непредсказуемого поведения программы или ее аварийного завершения. 

Исключения также позволяют разработчикам создавать более надежные программы, которые могут обрабатывать ошибки и продолжать работу в условиях, когда без использования исключений программа была бы прервана. Они также упрощают отладку программы, поскольку позволяют определить точное место, где произошла ошибка и как ее можно исправить.

Кроме того, исключения могут использоваться для управления потоком выполнения программы, например, для реализации механизма перехода к другому блоку кода при возникновении определенной ошибки

Как было отмечено, исключения используются при возникновении ошибок во время работы кода.

Какие могут быть ошибки? Зависит от задачи. Деление на 0, выход за границы массива, просто некорректные действия программы.

Встречались ли исключения раньше? Да, встречались, но совсем мало. Следует понимать разницу, между исключениями и просто ошибками вызванными условным UB. Например, дважды удалить выделенную память не порождает исключение, это UB, который перетекает в RE.

Что же тогда такое исключения?

Исключение это в первую очередь объект. Чтобы оно появилось, его нужно _бросить_, вызвав оператор `throw`

В любой момент времени можно задать вопрос, брошено ли сейчас исключение или нет. И если оно брошено, его необходимо _поймать_ `catch`, или же выполнение программы завершится аварийно.

Теперь конретнее:

Основные конструкции:

1. Оператор `throw`

2. Блок `try catch`

Рассмотрим код:

```c++
double divide(double a, double b) {
    return a / b;
}

int main() {
    int a;
    std::cin >> a;
    int b;
    std::cin >> b;
    std::cout << divide(a, b);
}
```

Как обработать ситуацию, когда `b == 0`?

```c++
double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        // What to do?
    }
}

int main() {
    int a;
    std::cin >> a;
    int b;
    std::cin >> b;
    std::cout << divide(a, b);
}
```

Давайте бросать исключение.

Оператор `throw` в качестве аргумента принимает объект, который будет являться исключением. Бросить можно почти все, что угодно. Начиная от объекта типа `int`, заканчивая пользовательским классом. Заметьте, что бросается именно объект, а не тип

```c++
struct MyErrorStruct {
    std::string ErrorMessage;
};

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        MyErrorStruct error;
        error.ErrorMessage = "can't divide " + std::to_string(a) + " by 0";
        throw error;
    }
}

int main() {
    int a;
    std::cin >> a;
    int b;
    std::cin >> b;
    std::cout << divide(a, b);
}
```

Здесь мы объявили структуру, которая будет содержать информацию об ошибке. Бросаем мы объект этой структуры. Однако, если запустить код с `b == 0`, то можно получить примерно такой вывод:

```
terminate called after throwing an instance of 'MyErrorStruct'

Process finished with exit code 134 (interrupted by signal 6: SIGABRT)
```
Исключение то мы бросили, однако нигде его не ловим. Для этого используется блок `try catch`

```c++
try {
    // КОД, который потенциально может
    // бросить исключение
} catch(/*Какое исключение мы хотим поймать*/) {
    // Обработка пойманного исключения
}
```

В `try` оборачивают код, который может бросить исключение, чтобы его затем поймать. Ловят его в блоке `catch`. А именно, в круглый скобках `catch` объявляют переменную, в которую нужно будет поместить исключение. Важно, что тип брошенного исключения должен совпадать(с некоторой оговоркой) с типом, который указан в круглых скобках `catch`. В теле `catch` происходит обработка исключения(например, вывод на экран сообщения об ошибке)


```c++
struct MyErrorStruct {
    std::string ErrorMessage;
};

double divide(double a, double b) {
    if (b != 0) {
        return a / b;
    } else {
        MyErrorStruct error;
        error.ErrorMessage = "can't divide " + std::to_string(a) + " by 0";
        throw error;
    }
}

int main() {
    int a;
    std::cin >> a;
    int b;
    std::cin >> b;
    try {
        std::cout << divide(a, b);
    } catch(MyErrorStruct error) {
        std::cout << "Got error with message:\n" << error.ErrorMessage << "\n";
    }
}
```

В `try` мы помещаем вызов `divide(a, b);`. В `catch` мы ловим исключения типа `MyErrorStruct`. Если исключение было поймано, то выводим содержимое на экран.

Запустим код несколько раз

Ввод:
```
5 0
```
Вывод:
```
Got error with message:
can't divide 5.000000 by 0
```
-------------
Ввод:
```
7 4
```
Вывод:
```
1.75
```

Независимо от ввода, программа корректно отработала.

-------------

Как можно ловить исключения?

1. catch может быть несколько подряд, сработает первый подходящий

```c++
int main() {
    try {
        int error = 6;
        throw error;
    } catch (const double& error) {
        std::cout << "A";
    } catch (const unsigned int& error) {
        std::cout << "B";
    } catch (const int& error) { // Сработает этот catch 
        std::cout << "C";
    }
}
```

2. catch поймает исключение, даже если тип его не совпадает с брошенными, если пойманный тип является родителем брошенного

```c++
struct Parent {
};

struct Child1 : Parent {
};

struct Child2 : Parent {
};

int main() {
    try {
        throw Child1();
    } catch (const Child2& error) {
        std::cout << "A";
    } catch (const Parent& error) { // Сработает этот catch 
        std::cout << "B";
    } catch (const Child1& error) {
        std::cout << "C";
    }
}
```
3. есть синтаксис для произвольного типа исключений, а именно `catch(...)`. Такой блок поймает любое исключение. Однако в явном виде его будет получить сложно(здравствуй статическая типизация)
```c++
int main() {
    try {
        std::string error = "abacaba";
        throw error;
    } catch (const double& error) {
        std::cout << "A";
    } catch (const unsigned int& error) {
        std::cout << "B";
    } catch (...) { // Сработает этот catch
        std::cout << "C";
    }
}
```
4. Лучше стараться использовать константные ссылки, чтобы лишний раз не копировать память
-------------

Перейдем непосредственно к практике.

В C++ есть класс `std::exception`

```c++
class exception {
    virtual const char* what() const noexcept = 0;
}
``` 

У него есть метод `what`, который возвращает описание ошибки.

Обычно для каждого типа ошибки создают наследника `std::exception` и переопределяют метод `what`

Так делают для поддержки функционала языка и некоторых преднаписанных функций. Более того, стандартные исключения в С++ также наследуются от `std::exception`.

-----

Исключения в векторе

Создадим маленький вектор и обратимся к большому индексу:
```c++
int main() {
    const int BIG_INDEX = 100000000;
    std::vector<int> vec(5);
    vec[BIG_INDEX] = 1000;
}
```

Такой код упадет, попробуем ловить исключение:

```c++
int main() {
    const int BIG_INDEX = 100000000;
    std::vector<int> vec(5);
    try {
        vec[BIG_INDEX] = 1000;
    } catch(...) {
        
    }
}
```
Даже такой код не помогает, потому что никакого исключения в коде не возникает. Чтобы оно возникло, нужно использовать метод `at`:


```c++
int main() {
    const int BIG_INDEX = 100000000;
    std::vector<int> vec(5);
    vec.at(BIG_INDEX) = 1000;
}
```

```
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 100000000) >= this->size() (which is 5)
Process finished with exit code 134 (interrupted by signal 6: SIGABRT)
```

Было брошено исключение типа `std::out_of_range` - наследник `std::exception`. Добавим блок `try-catch`

```c++
int main() {
    const int BIG_INDEX = 100000000;
    std::vector<int> vec(5);
    try {
        vec.at(BIG_INDEX) = 1000;
    } catch(const std::exception& error) {
        std::cout << "Got error:\n" << error.what();
    }
}
```
```
Got error:
vector::_M_range_check: __n (which is 100000000) >= this->size() (which is 5)
Process finished with exit code 0
```

Исключение было выброшено, но мы его поймали.

-------------

Еще пример, с динамическим кастом.

В этом примере мы создаем простую иерархию полиморфных классов и пытаемся скастовать `Child1` к `Child2`. Так делать нельзя, тк они попарно не являются наследником/родителем друг друга. 

```c++
struct Parent {
    virtual void what() const = 0;
};

struct Child1 : Parent {
    void what() const override {
        std::cout << "child1\n";
    }
};

struct Child2 : Parent {
    void what() const override {
        std::cout << "child2\n";
    }
};

int main() {
    auto child1 = Child1();
    const Parent& parent = child1;
    const Child2& child2 = dynamic_cast<const Child2&>(parent);
    child2.what();
}
```

```
terminate called after throwing an instance of 'std::bad_cast'
  what():  std::bad_cast

Process finished with exit code 134 (interrupted by signal 6: SIGABRT)
```

`dynamic_cast` бросает исключение типа `std::bad_cast` - наследник `std::exception`


--------------------

Что происходит во время исключения? Когда исключение брошено, компилятор начинает идти по стеку и деаллоцировать объекта на нем(вызывать у них деструкторы).
Поcмотрите на пример, в нем, после того как было вырошено исключение, созданный объект уничтожается:

```c++
struct ToBeOnStack {
    ToBeOnStack() {
        std::cout << "ToBeOnStack\n";
    }
    ~ToBeOnStack() {
        std::cout << "~ToBeOnStack\n";
    }
};

struct ExceptionType {};

void LogicFunction() {
    std::cout << "before\n";
    auto x = ToBeOnStack();
    throw ExceptionType();
}

int main() {
    std::cout << "before try\n";
    try {
        std::cout << "before LogicFunction\n";
        LogicFunction();
        std::cout << "after LogicFunction\n";
    } catch(...) {
        std::cout << "In Catch block\n";
    }
}
```
```
before try
before LogicFunction
before
ToBeOnStack
~ToBeOnStack
In Catch block
```

Однако, как можно выдеть из вывода, некоторые действия отменить нельзя, если было выброшено исключение. Например, вывод на экран. Он остается. Помимо этого, если создать объект динамически с помощью оператора `new`, то его нужно в дальнейшем деаллоцировать, т.е. вызвать оператор `delete`. Но что если будет выброшено исключение? Указатель на объект конечно удалится, будучи самим по себе объектом(размера 8 байт). Однако сам объект -- нет. Тк для его удаления необходимо дойти до строчки с `delete`. Но этого не произойдет.


```c++
struct ToBeAllocated {
    ToBeAllocated() {
        std::cout << "ToBeAllocated\n";
    }
    ~ToBeAllocated() {
        std::cout << "~ToBeAllocated\n";
    }
};

struct ExceptionType {};

void LogicFunction() {
    std::cout << "before\n";
    auto ptr = new ToBeAllocated();
    throw ExceptionType();
}

int main() {
    std::cout << "before try\n";
    try {
        std::cout << "before LogicFunction\n";
        LogicFunction();
        std::cout << "after LogicFunction\n";
    } catch(...) {
        std::cout << "In Catch block\n";
    }
}
```
```
before try
before LogicFunction
before
ToBeAllocated
In Catch block
```
Как видно, объект `ToBeAllocated` был создан, но не удален(в выводе нет строчки `~ToBeAllocated`).

Та же проблема присутствует, если исключение происходит в методе класса. Да, класс целиком удалится вместе с его полями, однако подобные вызовы с `new` не будут правильно обработаны. И чуть большая проблема будет, если исключение будет выброшено в конструкторе класса.

Однако, это решаемая проблема. Тут мы подходим к следующей теме.

----------

Умные указатели

Мы лишь слегка затронем эту тему, тк она требует довольно глубокого погружения в исходный код и знание других тем(например,  move-семантика).

Идейно, чтобы выделенная с помощью `new` память удалялась, необходимо, чтобы это удаление было реализовано в деструкторе. Т.е. нужно обернуть указатель в отдельный объект, в деструкторе которого и будет происходить удаление.

_Умные указатели_ - это специальные классы, которые оборачивают сырые указатели и позволяют автоматически управлять памятью. Они используются для предотвращения утечек памяти и ошибок при освобождении памяти.

1. `std::unique_ptr` - это умный указатель, который представляет единственный владелец объекта и автоматически освобождает память при уничтожении



```c++
std::unique_ptr<Тип объекта> ptr(указатель на этот объект);
```

Смысл в том, что теперь `ptr` ведет себя как обычный указатель, но нам не нужно его удалять в конце работы, тк он сам себя удалит. 

Пример работы:



```c++
class ToBeAllocated {
    std::string str = "";
public:
    ToBeAllocated() {
        std::cout << "ToBeAllocated\n";
    }

    ToBeAllocated(const std::string& str) : str(str) {
        std::cout << "ToBeAllocated\n";
    }

    void SetString(const std::string& another) {
        str = another;
    }

    std::string& GetString() {
        return str;
    }

    ~ToBeAllocated() {
        std::cout << "~ToBeAllocated\n";
    }
};

int main() {
    std::unique_ptr<ToBeAllocated> ptr(new ToBeAllocated());
    ptr->SetString("abacaba");
    std::cout << ptr->GetString() << "\n";
}
```
```
ToBeAllocated
abacaba
~ToBeAllocated
```

Т.е. это обертка над конкретным адресом, которая позаботится о том, чтобы этот адрес деаллоцировать. Однако, исходя из названия, такой класс не позволяет присваивания:

```c++
int main() {
    std::unique_ptr<ToBeAllocated> ptr1(new ToBeAllocated());
    std::unique_ptr<ToBeAllocated> ptr2(new ToBeAllocated());
    ptr1 = ptr2; // Тут CE
}
``` 

Также, над одним адресом можно создавать только один `std::unique_ptr`:

```c++
int main() {
    ToBeAllocated* realPtr = new ToBeAllocated();
    std::unique_ptr<ToBeAllocated> ptr1(realPtr);
    std::unique_ptr<ToBeAllocated> ptr2(realPtr);
}
```
```
ToBeAllocated
~ToBeAllocated
~ToBeAllocated
```

Адрес был дважды удален, тк каждый `std::unique_ptr` удалил его в своем деструкторе

2. `std::make_unique` - специальная шаблонная функция, которая помогает создавать `std::unique_ptr`

```c++
std::make_unique<Тип объекта>(Список аргументов, которые нужно передать в конструктор);
```

Т.е. в `make_unique` можно передать аргументы, которые нужно было бы передать в конструктор объекта. Она корректно создаст объект и вернет  `std::unique_ptr` на него.


```c++
class ToBeAllocated {
    std::string str;
public:
    ToBeAllocated() {
        std::cout << "ToBeAllocated\n";
    }

    ToBeAllocated(const std::string& str) : str(str) {
        std::cout << "ToBeAllocated\n";
    }

    void SetString(const std::string& another) {
        str = another;
    }

    std::string& GetString() {
        return str;
    }

    ~ToBeAllocated() {
        std::cout << "~ToBeAllocated\n";
    }
};

int main() {
    auto ptr = std::make_unique<ToBeAllocated>("abacaba");
    std::cout << ptr->GetString() << "\n";
}
```
```
ToBeAllocated
abacaba
~ToBeAllocated
```

Давайте исправим тот пример с исключениями, где созданный объект не удалялся:

```c++
class ToBeAllocated {
    std::string str;
public:
    ToBeAllocated() {
        std::cout << "ToBeAllocated\n";
    }

    ~ToBeAllocated() {
        std::cout << "~ToBeAllocated\n";
    }
};

struct ExceptionType {};


void LogicFunction() {
    std::cout << "before\n";
    auto ptr = std::make_unique<ToBeAllocated>();
    throw ExceptionType();
}

int main() {
    std::cout << "before try\n";
    try {
        std::cout << "before LogicFunction\n";
        LogicFunction();
        std::cout << "after LogicFunction\n";
    } catch(...) {
        std::cout << "In Catch block\n";
    }
}
```
```
before try
before LogicFunction
before
ToBeAllocated
~ToBeAllocated
In Catch block
```

3. `std::shared_ptr` - это умный указатель, который представляет несколько владельцев объекта и автоматически освобождает память, когда последний владелец уничтожается

Теперь у вас есть адрес, и на него могут ссылаться несколько умных указателей. Т.е. валидно делать присваивания и тп. 

Синтаксис у него такой же.

```c++
int main() {
    std::shared_ptr<ToBeAllocated> ptr1(new ToBeAllocated());
    std::shared_ptr<ToBeAllocated> ptr2(new ToBeAllocated());
    std::cout << "before =\n";
    ptr1 = ptr2; // Тут нет CE
    std::cout << "after =\n";
}
```
```
ToBeAllocated
ToBeAllocated
before =
~ToBeAllocated
after =
~ToBeAllocated
```

Смысл в том, что `std::shared_ptr` отслеживает, сколько `shared_ptr` указывают на конкретный адрес, и когда их кол-во становится `0`, он удаляет выделенную память.

Однако, это не дает нам право писать так:

```c++
int main() {
    ToBeAllocated* realPtr = new ToBeAllocated();
    std::shared_ptr<ToBeAllocated> ptr1(realPtr);
    std::shared_ptr<ToBeAllocated> ptr2(realPtr);
}
```
```
ToBeAllocated
~ToBeAllocated
~ToBeAllocated
```

Т.е. один и тот же адрес нужно оборачивать в `std::shared_ptr` ровно один раз. Несколько `std::shared_ptr` могут указывать на один и тот же адрес только засчет присваивания самих `std::shared_ptr`.

4. `std::make_shared`

Синтаксис такой же, как и у `std::make_unique`

Также имеет смысл использовать эту функцию, чтобы конструировать объекты без написания `new`.

5. К сожалению, есть ситуации, когда умные указатели не спасают от проблем с исключениями. Однако их можно обойти, если по максимуму использовать `std::make_shared` и `std::make_unique`.

6. `std::shared_ptr` не всегда удаляет объекты. Причем, это не из-за ошибки внутри кода `std::shared_ptr`, а скорее из-за неправильного его использования.
Представьте, что вы создадите 2 объекта, и внутри этих объектов вы будете хранить указатели на противоложный объект. Тогда вы получите, что 2 `shared_ptr` указывают друг на друга, и ни один из них не удалится по этой причине.

```c++
class Node {
public:
    Node() {
        std::cout << "ToBeAllocated\n";
    }
    std::shared_ptr<Node> ptr;
    ~Node() {
        std::cout << "~ToBeAllocated\n";
    }
};

int main() {
    auto a = std::make_shared<Node>();
    auto b = std::make_shared<Node>();
    a->ptr = b;
    b->ptr = a;
}
```
```
ToBeAllocated
ToBeAllocated
```

И для этого есть решение в С++, а именно `std::weak_ptr`, однако в рамках этого урока мы рассматривать его не будем. Следите, чтобы не возникало таких ситуаций.