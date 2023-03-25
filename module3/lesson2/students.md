# Инкапсуляция

## Слова public, private, protected

В C++ есть 3 модификатора доступа: public, protected, private

```
public -- доступно всем, 
protected -- доступно только наследникам внутри кода наследников
private -- не доступно никому
```

public используется для полей и методов, которые предназначены для использования снаружи и внутри кода класса.

protected используется для тех полей и методов, которые в теории нужны классам, которые будут наследоваться от текущего, но снаружи иерархии эти поля и методы не должны быть видны

private используется для тех полей и методов, которые нужны исключительно классу, в котором они написаны, и они не предназначены для использования снаружи


```c++
class Person {
private:
    std::string Name;
    int Age;
protected:
    std::string Address;
public:
    void SetName(const std::string& name) {
        this->Name = name;
    }

    void SetAge(int age) {
        this->Age = age;
    }
};

class Student : public Person {
public:
    void SetAddress(const std::string& address) {
        this->Address = address;
    }
};

int main() {
    Student student;
    student.SetName("John");
    student.SetAge(20);
    student.SetAddress("123 Main St.");
}

```

В этом примере класс `Person` имеет приватные поля `Name` и `Age`, которые доступны только внутри класса. Защищенное поле `Address` доступно для наследников класса, но не для объектов класса. Публичные методы `SetName` и `SetAge` позволяют установить значения для приватных полей.

Класс `Student` наследует от класса `Person` и имеет доступ к защищенному полю `Address`. Публичный метод `SetAddress` позволяет установить значение для этого поля.

В функции main создается объект класса `Student` и устанавливаются его имя, возраст и адрес

## Виды наследования

В C++ наследование может быть `public`, `protected` и `private`.

`public` наследование означает, что все `public` члены базового класса становятся `public` в производном классе, все `protected` члены базового класса становятся `protected` в производном классе, а `private` члены базового класса не наследуются.

`protected` наследование означает, что все `public` и `protected` члены базового класса становятся `protected` в производном классе, а `private` члены базового класса не наследуются.

`private` наследование означает, что все `public` и `protected` члены базового класса становятся `private` в производном классе, а private члены базового класса не наследуются.

По сути, виды наследования созданы для того, чтобы менять уровень доступа к полям и методам родителя, причем менять его для потомков и внешнего кода.

Также возможна следующая интерпритация: 

При `private` наследовании никто не знает, что вы потомок базоого класса

При `protected` наследовании только ваши потомки знают, что вы потомок базового класса

При `public` наследовании все знают, что вы потомок базового класса 

Под словом `знают` здесь имеется ввиду возможность обращаться к полям и методам базового класса, если их уровень доступа этому не противоречит

## Связь между видами наследования и модификаторами доступа

```c++
class SecretVault {
private:
    std::string GetTopSecret() const {
        return "TopSecret";
    }
protected:
    std::string GetSecret() const {
        return "Secret";
    }
public:
    std::string GetNonSecret() const {
        return "NonSecret";
    }
};

class PublicVault : public SecretVault {
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};

class ProtectedVault : protected SecretVault {
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};

class PrivateVault : private SecretVault {
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};

int main() {
    PublicVault publicVault;
    publicVault.GetNonSecret();
    // publicVault.GetSecret(); // CE
    // publicVault.GetTopSecret(); // CE
    
    ProtectedVault protectedVault;
    // protectedVault.GetNonSecret(); // CE
    // protectedVault.GetSecret(); // CE
    // protectedVault.GetTopSecret(); // CE
    
    PrivateVault privateVault;
    // privateVault.GetNonSecret(); // CE
    // privateVault.GetSecret(); // CE
    // privateVault.GetTopSecret(); // CE
}

```

int main() {
    // SecretVault* ptrPrivate = new PrivateVault; // CE
    // SecretVault* ptrProtected = new ProtectedVault; // CE
    SecretVault* ptrPublic = new PublicVault;
}

```c++
class Derived : public PublicVault {
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};
```

```c++
class Derived : public ProtectedVault {
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};
```

```c++
class Derived : public PrivateVault {
    void LogicFunction() {
        // GetNonSecret(); // CE
        // GetSecret(); // CE
        // GetTopSecret(); // CE
    }
};
```

## Дружественные функции

Дружественные функции в С++ - это функции, которые имеют доступ ко _всем_ членам класса, но не являются членами этого класса. Они объявляются с помощью ключевого слова `friend`. После слова `friend` необходимо написать полное объявление функции, а именно тип, имя, типы аргументов

Пример:

```c++
class MyClass {
private:
    int x;

public:
    MyClass() {
        x = 0;
    }

    friend void MyFriendFunction(MyClass obj);
};

void MyFriendFunction(MyClass obj) {
    obj.x = 10;
    std::cout << obj.x;
}

int main() {
    MyClass myObj;
    MyFriendFunction(myObj);
}
```

В этом примере мы объявляем функцию `MyFriendFunction` как дружественную для класса `MyClass`. Эта функция изменяет значение приватного члена `x` объекта `MyClass`. В функции `main` мы создаем объект `MyObj` класса `MyClass` и передаем его в функцию `MyFriendFunction`. Функция изменяет значение `x` на 10 и выводит его на экран.

В том числе, если функция дружественная, она также имеет доступ к типу наследования объекта, а именно `private` и `protected` наследование для неё `условно` становится `public`

Теперь `main` знает, что `PrivateVault` наследник `SecretVault`:
```c++
class PrivateVault : private SecretVault {
    friend int main();
    void LogicFunction() {
        GetNonSecret();
        GetSecret();
        // GetTopSecret(); // CE
    }
};

int main() {
    SecretVault* ptrPrivate = new PrivateVault;
}
```

В С++ есть несколько уровней доступа к членам классов.
А именно, как понять, имеет ли доступ текущая часть кода к члену класса или нет? Дружественность передается по наследству, однако, если само наследование скрыто, то дружественность тоже будет скрыта:

`public` наследование:
```c++
class A {
    int x;
    friend int main();
};

class B : public A {

};

int main() {
    B b;
    b.x = 100; // OK
}
```

`protected` наследование:

```c++
class A {
    int x;
    friend int main();
};

class B : protected A {

};

int main() {
    B b;
    // b.x = 100; // CE
}
```

## Дружественные классы

Дружественный класс в С++ - это класс, который имеет доступ к закрытым членам другого класса, но не является его наследником. Дружественный класс объявляется с помощью ключевого слова `friend`.

Пример:

```c++
class MyClass {
private:
    int x;

public:
    MyClass() {
        x = 0;
    }
    friend class MyFriendClass;
};

class MyFriendClass {
public:
    void MyFriendFunction(MyClass obj) {
        obj.x = 10;
        std::cout << obj.x;
    }
};

int main() {
    MyClass myObj;
    MyFriendClass myFriend;
    myFriend.MyFriendFunction(myObj);
}
```

В этом примере мы объявляем класс `MyFriendClass` как дружественный для класса `MyClass`. Метод `MyFriendFunction` этого класса имеет доступ к закрытому члену `x` объекта `MyClass` и изменяет его значение на 10. В функции `main` мы создаем объект `myObj` класса `MyClass` и объект `myFriend` класса `MyFriendClass`, и вызываем метод `MyFriendFunction` передавая ему объект `myObj`. Метод изменяет значение `x` на 10 и выводит его на экран.

