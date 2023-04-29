# Декоратор

Декоратор (Decorator) - это структурный паттерн проектирования, который позволяет динамически добавлять объектам новые функциональные возможности, оборачивая их в объекты-декораторы. Декораторы имеют тот же интерфейс, что и декорируемый объект, и передают вызовы дальше по цепочке декораторов, пока они не достигнут конечного объекта.

```c++
#include <iostream>

class Component {
public:
    virtual void operation() = 0;
};

class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "ConcreteComponent: Doing some operation." << std::endl;
    }
};

class Decorator : public Component {
private:
    Component* component_;

public:
    Decorator(Component* component) : component_(component) {}

    void operation() override {
        component_->operation();
    }
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}

    void operation() override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorA: Adding additional operation." << std::endl;
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}

    void operation() override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorB: Adding more additional operation." << std::endl;
    }
};

int main() {
    Component* component = new ConcreteComponent();
    component->operation();

    Component* decoratorA = new ConcreteDecoratorA(component);
    decoratorA->operation();

    Component* decoratorB = new ConcreteDecoratorB(decoratorA);
    decoratorB->operation();

    delete component;
    delete decoratorA;
    delete decoratorB;

    return 0;
}
```

В данном примере класс `Component` представляет базовый объект, который может выполнять некоторую операцию. Класс `ConcreteComponent` - это конкретный объект, который реализует базовый функционал. Класс `Decorator` выступает в качестве базового класса для всех декораторов и передает вызовы дальше по цепочке. Классы `ConcreteDecoratorA` и `ConcreteDecoratorB` - это конкретные декораторы, которые добавляют дополнительную функциональность к базовому объекту.

При выполнении программы будет выведено:

```
ConcreteComponent: Doing some operation.
ConcreteComponent: Doing some operation.
ConcreteDecoratorA: Adding additional operation.
ConcreteComponent: Doing some operation.
ConcreteDecoratorA: Adding additional operation.
ConcreteDecoratorB: Adding more additional operation.
```

# Прокси

Proxy паттерн - это структурный паттерн проектирования, который позволяет создать объект-заместитель (proxy), который выступает в качестве промежуточного уровня между клиентом и реальным объектом. Proxy может выполнять дополнительные функции, такие как кэширование, логирование, контроль доступа и т.д., не изменяя при этом интерфейса реального объекта.

```c++
#include <iostream>

class Subject {
public:
    virtual void request() = 0;
};

class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

class Proxy : public Subject {
private:
    RealSubject* real_subject_;

public:
    Proxy(RealSubject* real_subject) : real_subject_(real_subject) {}

    void request() override {
        if (check_access()) {
            real_subject_->request();
            log_request();
        }
    }

    bool check_access() {
        std::cout << "Proxy: Checking access prior to firing a real request." << std::endl;
        return true;
    }

    void log_request() {
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }
};

int main() {
    RealSubject* real_subject = new RealSubject();
    Proxy* proxy = new Proxy(real_subject);

    proxy->request();

    delete real_subject;
    delete proxy;

    return 0;
}
```

В данном примере класс `RealSubject` представляет реальный объект, который может выполнять некоторую операцию. Класс `Proxy` выступает в качестве заместителя и передает запросы на выполнение операции реальному объекту через метод `request()`. При этом `Proxy` может выполнять дополнительные функции, такие как проверка доступа и логирование запроса. В результате выполнения программы будет выведено:

```
Proxy: Checking access prior to firing a real request.
RealSubject: Handling request.
Proxy: Logging the time of request.
```

# Адаптер

Адаптер (Adapter) - это структурный паттерн проектирования, который позволяет использовать интерфейс существующего класса в другом классе без изменения исходного кода. Адаптер оборачивает объект и предоставляет новый интерфейс для взаимодействия с ним.

```c++
#include <iostream>

class Target {
public:
    virtual void request() = 0;
};

class Adaptee {
public:
    void specificRequest() {
        std::cout << "Adaptee: Specific request." << std::endl;
    }
};

class Adapter : public Target {
private:
    Adaptee* adaptee_;

public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}

    void request() override {
        adaptee_->specificRequest();
    }
};

int main() {
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);

    target->request();

    delete adaptee;
    delete target;

    return 0;
}
```


В данном примере класс `Target` представляет целевой интерфейс, который должен быть использован в клиентском коде. Класс `Adaptee` представляет существующий класс, который имеет свой собственный интерфейс. Класс `Adapter` оборачивает объект класса `Adaptee` и предоставляет новый интерфейс `Target`.

При выполнении программы будет выведено:

```
Adaptee: Specific request.
```

Таким образом, адаптер позволяет использовать объекты с разными интерфейсами вместе, что упрощает переиспользование кода и уменьшает зависимости между классами.

# Отличие

Эти 3 паттерна отличаются тем, какой интерфейс предоставляют и что делают с функциональностью оригинального класса.

Прокси оборачивает некоторый класс и предоставляет такой же интерфейс. Цель -- "притвориться" оригинальным классом и скрыть от клиента детали.

Декоратор также оборачивает некоторый класс и предоставляет такой же или расширенный интерфейс. Иногда декоратор называют "умным заместителем" (smart proxy). Т.е. декоратор может притворяться оригинальным классом и при этом расширять его функциональность.

Адаптер также оборачивает некоторый класс, но при этом предоставляет другой интерфейс. Т.е. используется в случаях, когда есть класс с нужными данными и поведением, но с неподходящим интерфейсом.

# Мост

Мост (Bridge) - это структурный паттерн проектирования, который разделяет абстракцию и реализацию таким образом, чтобы они могли изменяться независимо друг от друга. Мост используется, когда нужно связать классы с разными абстракциями, такими как различные операционные системы или базы данных.


```c++
#include <iostream>

class Implementor {
public:
    virtual void operationImpl() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    void operationImpl() override {
        std::cout << "ConcreteImplementorA: operation implementation." << std::endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    void operationImpl() override {
        std::cout << "ConcreteImplementorB: operation implementation." << std::endl;
    }
};

class Abstraction {
protected:
    Implementor* implementor_;

public:
    Abstraction(Implementor* implementor) : implementor_(implementor) {}

    virtual void operation() = 0;
};

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor* implementor) : Abstraction(implementor) {}

    void operation() override {
        std::cout << "RefinedAbstraction: extended operation." << std::endl;
        implementor_->operationImpl();
    }
};

int main() {
    Implementor* implementorA = new ConcreteImplementorA();
    Implementor* implementorB = new ConcreteImplementorB();

    Abstraction* abstractionA = new RefinedAbstraction(implementorA);
    Abstraction* abstractionB = new RefinedAbstraction(implementorB);

    abstractionA->operation();
    abstractionB->operation();

    delete implementorA;
    delete implementorB;
    delete abstractionA;
    delete abstractionB;

    return 0;
}
```

В данном примере класс `Implementor` представляет реализацию, которая может быть изменена независимо от абстракции. Классы `ConcreteImplementorA` и `ConcreteImplementorB` представляют конкретные реализации.

Класс `Abstraction` представляет абстракцию, которая может использовать любую реализацию. Класс `RefinedAbstraction` представляет расширенную абстракцию.

При выполнении программы будет выведено:

```
RefinedAbstraction: extended operation.
ConcreteImplementorA: operation implementation.
RefinedAbstraction: extended operation.
ConcreteImplementorB: operation implementation.
```

Таким образом, мост позволяет разделять абстракцию и реализацию таким образом, чтобы они могли изменяться независимо друг от друга. Это упрощает добавление новых реализаций и расширение функциональности программы.
