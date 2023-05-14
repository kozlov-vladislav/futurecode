# Observer

Паттерн Observer (наблюдатель) - это поведенческий паттерн проектирования, который определяет отношение "один-ко-многим" между объектами таким образом, что при изменении состояния одного объекта все зависящие от него объекты автоматически уведомляются и обновляются.

Пример реализации паттерна Observer на С++:

```c++
#include <iostream>
#include <vector>

class Observer {
public:
    virtual void update(int data) = 0;
};

class Subject {
private:
    int data;
    std::vector<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    void detach(Observer* observer) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }
    void notify() {
        for (auto observer : observers) {
            observer->update(data);
        }
    }
    void setData(int newData) {
        data = newData;
        notify();
    }
};

class ConcreteObserver : public Observer {
public:
    void update(int data) override {
        std::cout << "Data changed: " << data << "\n";
    }
};

int main() {
    ConcreteObserver observer1, observer2;
    Subject subject;
    subject.attach(&observer1);
    subject.attach(&observer2);
    subject.setData(10);
    subject.detach(&observer2);
    subject.setData(20);
}
```

В данном примере есть классы Observer и Subject. Класс Observer - это абстрактный класс, который определяет интерфейс для всех конкретных наблюдателей. Класс Subject - это класс, за которым наблюдают наблюдатели. В классе Subject есть методы attach, detach и notify для добавления, удаления и уведомления наблюдателей соответственно. В классе ConcreteObserver реализуется конкретный наблюдатель. В функции main создаются объекты классов ConcreteObserver и Subject, наблюдатели добавляются к субъекту методом attach, затем меняется состояние субъекта методом setData, после чего один из наблюдателей удаляется методом detach, и снова меняется состояние субъекта. При каждом изменении состояния субъекта все наблюдатели автоматически уведомляются и обновляются.

# Снимок

Паттерн Снимок (Memento) - это поведенческий паттерн проектирования, который позволяет сохранять и восстанавливать предыдущее состояние объекта без нарушения инкапсуляции.

Пример реализации паттерна Снимок на С++:

```c++
#include <iostream>
#include <string>
#include <vector>

class Memento {
private:
    std::string state;
public:
    Memento(const std::string& state) : state(state) {}
    std::string getState() const {
        return state;
    }
};

class Originator {
private:
    std::string state;
public:
    void setState(const std::string& newState) {
        state = newState;
    }
    Memento createMemento() {
        return Memento(state);
    }
    void restoreMemento(const Memento& memento) {
        state = memento.getState();
    }
    void printState() const {
        std::cout << "State: " << state << "\n";
    }
};

class Caretaker {
private:
    std::vector<Memento> mementos;
public:
    void addMemento(const Memento& memento) {
        mementos.push_back(memento);
    }
    Memento getMemento(int index) const {
        return mementos[index];
    }
};

int main() {
    Originator originator;
    Caretaker caretaker;
    originator.setState("State1");
    originator.printState();
    caretaker.addMemento(originator.createMemento());
    originator.setState("State2");
    originator.printState();
    caretaker.addMemento(originator.createMemento());
    originator.restoreMemento(caretaker.getMemento(0));
    originator.printState();
}
```

В данном примере есть классы Memento, Originator и Caretaker. Класс Memento - это класс, который хранит состояние объекта Originator. Класс Originator - это класс, состояние которого сохраняется и восстанавливается. В классе Originator есть методы createMemento и restoreMemento для создания снимка состояния и восстановления состояния из снимка соответственно. Класс Caretaker - это класс, который хранит снимки состояний объекта Originator. В функции main создаются объекты классов Originator и Caretaker, устанавливается начальное состояние объекта Originator, затем создается снимок состояния и сохраняется в объекте Caretaker. Далее изменяется состояние объекта Originator, создается еще один снимок и сохраняется в объекте Caretaker. После этого состояние объекта Originator восстанавливается из первого снимка методом restoreMemento, и состояние выводится на экран методом printState. Таким образом, паттерн Снимок позволяет сохранять и восстанавливать состояние объекта без нарушения инкапсуляции.


Паттерн Посредник (Mediator) - это поведенческий паттерн проектирования, который позволяет уменьшить связанность между объектами, вынося их взаимодействие в отдельный класс-посредник.

Пример реализации паттерна Посредник на С++:

```c++
#include <iostream>
#include <string>
#include <vector>

class Colleague;

class Mediator {
public:
    virtual void sendMessage(const std::string& message, Colleague* colleague) = 0;
};

class Colleague {
protected:
    Mediator* mediator;
public:
    Colleague(Mediator* mediator) : mediator(mediator) {}
    virtual void receiveMessage(const std::string& message) = 0;
    virtual void sendMessage(const std::string& message) = 0;
};

class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(Mediator* mediator) : Colleague(mediator) {}
    void receiveMessage(const std::string& message) override {
        std::cout << "ConcreteColleague1 received message: " << message << std::endl;
    }
    void sendMessage(const std::string& message) override {
        mediator->sendMessage(message, this);
    }
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(Mediator* mediator) : Colleague(mediator) {}
    void receiveMessage(const std::string& message) override {
        std::cout << "ConcreteColleague2 received message: " << message << std::endl;
    }
    void sendMessage(const std::string& message) override {
        mediator->sendMessage(message, this);
    }
};

class ConcreteMediator : public Mediator {
private:
    std::vector<Colleague*> colleagues;
public:
    void addColleague(Colleague* colleague) {
        colleagues.push_back(colleague);
    }
    void sendMessage(const std::string& message, Colleague* colleague) override {
        for (auto c : colleagues) {
            if (c != colleague) {
                c->receiveMessage(message);
            }
        }
    }
};

int main() {
    ConcreteMediator mediator;
    ConcreteColleague1 colleague1(&mediator);
    ConcreteColleague2 colleague2(&mediator);
    mediator.addColleague(&colleague1);
    mediator.addColleague(&colleague2);
    colleague1.sendMessage("Hello, colleague2!");
    colleague2.sendMessage("Hi, colleague1!");
}
```

В данном примере есть классы Colleague и Mediator. Класс Colleague - это класс, который может отправлять и получать сообщения. Класс Mediator - это класс-посредник, который управляет взаимодействием между объектами класса Colleague. В классе Mediator есть метод sendMessage для отправки сообщения коллегам и метод addColleague для добавления коллег в список. В классе Colleague есть методы sendMessage и receiveMessage для отправки и получения сообщений соответственно. В функции main создаются объекты классов ConcreteColleague1, ConcreteColleague2 и ConcreteMediator, коллеги добавляются в список посредника, после чего коллеги отправляют друг другу сообщения методом sendMessage. Таким образом, паттерн Посредник позволяет уменьшить связанность между объектами, вынося их взаимодействие в отдельный класс-посредник.