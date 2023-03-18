## Наследование

Наследование в ООП в C++ позволяет создавать новые классы на основе уже существующих, наследуя их свойства и методы. Это позволяет повторно использовать код, упрощает разработку и поддержку программного обеспечения, уменьшает количество ошибок и ускоряет процесс разработки. Наследование также позволяет создавать иерархии классов, где более общие классы могут быть наследованы более специализированными классами, что облегчает организацию кода и упрощает его понимание.

Наследование в C++ - это механизм, который позволяет создавать новый класс на основе уже существующего класса. Новый класс, называемый производным классом, наследует свойства и методы базового класса, но также может добавлять свои собственные свойства и методы.

Пример кода:

```c++
class Shape {
public:
    void SetWidth(int w) {
        width = w;
    }
    void SetHeight(int h) {
        height = h;
    }
    int GetWidth() {
        return width;
    }
    int GetHeight() {
        return height;
    }
private:
    int width;
    int height;
};

// Производный класс
class Rectangle: public Shape {
public:
    int getArea() {
        return GetWidth() * GetHeight();
    }
};

int main() {
    Rectangle rect;
    rect.SetWidth(5);
    rect.SetHeight(7);
    std::cout << "Площадь прямоугольника: " << rect.getArea() << "\n";
    return 0;
}
```

В этом примере мы создаем базовый класс `Shape`, который имеет два свойства `width` и `height`, и два метода `setWidth()` и `setHeight()`, которые устанавливают значения этих свойств. Затем мы создаем производный класс `Rectangle`, который наследует свойства и методы базового класса, но также добавляет свой собственный метод `getArea()`, который возвращает площадь прямоугольника. В функции `main()` мы создаем объект `Rectangle` и используем методы базового и производного классов для установки ширины и высоты прямоугольника и расчета его площади.


При этом, поля и методы, помеченые как `private` у класса-родителя, также нельзя вызывать и у потомков:

```c++
class Base {
    int PrivateField = 0;
    void PrivateMethod() {
        
    }
public:
    int PublicField = 0;
    void PublicMethod() {

    }
};

class Derived : public Base {
public:
    void LogicFunction() {
        PrivateField = 100; // CE
        PublicField = 100; // OK
        PrivateMethod(); // CE
        PublicMethod(); // OK
    }
};
```


## Перегрузка методов при наследовании

Что будет, если вы объявите 2 метода с одинаковыми сигнатурами у класса - родителя и класса - наследника, а затем вызовете этот метод у наследника?
По сути, как таковой перегрузки не происходит. Если есть хотя бы один метод у класса-наследника, который подходит к вызову, то к методам класса родителя компилятор даже не станет переходить. Поэтому можно писать такой код:

```c++
class Device {
public:
    void PrintID() {
        std::cout << "Device\n";
    }
};

class Laptop : public Device {
public:
    void PrintID() {
        std::cout << "Laptop\n";
    }
};


int main() {
    Laptop obj;
    obj.PrintID(); // Laptop
    obj.Device::PrintID(); // Device
}
```

`obj.PrintId()` выведет `Laptop`, хоть точно такой же метод есть и у родителя.
Чтобы вызвать `PrintId()` непосредственно родителя, нужно написать следующий синтаксис `obj.Device::PrintId`. Т.е. после точки ставите имя класса родителя, затем `::`, а затем метод, который хотите вызвать.

Также работает и внутри класса наследника:


```c++
class Device {
public:
    void PrintID() {
        std::cout << "Device\n";
    }
};

class Laptop : public Device {
public:
    void PrintID() {
        std::cout << "Laptop\n";
    }
    void LogicFuntion() {
        PrintID(); // Laptop
        Device::PrintID(); // Device
    }
};
```

Чтобы лучше продемонстрировать это, можно также посмотреть и на следующий пример:

```c++
class Base {
public:
    void Method(double x) {
        std::cout << "Base\n";
    }
};

struct Derived : public Base {
public:
    void Method(int x) {
        std::cout << "Derived\n";
    }
};

int main() {
    Derived obj;
    obj.Method(3.14);
}
```

У `obj` вызывется `Method` с аргументом типа `double`. Но все равно будет выбрана версия метода потомка, которая принимет `int`, хоть и есть такой же метод у родителя, принимающий в точности `double`

# Множественное наследование

Множественное наследование - это возможность класса наследовать свойства и методы нескольких базовых классов. В С++, класс может наследовать от нескольких классов с помощью оператора наследования `:`, разделяя имена базовых классов запятыми.

```c++
class Person {
public:
    void SayHello() {
        std::cout << "Hello!\n";
    }
};

class Employee {
public:
    void DoWork() {
        std::cout << "Working hard...\n";
    }
};

class Manager : public Person, public Employee {
public:
    void Manage() {
        std::cout << "Managing employees...\n";
    }
};

int main() {
    Manager manager;
    manager.SayHello();
    manager.DoWork();
    manager.Manage();
}
```

В этом примере класс `Manager` наследует методы `sayHello()` от класса `Person` и методы `doWork()` от класса `Employee`. Таким образом, объект класса `Manager` может вызывать как метод `SayHello()`, так и метод `DoWork()`. Кроме того, в классе `Manager` определен дополнительный метод `Manage()`, который не наследуется от других классов.

## Ромбовидное наследование

Ромбовидное наследование в C++ возникает, когда производный класс наследуется от двух или более классов, которые в свою очередь имеют общего предка. Это приводит к созданию ромбовидной структуры, где производный класс находится в вершине ромба, а два базовых класса - на его боковых сторонах.

Пример кода:

```c++
// Базовый класс
class Person {
public:
    void SayHello() {
        std::cout << "Привет, я человек\n";
    }
};

// Производный класс
class Student: public Person {
public:
    void Study() {
        std::cout << "Я учусь\n";
    }
};

// Производный класс
class Teacher: public Person {
public:
    void Teach() {
        std::cout << "Я преподаю\n";
    }
};

// Производный класс
class TeachingAssistant: public Student, public Teacher {
public:
    void Assist() {
        std::cout << "Я помогаю преподавателю\n";
    }
};

int main() {
    TeachingAssistant* ta = new TeachingAssistant();
    ta->SayHello(); // Привет, я человек
    ta->Study(); // Я учусь
    ta->Teach(); // Я преподаю
    ta->Assist(); // Я помогаю преподавателю
    delete ta;
}
```

В этом примере мы создаем базовый класс `Person`, который имеет метод `SayHello()`, выводящий сообщение о том, что это человек. Затем мы создаем два производных класса `Student` и `Teacher`, которые наследуют метод `SayHello()` от базового класса и добавляют свои собственные методы `Study()` и `Teach()`. Наконец, мы создаем производный класс `TeachingAssistant`, который наследует от обоих производных классов `Student` и `Teacher` и добавляет свой собственный метод `Assist()`.


##  Наследование низкоуровнево

Пусть у нас есть иерархия классов, одни наследуются от других. Вы создаете объект ребенка. Как стоит относиться ко всей иерархии наследования? Предлагается рассматривать её просто как один большой сложный объект. Этот объект состоит из нескольких блоков, каждый блок для класса из иерархии наследования. В самом простом случае, если `Derived` наследуется от `Base`, этот объект будет состоять из двух блоков. Первый -- для `Base`, второй -- для `Derived`. Все объекты лежат где-то в памяти, значит и эти блоки тоже лежат. Причем располагаются они подряд.

Рассмотрим такой пример:

```c++
class Granny {
public:
    int x;
};

class Mother : public Granny {
public:
    int y;
};

class Daughter : public Mother {
public:
    int z;
};
```

Если вы создадите объект `Daughter`, то он будет весить 3 * 4 байт, тк хранит 3 объекта типа `int`. Также он будет состоять из 3 блоков, причем в памяти они будут располагаться так:

|Granny|Mother|Daughter|
|:--:|:--:|:--:|
|x|y|z|

И это всё один объект `Daughter`.

Аналогично, если вы создадите объект `Mother`, то в памяти он будет располагаться так:

|Granny|Mother|
|:--:|:--:|
|x|y|


## Порядок создания классов

Вовзращаемся к вопросу о порядке создания объектов.
В случае наследования в начале создается целиком родитель, а только после этого создается ребенок.

```c++
class Base {
public:
    Base() {
        std::cout << "Base\n";
    }
    ~Base() {
        std::cout << "~Base\n";
    }
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived\n";
    }
    ~Derived() {
        std::cout << "~Derived\n";
    }
};

int main() {
    Derived obj;
}
```
Вывод:
```
Base
Derived
~Derived
~Base
```

Как видно из вывода в начале была создана часть, касающаяся `Base`, и только после этого `Derived`. Порядок удаления обратный. Сначала удалется целиком потомок, и только после этого -- родитель. У этого есть несколько причин. В конструкторе потомка мы уже можем пользоваться полями и методами родителя, и чтобы это было возможно, к этому моменту родитель уже должен быть целиком создан

## Вызов конструкторов родителей

```c++
class Base {
    int x;
public:
    Base(int x) : x(x) {};
    
};

class Derived : public Base {
};

int main() {
    Derived obj;
}
```

При попытке создать объект класса Derived будет ошибка компиляции. Дейтсвительно, у `Base` нет конструктора по умолчанию. При этом, если исправить `main` на такой:

```c++
int main() {
    Derived obj(5);
}
```
нельзя, тк у `Derived` нет конструктора от `int`. Чтобы это исправить, нужно вызывать конструктор `Base` явно, причем в классе `Derived`. Сделать это можно так:

```c++
class Base {
    int x;
public:
    Base(int x) : x(x) {};

};

struct Derived : public Base {
    Derived() : Base(5) {};
};

int main() {
    Derived obj;
}
```

В `member initializer list` конструктора `Derived` вы вызываете конструктор родителя. Теперь код будет работать.





## static_cast

`static_cast` - это оператор приведения типов в C++, который выполняет явное преобразование одного типа данных в другой. Он используется для преобразования указателей или ссылок на объекты одного типа в указатели или ссылки соответственно на объекты другого типа, а также для преобразования числовых типов данных.

```c++
class Base {
public:
    int x = 5;
    void Print() {
        std::cout << "Hello from base\n";
    }
};

struct Derived : public Base {
public:
    int y = 6;
    void Print() {
        std::cout << "Hello from derived\n";
    }
};

int main() {
    Derived* obj = new Derived;
    obj->Print(); // Hello from derived
    std::cout << obj << "\n";
    Base* objBase = static_cast<Derived*>(obj);
    objBase->Print(); // Hello from base
    std::cout << objBase << "\n";
    delete obj;
}
```
Вывод
```
Hello from derived
0x55e179b18eb0
Hello from base
0x55e179b18eb0
```

В этом примере мы создаем объект `Derived`, а затем записываем его адрес в переменную типа `Base*`.
После вызываем у неё метод `Print()`. Он выводит `Hello from base`, т.к. теперь компилятор воспринимает `objBase` как указатель на объект типа `Base`, а значит и работает с ним как с `Base`. Хотя на самом деле там лежит объект типа `Derived`.
Также заметьте, что адреса получились одинаковыми, это связано с расположением объекта в памяти. Начало `Base` такое же, как и у `Derived` из-за блочной структуры описанной выше. Это второй аргумент в пользу подобной структуры, компилятору ничего не стоит скастовать один тип указателя в другой, если объекты имеют один адрес. Тут мы приблизились к такой теме, как статические и динамические типы, но её мы обсудим позднее.

Также `static_cast` позволяет кастовать и вниз по иерархии, чем отличаются эти примеры?

1. 
```c++
int main() {
    Base obj;
    Base* objBase = &obj;
    Derived* objDerived = static_cast<Derived*>(objBase);
    std::cout << objDerived->y;
}
```

2. 
```c++
int main() {
    Derived obj;
    Base* objBase = &obj;
    Derived* objDerived = static_cast<Derived*>(objBase);
    std::cout << objDerived->y;
}
```

В обоих примерах мы преобразуем `Base*` в `Derived*`, во втором примере под этим адресом действительно лежит объект типа `Derived`, однако в первом примере там находится объект типа `Base`. Однако оба примера компилируются. 

В первом примере происходит `UB`, так нельзя писать. Не совсем правильно работать с адресом так, будто там лежит потомок, когда на самом деле создан лишь родитель. Однако С++ позволяет такое писать, будьте осторожны.

Это касается и ссылок, с ними тоже можно так работать:
```c++
int main() {
    Derived obj;
    Base& objBase = obj;
    Derived& objDerived = static_cast<Derived&>(objBase);
    std::cout << objDerived.y;
}
```


Также хочется отметить еще один пример неправильного использования указателей:

Кто-то может написать такой код:

```c++
class Base {
public:
    Base() {
        std::cout << "Base\n";
    }
    ~Base() {
        std::cout << "~Base\n";
    }
};

struct Derived : public Base {
public:
    Derived() {
        std::cout << "Derived\n";
    }
    ~Derived() {
        std::cout << "~Derived\n";
    }
};

int main() {
    Base* obj = new Derived;
    delete obj;
}
```
Вывод:
```c++
Base
Derived
~Base
```

Мы создаем объект типа `Derived`, но в `delete` передаем адрес(в целом корректный), но типа `Base*`. Поэтому вызывается деструктор только `Base`. Деструктор `Derived` не вызывается. Чтобы это исправить, можно написать так
```c++
int main() {
    Base* obj = new Derived;
    delete static_cast<Derived*>(obj);
}
```

Необходимо быть осторожным при использовании `static_cast` и в целом кастов указателей, убедиться, что типы данных корректны, чтобы избежать неопределенного поведения(UB).



## Пример задачи

Итак, задача. У вас есть приложение, а в нем пользователи. У каждого пользователя есть свой уникальный `id`. Приложение - обычный мессенджер, а ваш класс будет управлять чатом. Взаимодействие с классом будет следующее, он извне получает запросы об изменении состояния чата(добавление пользователя, новые сообщения, бан пользователей и т.п.). У каждого из этих запросов есть отправитель, конкретный пользователь со своим `id`. Дело в том, что в чатах обычно есть роли пользователей, поэтому, скажем, удалять сообщения других людей могут только модераторы, а добавлять в чат новых людей могут только админы.

Список ролей у пользователей:
|Роль|Описание|
|:--:|:--:|
|ADMIN|Может регистрировать новых пользователей, давать роль админа или модератора другим пользователям, а также полностью останавливать чат|
|MODERATOR|Может банить пользователей, создавать других модераторов, а также полностью редактировать все сообщения|
|BANNED|Не может ничего, предполагается, что ни ADMIN, ни MODERATOR не станут BANNED|
|USER|Может писать сообщения, а также редактировать сообщения, но только свои|

Как можете видеть, один и тот же пользователь в праве иметь несколько ролей сразу. Например, `ADMIN`, `MODERATOR`, `USER`.

Итак, у каждого запроса есть отправитель.

Также на каждый запрос ваш класс должен возвращать ответ в следующем виде:

```c++
struct ResposeData {
    bool Success;
    std::string Response;
};
```
Где `Success` -- выполнил ли класс запрос. `Response` -- комментарий класса об ошибке, если `Success` равен `false`

Итак, вас попросили написать класс со следующими методами. Везде `sender`, это отправитель запроса. В конструкторе единственный аргумент, id самого первого админа.

```c++
class SystemBase {
public:
    SystemBase(int admin);
    ResposeData BanUser(int sender, int user);
    ResposeData UnBanUser(int sender, int user);
    ResposeData RegisterNewUser(int sender, int newUser);
    ResposeData GrantModeratorRole(int sender, int user);
    ResposeData GrantAdminRole(int sender, int user);
    ResposeData StopChat(int sender);
    ResposeData ResumeChat(int sender);
};
```

При этом, если запрос некорректен, например, метод `GrantAdminRole` вызван от `sender`, который сам не является админом, то такой метод в `ResponseData` должен иметь `Success = false`, комментарий не важен.

Пример работы:
```c++
void PrintResponse(const ResposeData& response) {
    std::cout << "result: " << response.Success << "\nresponse: " << response.Response << "\n";
}

int main() {
    const int USER1 = 1;
    const int USER2 = 2;
    const int USER3 = 3;
    SystemBase chat(1);

    auto responseRegisterFromAdmin1 = chat.RegisterNewUser(USER1, USER2);
    PrintResponse(responseRegisterFromAdmin1);
    auto responseRegisterFromAdmin2 = chat.RegisterNewUser(USER1, USER2);
    PrintResponse(responseRegisterFromAdmin2);
    auto responseGrantFromAdmin = chat.GrantModeratorRole(USER1, USER2);
    PrintResponse(responseGrantFromAdmin);
    auto responseRegisterFromModerator = chat.RegisterNewUser(USER2, USER3);
    PrintResponse(responseRegisterFromModerator);
    auto responseRegisterFromAdmin3 = chat.RegisterNewUser(USER1, USER3);
    PrintResponse(responseRegisterFromAdmin3);
    auto responseBanFromModer = chat.BanUser(USER2, USER3);
    PrintResponse(responseBanFromModer);
    auto responseStopFromModer = chat.StopChat(USER2);
    PrintResponse(responseStopFromModer);
    auto responseStopFromAdmin = chat.StopChat(USER1);
    PrintResponse(responseStopFromAdmin);
}
```
Вывод:
```
result: 1
response: 
result: 0
response: already registered
result: 1
response: 
result: 0
response: only admin can register
result: 1
response: 
result: 1
response: 
result: 0
response: only admin can stop chat
result: 1
response: 
```

Тот, кто попросил вас написать этот класс считает, что в `ResposeData` сам `Response` может быть любыми, главное, чтобы `Success` был корректным. Т.е. вывод в примере после `response: ` может быть любым


Указания:

Реализуйте логику выдачи ролей пользователям в отдельном классе `AccessControl`.
Реализуйте логику остановки чата в отдельном классе `Pausable`. Слова `реализуйте логику` означают, что ни `AccessControl`, ни `Pausable` ничего не знают про класс `SystemBase` и уже самодостаточны. Классу `SystemBase` необходимо лишь наследоваться от этих двух классов, чтобы включить в себя их функционал.

В систему отправляйте лишь код полученных классов. Главное, чтобы  ваш `SystemBase` соответствовал интерфейсу, указанному выше

```c++
class AccessControl {
    std::unordered_set<std::string> KnownRoles; // Список ролей
    std::unordered_map<std::string, std::unordered_set<int>> GrantedRoles; // Роль -> список пользователей
    bool RoleExists(const std::string& roleName) const {
        return KnownRoles.count(roleName);
    }
public:
    bool HasRole(int id, const std::string& roleName) const {
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        auto& usersList = GrantedRoles.find(roleName)->second;
        return usersList.count(id) == 1;
    }

    bool GrantRole(int id, const std::string& roleName) { // bool - успешно ли
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        GrantedRoles[roleName].insert(id);
        return true;
    }
    bool RemoveRole(int id, const std::string& roleName) { // bool - успешно ли
        if (!RoleExists(roleName)) { // Такой роли нет
            return false;
        }
        auto& roleInfo = GrantedRoles[roleName];
        auto iter = roleInfo.find(id);
        if (iter == roleInfo.end()) { // У пользователя уже нет такой роли
            return false;
        }
        roleInfo.erase(iter);
        return true;
    }

    void RegisterRole(const std::string& roleName) {
        KnownRoles.insert(roleName);
        GrantedRoles.insert({roleName, {}});
    }
};

class Pausable {
    bool Paused = false;
public:
    bool IsPaused() const {
        return Paused;
    }
    void Pause() {
        Paused = true;
    }
    void UnPause() {
        Paused = false;
    }
};


struct ResposeData {
    bool Success;
    std::string Response;
};

ResposeData MakeSuccessResponse() {
    return {true, ""};
}

ResposeData MakeFailedResponse(const std::string& response) {
    return {false, response};
}


class SystemBase : public AccessControl, public Pausable {
    const std::string ADMIN_ROLE = "admin";
    const std::string USER_ROLE = "user";
    const std::string MODERATOR_ROLE = "moderator";
    const std::string BANNED_ROLE = "banned";
public:
    SystemBase(int admin) {
        RegisterRole(ADMIN_ROLE);
        RegisterRole(USER_ROLE);
        RegisterRole(MODERATOR_ROLE);
        RegisterRole(BANNED_ROLE);
        GrantRole(admin, ADMIN_ROLE);
    }

    ResposeData BanUser(int sender, int user)  {
        if (!HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only moderator can ban");
        }
        if (HasRole(user, BANNED_ROLE)) {
            return MakeFailedResponse("already banned");
        }
        GrantRole(user, BANNED_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData UnBanUser(int sender, int user)  {
        if (!HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only moderator can unban");
        }
        if (!HasRole(user, BANNED_ROLE)) {
            return MakeFailedResponse("already unbanned");
        }
        RemoveRole(user, BANNED_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData RegisterNewUser(int sender, int newUser) {
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can register");
        }
        if (HasRole(newUser, USER_ROLE)) { // Пользователь уже зареган
            return MakeFailedResponse("already registered");
        }
        GrantRole(newUser, USER_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData GrantModeratorRole(int sender, int user) {
        if (!HasRole(sender, ADMIN_ROLE) && !HasRole(sender, MODERATOR_ROLE)) {
            return MakeFailedResponse("only admin or moderator can grant moderator role");
        }
        GrantRole(user, MODERATOR_ROLE);
        return MakeSuccessResponse();
    }
    ResposeData GrantAdminRole(int sender, int user) {
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can grant admin role");
        }
        GrantRole(user, ADMIN_ROLE);
        return MakeSuccessResponse();
    }

    ResposeData StopChat(int sender) {
        if (IsPaused()) {
            return MakeFailedResponse("already stopped");
        }
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin can stop chat");
        }
        Pause();
        return MakeSuccessResponse();
    }
    ResposeData ResumeChat(int sender) {
        if (!IsPaused()) {
            return MakeFailedResponse("already unpaused");
        }
        if (!HasRole(sender, ADMIN_ROLE)) {
            return MakeFailedResponse("only admin");
        }
        UnPause();
        return MakeSuccessResponse();
    }
};
```