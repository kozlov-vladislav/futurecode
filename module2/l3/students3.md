std::vector
=====

# Понятие класса. Приватные и публичные поля и методы

Во время реализации структур, вы могли заметить, что далеко не все поля и методы предполагается использовать конечному пользователю. А именно, часть из них хотелось бы скрыть. В языке С++, есть такие 2 понятия как `private` и `public` поля и методы. Все, что вы до этого писали в структурах, было `public`. Просто потому что они таковы по умолчанию в структурах. Но можно явно указать, что мы хотим. Синтаксис такой:

```c++
struct Имя{
    // До первого private все по умолчанию публично
private:
    // Все, что тут написать, будет приватным
    // ...
public:
    // А здесь публичным
private:
    // Снова приватным
    // ...
    // И т.д.
};
```

```c++

struct PublicStruct {
    int x; // Доступно всем
private:
    int y; // Доступно только внутри PublicStruct
    std::string str; // Доступно только внутри PublicStruct
public:
    int z; // Опять доступно всем
    double eps;
};

int main() {
    PublicStruct ps;
    ps.x; // OK
    ps.y; // CE -- y - приватный
    ps.str; // CE -- str - приватный
    ps.z; // OK
    ps.eps; // OK
}
```

Работа с приватными полями внутри структуры точно такая же, как и раньше. Разница лишь в том, что они _не видны_ снаружи структуры, т.е. к ним нельзя явно обратиться.

-------

# class

Даайте в прошлом примере слово `struct` заменим на `class`. Получится та же самая структура, единственное отличие в том, что у класса поля по умолчанию приватные, а не публичные.

```c++

class PrivateClass {
    int x; // Доступно только внутри PrivateClass
private:
    int y; // Все еще доступно только внутри PrivateClass
    std::string str;
public:
    int z; // А это доступно всем
    double eps;
};

int main() {
    PrivateClass pс;
    pс.x; // CE -- x - привтаный по умолчанию
    pс.y; // CE -- y - приватный
    pс.str; // CE -- str - приватный
    pс.z; // OK
    pс.eps; // OK
}

```


# vector

Вектор уже встречался в предыдущих занятиях, сейчас же цель -- разобраться в его работе изнутри.

Вектор - это массив изменяемой длины. Пусть `size` -- текущий размер вектора. У его элементов есть порядок, а именно у каждого из них есть свой индекс. Индексы идут от `0` до `size - 1`. Началом вектора считается элемент с индексом `0`, концом -- элемент с индексом `size - 1`.

Под изменяемой длиной подразуемевается несколько конкретных операций с вектором:

1. `resize(new_size)`: если `size` > `new_size`, то добавить в конец столько элементов, чтобы размер вектора стал `new_size`. Если размер `size` < `new`, то удалить с конца вектора столько элементов, чтобы размер стал равен `new_size`
2. `push_back(x)`: добавить в конец вектора элемент `x`
3. `pop_back()`: удалить последний элемент вектора
4. `insert(index, x)`: добавить элемент `x` в вектор таким образом, чтобы он стоял на индексе `index`

Отдельный вопрос, каким именно образом можно добиться увеличения памяти, и за сколько времени работает каждая из операций выше.


Идея в следующем, давайте выделим сразу какое-то количество памяти, даже если столько пока не требуется для хранения элементов. Выделять память будем динамически, поэтому будем хранить указатель на выделенную память и её размер. размер выделенной памяти будем хранить в поле `capacity`. Еще нужно хранить сколько памяти уже задействовано на хранение элементов, делать это будем в поле `size`.

Пример: `capacity` = 10, `size` = 4. Это значит, что в векторе выделено памяти под хранение 10 элементов. Но действительно там сейчас есть только 5 элементов, их индексы 0, 1, 2, 3. Значит, у нас есть еще 6 мест для новых переменных. При этом пользователь нашего класса знает лишь, что в нем хранится 4 элемента. Что выделено место под 10 переменных ему знать не обязательно.

Начнем писать код. Резервируем память в конструкторе, не забываем удалить её в дестукторе. Метод `Аt` возвращает `index`-ый элемент массива

```c++
template<typename T>
class Vector {
public:
    T* buffer;
    unsigned int capacity = 10;
    unsigned int size = 0;
    Vector() {
        buffer = new T[capacity];
    }
    T& At(unsigned int index) {
        return buffer[index];
    }
    ~Vector() {
        delete[] buffer;
    }

};
```

Как тогда реализовать `push_back`? Пока поступим следующим образом: если `size` < `capacity`, т.е. еще есть свободные места, то просто добавим в конец уже существющим элементам новый элемент.


```c++
void PushBack(const T& element) {
    if (size < capacity) {
        auto newIndex = size;
        buffer[newIndex] = element;
        ++size;
    }
}
```

Но что делать, если вся память уже израсходована? Нужно её выделить заново, но уже больше. Тогда в новую нужно перенести содержимое старой и удалить ненужную. Более того, давайте если `size` = `capacity`, то выделять будем размера `2 * capacity`. Эту процедуру реализуем в SetNewCapacity. Тогда остаётся в начале `push_back` просто проверить, нужно ли увеличивать размер или нет:

```c++
void SetNewCapacity(unsigned int newCap) {
    capacity = newCap;
    T* newBuffer = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}

void PushBack(const T& element) {
    if (size == capacity) {
        SetNewCapacity(2 * capacity);
    }
    
    auto newIndex = size;
    buffer[newIndex] = element;
    ++size;
}
```

Теперь перейдем к `pop_back`. Он реализовывается намного проще, будем просто уменьшать `size` на 1.

```c++
void PopBack() {
    --size;
}
```

Напишем еще метод `Size`, возвращающий текущий размер.

```c++

unsigned Size() {
    return size;
}

```

И метод `Resize`:

```c++
void Resize(unsigned int newSize) {
    if (newSize > capacity) {
        SetNewCapacity(2 * newSize);
    }
    size = newSize;
}
```


У нас почти готов минимальный вектор. В `std::vector` есть возможность обращаться по квадратным скобочкам []. В C++ это называется `operator[]`, перегрузим его.

```c++
T& operator[](unsigned int index) {
    return buffer[index];
}
```

На самом деле, минимально мы уже реализовали вектор. Соберем весь код воедино и проверим, как он работает

```c++
template<typename T>
class Vector {
    T* buffer;
    unsigned int capacity = 100;
    unsigned int size = 0;

    void SetNewCapacity(unsigned int newCap) {
        capacity = newCap;
        T* newBuffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
    }

public:

    Vector() {
        buffer = new T[capacity];
    }

    ~Vector() {
        delete[] buffer;
    }

    T& At(unsigned int index) {
        return buffer[index];
    }

    T& operator[](unsigned int index) {
        return buffer[index];
    }

    void PushBack(const T& element) {
        if (size == capacity) {
            SetNewCapacity(2 * capacity);
        }
        auto newIndex = size;
        buffer[newIndex] = element;
        ++size;
    }

    void PopBack() {
        --size;
    }

    void Resize(unsigned int newSize) {
        if (newSize > capacity) {
            SetNewCapacity(2 * newSize);
        }
        size = newSize;
    }

    unsigned int Size() {
        return size;
    }
};
```

Посмотрим на работу:

```c++
void printVector(Vector<int>& vec) {
    std::cout << "Vector size is " << vec.Size() << "\nVector elements are: ";
    for (unsigned int i = 0; i < vec.Size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    Vector<int> vec;

    vec.PushBack(5);
    vec.PushBack(6);
    vec.PushBack(7);
    printVector(vec);

    vec[1] = 100;
    std::cout << "\nChanged vec[1] = 100\n";
    printVector(vec);

    vec.PopBack();
    std::cout << "\npop_back\n";
    printVector(vec);
}
```
Вывод:

```
Vector size is 3
Vector elements are: 5 6 7 

Changed vec[1] = 100
Vector size is 3
Vector elements are: 5 100 7 

pop_back
Vector size is 2
Vector elements are: 5 100 
```

Видно, что наш собственный вектор работает, как ожидалось.

Обсудим время работы `push_back`. Всякий раз, когда $capacity > size$, мы просто записываем элемент на нужный индекс, т.е. тратим ~ 1 действие. Но вот если выделенной памяти не хватает, то нам приходится выделять её заново. Причем выделяем мы $2 * size$ новой памяти. С другой стороны, это происходит довольно редко. Поэтому точно ответить на вопрос, сколько работает этот метод, не получится. Это напрямую зависит от его текущих $size$ и $capacity$.

Но мы можем сказать, сколько в среднем он работает. В среднем означает следующее, давайте $M$ раз вызовем `push_back`, посчитаем, сколько суммарно действий мы сделали - $Total$, и поделим $Total$ на $M$.

Итак, за $M$ действий мы $M$ раз добавляли элемент, и еще сколько то раз выделяли память. Суммарно можно оценить выделенную память сверху вот таким числом $1 + 2 + 4 + 8 + ... + 2^k$. Степени 2-ки здесь из-за того, что каждый раз мы просим память в 2 раза больше, чем раньше. При этом $k$ такое максимальное, что $2^k \leq M$.

Но $1 + 2 + 4 + 8 + ... + 2^k = 2^{k+1} - 1 \leq 2 * M - 1 \leq 2 * M$

Итого, $M$ действий на добавление элементов, $2*M$ действий на выделение, $Total = 3 * M$. В среднем $\frac {Total}{M} = \frac {3 * M}{M} = 3 = O^*(1)$

$O(1)$ пишут, когда метод работает за не дольше, чем какое-то константное кол-во действий

В нашем векторе мы получили число 3, если посчитать более аккуратно, то получится чуть меньшее число, но все это означает, что на каждый `push_back` в среднем тратится совсем немного времени.

-------

Осталось еще написать конструктор `Vector(size)` и `Vector(size, defaultValue)`

Перепишем конструкторы следующим образом:

```c++
Vector() {
    buffer = new T[capacity];
}

Vector(unsigned int size) : size(size), capacity(2 * size) {
    buffer = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
            buffer[i] = T();
    }
}

Vector(unsigned int size, const T& defaultValue) : size(size), capacity(2 * size) {
    buffer = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = defaultValue;
    }
}
```

Также, как правило, если вам пришлось писать нетривиальный конструктор, то скорее всего придется написать и `copy`-конструктор, а также оператор присваивания. Действительно, в нашем векторе это нужно явно реализовать.

```c++
Vector(const Vector& another) : size(another.size), capacity(another.capacity) {
    buffer = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = another.buffer[i];
    }
}

Vector& operator= (const Vector& another) {
    if (&another == this) {
        return *this;
    }
    delete[] buffer;
    size = another.size;
    capacity = another.capacity;
    buffer = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        buffer[i] = another.buffer[i];
    }
}
```

Наш вектор стал намного лучше

_Примечение_: можно заметить, что в конструкторах очень много строчек повторяются. Копипаста это плохо, можно немного переписать `operator=`, вот вариант, подумайте, почему это то же самое, что и раньше:

```c++
void swapWithAnother(Vector& another) {
    std::swap(size, another.size);
    std::swap(capacity, another.capacity);
    std::swap(buffer, another.buffer);
}

Vector& operator= (const Vector& another) {
    if (&another == this) {
        return *this;
    }
    Vector tempVector = another;
    swapWithAnother(tempVector);
}
```

Итак, осталось правильно поставить модификаторы `const` к некоторым методам и получится такой код:

```c++
template<typename T>
class Vector {
    T* buffer;
    unsigned int size = 0;
    unsigned int capacity = 10;

    void SetNewCapacity(unsigned int newCap) {
        capacity = newCap;
        T* newBuffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            newBuffer[i] = buffer[i];
        }
        delete[] buffer;
        buffer = newBuffer;
    }

public:

    Vector() {
        buffer = new T[capacity];
    }

    Vector(unsigned int size) : size(size), capacity(2 * size) {
        buffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            buffer[i] = T();
        }
    }

    Vector(unsigned int size, const T& defaultValue) : size(size), capacity(2 * size) {
        buffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            buffer[i] = defaultValue;
        }
    }

    Vector(const Vector& another) : size(another.size), capacity(another.capacity) {
        buffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            buffer[i] = another.buffer[i];
        }
    }

    Vector& operator=(const Vector& another) {
        if (&another == this) {
            return *this;
        }
        delete[] buffer;
        size = another.size;
        capacity = another.capacity;
        buffer = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            buffer[i] = another.buffer[i];
        }
    }

    ~Vector() {
        delete[] buffer;
    }

    T& At(unsigned int index) {
        return buffer[index];
    }

    const T& At(unsigned int index) const {
        return buffer[index];
    }

    T& operator[](unsigned int index) {
        return buffer[index];
    }

    const T& operator[](unsigned int index) const {
        return buffer[index];
    }

    void PushBack(const T& element) {
        if (size == capacity) {
            SetNewCapacity(2 * capacity);
        }
        auto newIndex = size;
        buffer[newIndex] = element;
        ++size;
    }

    void PopBack() {
        --size;
    }

    void Resize(unsigned int newSize) {
        if (newSize > capacity) {
            SetNewCapacity(2 * newSize);
        }
        size = newSize;
    }

    unsigned int Size() const {
        return size;
    }
};
```

Теперь несколько комментариев по реальному вектору
1. Он устроен намного сложнее
2. Как видите, память только увеличивается, но не уменьшается. Поэтому size вектора еще не говорит о реальном потреблении памяти
3. Метод `at` придуман не просто так, в std::vector он _кидает исключение_, если обращаются по неправильному индексу. Пока мы не говорим, что это означает
4. Можно управлять чуть тоньше ресурсами, которыми он пользуется
5. Вызовы `push_back` почти всегда работают быстро, и только иногда мы перевыделяем память, что занимает много времени. При этом, все равно в среднем `push_back` работает за так называемую $O^*(1)$, это означает константное кол-во действий в среднем.


# Итераторы

Вспомним, что умеют указатели. 

```c++
int arr[10];
int i = 5;
int* ptr = &arr[i]; // можно писать arr + i -- адрес i-ого элемента
```

с `ptr` можно делать следующее:

1. `ptr + k` -- сдвинуть адрес на k вперед
2. `k + ptr` -- сдвинуть адрес на k вперед
3. `ptr - k` -- сдвинуть адрес на k назад
4. `++ptr` -- сдвинуть адрес на 1 вперед
5. `--ptr` -- сдвинуть адрес на 1 назад
6. `ptr++` -- сдвинуть адрес на 1 вперед
7. `ptr--` -- сдвинуть адрес на 1 назад

Сдвигая адрес, мы по сути переходим от одних элементов к другим в массиве

Хочется подобный инструмент, но не для массива, а для контейнеров таких как вектор.

И они есть, называются итераторы.

```c++
std::vector<int> vec;
```
Пусть есть некоторый вектор.

Тогда можно получить итератор на его первый элемент с помощью метода `begin`:

```c++
auto iter = vec.begin();
```

Итератор, это специальный объект, работа с которым очень похожа на указатель, а именно:

Можно разименовывать:
1. `*iter` -- значение элемента, на который указывает итератор

Можно прибавлять числа

1. `*iter` -- первый элемент вектора

2. `*(iter + 1)` -- второй элемент вектора

3. `*(iter + 2)` -- третий элемент вектора

4. и.т.д.

Можно изменять сам итератор:

1. `++iter`  - итератор на следующий элемент.
1. `iter++`  - итератор на следующий элемент.
1. `--iter`  - итератор на предыдущий элемент.
1. `iter--`  - итератор на предыдущий элемент.

Для лучшего понимания давайте рассмотрим 2 примера, в первом переберем все элементы классического массива с помощью указателей, а во втором -- все элементы вектора с помощью итератора

```c++
int arr[10];
int* ptr = arr;
int n = 10;
for (int i = 0; i < n; ++i) {
    *ptr = i;
    ++ptr;
}

for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
}
```
Вывод:
```
0 1 2 3 4 5 6 7 8 9
```

```c++
std::vector<int> vec(10);
auto iter = vec.begin();
int n = 10;
for (int i = 0; i < n; ++i) {
    *iter = i;
    ++iter;
}

for (int i = 0; i < n; ++i) {
    std::cout << arr[i] << " ";
}
```
Вывод:
```
0 1 2 3 4 5 6 7 8 9
```

В случае вектора итератор это то же, что и указатель на элементы.

К слову, у итераторов есть свои типы, но они записываются довольно сложно, поэтому обычно пишут слово `auto`. Если без него, то тип на самом деле такой:

```c++
std::vector<int>::iterator iter = vec.begin();
```

Также у вектора и почти всех других контейнеров, что мы рассмотрим, есть метод `end()`. Он возвращает итератор, но не на последний элемент, как могло показаться, а итератор на элемент, идущий после последнего(Да, такого нет, но представьте, будто есть). Т.е. `end()` -- метка конца всех элементов, и если какой-то итератор равняется `end()`, мы дошли до конца контейнера. Давайте переберем элементы вектора, используя `begin` и `end`:

```c++
std::vector<int> vec(10);
auto last = vec.end();
for (auto iter = vec.begin(); it != last; ++it) {
    *iter = i;
}
```

Как получить итератор не на первый элемент, а на `i`-ый? Просто прибавить к `vec.begin()` число `i`:
```c++
auto it = vec.begin() + i;
```


Может, показаться, что итераторы не особо и нужны. Действительно, они делают ровно то, что и указатели. Оказывается, это хоть и верно для `std::vector`, но вот для других контейнеров это уже не так. В следующем стандартном контейнере, который мы рассмотрим, `std::list`, уже нельзя пользоваться ни указателями, ни индексами элементов. И без итераторов его элементы уже никак не перебрать. 


Но пока давайте до конца разберемся с итераторами в векторе, и что можно с ними делать.

Мы говорили _итератор на элемент_, но правильнее было бы говорить, что итератор связан не с элементом, а с позицией в векторе. Приняв такую интерпритацию, можно перейти к последнему незатронотому методу вектора. 

При реализации вектора мы задались несколькими вопросами, и последний из них был, как вставлять элемент не в конец вектора, а в произвольную позицию. Это умеет делать метод `insert(итератор iter, элемент x)`. Пусть итератор указывает на индекс `i`. Тогда `x` будет вставлен так, чтобы оказаться на индексе `i`. При этом все элементы правее этого индекса, будут на 1 сдвинуты вправо.

Посмотрите на пример:


```c++
void printVector(std::vector<int>& vec) {
    std::cout << "Vector size is " << vec.size() << "\nVector elements are: ";
    for (unsigned int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> vec(4, 1);
    printVector(vec);
    vec.insert(vec.begin(), 100);
    printVector(vec);
    vec.insert(vec.begin() + 2, 200);
    printVector(vec);
}
```
Вывод:
```
Vector size is 4
Vector elements are: 1 1 1 1 
Vector size is 5
Vector elements are: 100 1 1 1 1 
Vector size is 6
Vector elements are: 100 1 200 1 1 1 
```

Получается, в общем случае, строчка

```c++
vec.insert(vec.begin() + index, x);
```

вставит `x` на позицию `index`.

За сколько работает такая операция? Если размер вектора `size`, а вставляем мы на позицию `index`, то нужно сдвинуть вправо как минимум `size - index - 1` элементов, а порой еще дополнительно выделить память. При этом, если `index` == 0, то сдвинуть нужно целых `size` элементов, что для больших векторов будет стоить много. Поэтому, методом insert пользуются только либо для маленьких векторов, либо если вставка происходит ближе к концу вектора.

К слову, у `insert` есть и возвращаемое значение. Это пара (`bool`, `std::vector<T>::iterator`). Первое -- получилось ли вставить, а второе -- итератор на вставленный элемент. 

И последнее, это конечно же написать собственный `insert`. Он будет немного отличаться от того, что в `std::vector`, т.к. мы не будем использовать итераторы. Вместо итератора на индекс `i`, мы просто будем просить индекс `i`.

```c++
void Insert(unsigned int atIndex, const T& element) {
    if (size == capacity) {
        SetNewCapacity(2 * capacity);
    }
    for (unsigned int i = size; i >= atIndex + 1; --i) {
        buffer[i] = buffer[i - 1];
    }
    buffer[atIndex] = element;
    ++size;
}
```

Еще есть метод `erase(итератор)`, который удаляет элемент по итератору, реализация и время работы у него аналогичные.

```c++
void Erase(unsigned int atIndex) {
    for (unsigned int i = atIndex + 1; i < size; ++i) {
        buffer[i - 1] = buffer[i];
    }
    --size;
}
```

_* В нашем коде мы написали далеко не все, что написано в классическом std::vector. Например, так работать с памятью не принято, используют специальные обертки. Однако с точки зрения алгоритма вектора, мы целиком его воссоздали_