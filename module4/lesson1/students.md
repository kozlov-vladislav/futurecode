# static поля и методы

Слово static в C++ может использоваться в нескольких контекстах:

1. Статические переменные в функциях:
```c++
void foo() {
    static int count = 0;
    count++;
    std::cout << "Count: " << count << std::endl;
}

int main() {
    foo();
    foo();
    foo();
}
```

В этом примере переменная count объявлена как static, что означает, что ее значение сохраняется между вызовами функции foo(). В результате на экран выводится:
Count: 1
Count: 2
Count: 3

Иными словами, static переменные создаются внутри функции и сохраняют свое состояние между вызовами. В этом смысле они похожи на глобальные переменные. Отличие в области видимости этих переменных

2. Статические методы и переменные класса:

```c++
class MyClass {
private:
    static int count;
public:
    static void incrementCount() {
        count++;
    }
    static int getCount() {
        return count;
    }
};

int MyClass::count = 0;

int main() {
    MyClass::incrementCount();
    MyClass::incrementCount();
    std::cout << "Count: " << MyClass::getCount() << std::endl;
    return 0;
}
```

В этом примере переменная count объявлена как статическая и принадлежит классу MyClass, а не его экземплярам. Методы incrementCount() и getCount() также объявлены как статические и могут быть вызваны без создания экземпляра класса. Результатом работы программы является вывод на экран:
Count: 2

Иными словами, static поля, это аналог static переменных внутри функции. Это те поля, которые относятся не к конретному объекту классу, а к классу в целом.

Тк такие переменные и методы не отсносятся к конректным объектам, обращаются к ним по имени класса через `::`

```c++
Имя_Класса::Имя_Метода
```

Ввиду особенностей компиляции, static поля нужно определять отдельно. Например, сразу после кода класса.

Такой код не скомпилируется:

```c++
struct S {
    static int x = 0;
};
```

Переменная может меняться, поэтому я нужно опеределять вне класса.

Однако, если static поле константно, то можно(и нужно) определять сразу внутри класса

```c++
struct S {
    const static int x = 0;
};
```

# Синглтон

Синглтон - это паттерн проектирования, который гарантирует, что класс имеет только один экземпляр и обеспечивает глобальную точку доступа к этому экземпляру.

Как пример, можно написать такой класс:

```c++
class Singleton {
private:
    static Singleton* instance;
    Singleton() {}
public:
    static Singleton* GetInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
    static void DestroyInstance() {
        if (instance == nullptr) {
            return;
        }
        delete instance;
    }
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::GetInstance();
    Singleton* s2 = Singleton::GetInstance();

    if (s1 == s2) {
        std::cout << "s1 and s2 are the same instance\n";
    }
    Singleton::DestroyInstance();
}
```


В этом примере класс `Singleton` имеет приватный конструктор, чтобы предотвратить создание экземпляров класса извне. Статическая переменная `instance` хранит единственный экземпляр класса. Метод `GetInstance`() возвращает этот экземпляр, создавая его при необходимости. В функции `main()` создаются две переменные `s1` и `s2`, которые должны ссылаться на один и тот же экземпляр класса `Singleton`.

В конце уничтожаем созданный объект с помощью метода `DestroyInstance()`. Однако можно хранить указатель не явно, а внутри структуры-обертки(например, умные указатели). Тогда не придется удалять объект явно.


# Фабрика

Паттерн Фабрика (Factory) - это порождающий паттерн проектирования, который позволяет создавать объекты без явного указания их класса, делегируя процесс создания специальным объектам-фабрикам. Фабрика может создавать объекты с различными свойствами, но интерфейс создания остается одинаковым.

По сути, любой класс, который позволяет создавать объекты одной функциональности, может считаться фабрикой:


```c++
class TradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    TradePair(const std::string& nameFirst,
              const std::string& nameSecond) : currencyFirst(nameFirst),
                                               currencySecond(nameSecond) {
        // Проверяем, что nameFirst - существует
        // Проверяем, что nameSecond - существует
        // Создаем подключение к серверу и т.п.
    }
    void Trade() {};
    std::pair<std::string, std::string> GetNames() const {
        return {currencyFirst, currencySecond};
    }
};

class TradePairFactory {
public:
    static TradePair Create(const std::string& nameFirst, const std::string& nameSecond) {
        return TradePair(nameFirst, nameSecond);
    }
};

int main() {
    auto pair1 = TradePairFactory::Create("RUB", "USD");
    auto pair2 = TradePairFactory::Create("USD", "EUR");
}
```

В этом примере мы создаем класс торговой пары(`TradePair`) с помощью фабрики `TradePairFactory`. У нее есть статический метод `Create`, который возвращает нужный объект торговой пары. Т.е. мы делигируем создание объектов торговых пар специальному классу - фабрике.

Этот пример можно улучшить, например, привнести функционал `Синглтона` в `TradePair`(в рабочем проекте скорее всего это и нужно сделать), создать специальный класс для непосредственно валюты(RUB, USD, EUR) и т.п.

# Абстрактная фабрика

Допустим, что теперь есть 2 вида торговых пар. Те, что на обычной бирже и те, что на криптовалютной. И работа с ними настолько разная, что пришлось писать 2 разных класса для этих целей:

```c++
class MoexTradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    MoexTradePair(const std::string& nameFirst,
              const std::string& nameSecond) : currencyFirst(nameFirst),
                                               currencySecond(nameSecond) {
        // Проверяем, что nameFirst - существует
        // Проверяем, что nameSecond - существует
        // Создаем подключение к серверу и т.п.
    }
    void Trade() {
        // Пусть здесь идет отправка на обычную биржу
        std::cout << "Trade MOEX\n";
    };
    std::pair<std::string, std::string> GetNames() const {
        return {currencyFirst, currencySecond};
    }
};

class CryptoTradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    CryptoTradePair(const std::string& nameFirst,
              const std::string& nameSecond) : currencyFirst(nameFirst),
                                               currencySecond(nameSecond) {
        // Проверяем, что nameFirst - существует
        // Проверяем, что nameSecond - существует
        // Создаем подключение к серверу и т.п.
    }
    void Trade() {
        // Пусть здесь идет отправка на криптовалютную биржу
        // Рассчитывается газ на отправку и т.п.
        std::cout << "Trade MOEX\n";
    };
    std::pair<std::string, std::string> GetNames() const {
        return {currencyFirst, currencySecond};
    }
};
```

Как видите классы очень похожи. Пусть у них будет общий предок, который задает интерфейс `TradePair`

```c++
class ITradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    ITradePair(const std::string& nameFirst,
               const std::string& nameSecond) : currencyFirst(nameFirst),
                                                currencySecond(nameSecond) {
    }

    virtual void Trade() = 0;

    std::pair<std::string, std::string> GetNames() const {
        return {currencyFirst, currencySecond};
    }

    virtual ~ITradePair() {};
};

class MoexTradePair : public ITradePair {
public:
    MoexTradePair(const std::string& nameFirst,
                  const std::string& nameSecond) : ITradePair(nameFirst, nameSecond) {};

    void Trade() override {
        // Пусть здесь идет отправка на обычную биржу
        std::cout << "Trade MOEX\n";
    };

};

class CryptoTradePair : public ITradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    CryptoTradePair(const std::string& nameFirst,
                    const std::string& nameSecond) : ITradePair(nameFirst, nameSecond) {};

    void Trade() {
        // Пусть здесь идет отправка на криптовалютную биржу
        // Рассчитывается газ на отправку и т.п.
        std::cout << "Trade Crypto\n";
    };
};
```

Как теперь можно написать фабрику для торговых пар?

Давайте сперва напишем 2 фабрики, по одной на каждый тип торговой пары(MOEX, Crypto)


```c++
class MoexTradePairFactory {
public:
    static ITradePair* Create(const std::string& nameFirst, const std::string& nameSecond) {
        return new MoexTradePair(nameFirst, nameSecond);
    }
};

class CryptoTradePairFactory {
public:
    static ITradePair* Create(const std::string& nameFirst, const std::string& nameSecond) {
        return new CryptoTradePair(nameFirst, nameSecond);
    }
};
```

Классы торговых пар теперь полиморфные, поэтому мы возвращаем указатель, причем сразу на `ITradePair`(спасибо полиморфизм).

Однако, вместо сырых небезопасных указателей давайте использовать std::shared_ptr:


```c++
class MoexTradePairFactory {
public:
    static std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) {
        return std::make_shared<MoexTradePair>(nameFirst, nameSecond);
    }
};

class CryptoTradePairFactory {
public:
    static std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) {
        return std::make_shared<CryptoTradePair>(nameFirst, nameSecond);
    }
};

int main() {
    auto pair1 = MoexTradePairFactory::Create("RUB", "USD");
    auto pair2 = CryptoTradePairFactory::Create("USD", "EUR");
    pair1->Trade();
    pair2->Trade();
}
```
Вывод
```
Trade MOEX
Trade Crypto
```

Как видите, были созданы нужные пары, и хоть статический тип у них совпадает(`ITradePair`), реально под этими указателями лежат `MoexTradePair` и `CryptoTradePair`.

На этом шаге можно остановиться, однако, если у вас есть код, которому не важно, какого типа создавать пары, то придеться писать 2 версии такого кода. Первую - для Moex, вторую для Crypto. Чтобы этого избежать, давайте фабрики тоже сделаем полиморфными

```c++
class ITradePairFactory {
public:
    virtual std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) = 0;
};

class MoexTradePairFactory : public ITradePairFactory{
public:
    std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) override {
        return std::make_shared<MoexTradePair>(nameFirst, nameSecond);
    }
};

class CryptoTradePairFactory : public ITradePairFactory {
public:
    std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) override {
        return std::make_shared<CryptoTradePair>(nameFirst, nameSecond);
    }
};
```

Мы создали класс `ITradePairFactory`, он и задает интерфейс работы с фабриками. К сожалению, от `static` методов пришлось отказаться, тк метод не может быть и виртуальным, и `static`

```c++
void DoSomeStuff(const std::shared_ptr<ITradePairFactory>& factory) {
    auto pair1 = factory->Create("USD", "RUB");
    auto pair2 = factory->Create("USD", "EUR");
    pair1->Trade();
    pair2->Trade();
}

int main() {
    std::shared_ptr<ITradePairFactory> factory;
    if ("Если код для MOEX") {
        factory = std::make_shared<MoexTradePairFactory>();
    } else {
        factory = std::make_shared<CryptoTradePairFactory>();
    }
    DoSomeStuff(factory);
}
```

Как видите, функции `DoSomeStuff` совершенно не важно, какого типа Торговые пары, на какой платформе они торгуются и т.п. Все они задаются общим интерфейсом(и пары, и фабрики), поэтому она способна в качестве аргумента принимать указатель на `ITradePairFactory`.

То, что мы сейчас написали, называется _Абстрактная фабрика_. 

Итого, абстрактная фабрика, это такая фабрика, которая задается базовым абстрактным классом, а конкретные реализации фабрик уже наследуются от базового класса.
Однако, чтобы они могли перегружать виртуальные методы, метод `Create` должен возвращать объекты одного и того же типа.

Поэтому и объекты, которые порождают фабрики также должны следовать единому интерфейсу, поэтому и они наследуются от своего абстрактного родителя.

Еще пример:
Класс, который рендерит кнопки на экране. Однако кнопки могут быть как просто на рабочем столе, так и в браузере, так и на другой системе. Поэтому для кнопок нужно писать абстрактную фабрику.

_Весь код:_

```c++
class ITradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    ITradePair(const std::string& nameFirst,
               const std::string& nameSecond) : currencyFirst(nameFirst),
                                                currencySecond(nameSecond) {
    }

    virtual void Trade() = 0;

    std::pair<std::string, std::string> GetNames() const {
        return {currencyFirst, currencySecond};
    }
    virtual ~ITradePair() {};
};

class MoexTradePair : public ITradePair {
public:
    MoexTradePair(const std::string& nameFirst,
                  const std::string& nameSecond) : ITradePair(nameFirst, nameSecond) {};

    void Trade() override {
        // Пусть здесь идет отправка на обычную биржу
        std::cout << "Trade MOEX\n";
    };

};

class CryptoTradePair : public ITradePair {
    const std::string currencyFirst;
    const std::string currencySecond;
public:
    CryptoTradePair(const std::string& nameFirst,
                    const std::string& nameSecond) : ITradePair(nameFirst, nameSecond) {};

    void Trade() {
        // Пусть здесь идет отправка на криптовалютную биржу
        // Рассчитывается газ на отправку и т.п.
        std::cout << "Trade Crypto\n";
    };
};

class ITradePairFactory {
public:
    virtual std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) = 0;
};

class MoexTradePairFactory : public ITradePairFactory{
public:
    std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) {
        return std::make_shared<MoexTradePair>(nameFirst, nameSecond);
    }
};

class CryptoTradePairFactory : public ITradePairFactory {
public:
    std::shared_ptr<ITradePair> Create(const std::string& nameFirst, const std::string& nameSecond) {
        return std::make_shared<CryptoTradePair>(nameFirst, nameSecond);
    }
};

void DoSomeStuff(const std::shared_ptr<ITradePairFactory>& factory) {
    auto pair1 = factory->Create("USD", "RUB");
    auto pair2 = factory->Create("USD", "EUR");
    pair1->Trade();
    pair2->Trade();
}

int main() {
    std::shared_ptr<ITradePairFactory> factory;
    if ("Если код для MOEX") {
        factory = std::make_shared<MoexTradePairFactory>();
    } else {
        factory = std::make_shared<CryptoTradePairFactory>();
    }
    DoSomeStuff(factory);
}
```