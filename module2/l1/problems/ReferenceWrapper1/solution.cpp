struct ReferenceWrapper1 {
    int& ref;
    ReferenceWrapper1(int&);
    int& Get();
};

ReferenceWrapper1::ReferenceWrapper1(int& x) : ref(x) {}

int& ReferenceWrapper1::Get() {
    return ref;
};


// 2

/*

struct ReferenceWrapper1 {
    int* ref;
    ReferenceWrapper1(int&);
    int& Get();
};

ReferenceWrapper1::ReferenceWrapper1(int& x) : ref(&x) {}

int& ReferenceWrapper1::Get() {
    return *ref;
};


*/