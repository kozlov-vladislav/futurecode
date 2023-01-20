struct BagStruct {
    unsigned capacity;
    unsigned size = 0;
    BagStruct(unsigned int);
    void Mint(unsigned int);
    unsigned int Balance();
    void Transfer(BagStruct&);
    void Transfer(BagStruct*);
};

BagStruct::BagStruct(unsigned int capacity) : capacity(capacity) {}

void BagStruct::Mint(unsigned int number) {
    size += number;
    size = size > capacity ? capacity : size;
}

unsigned int BagStruct::Balance() {
    return size;
}

void BagStruct::Transfer(BagStruct* destination) {
    Transfer(*destination);
}

void BagStruct::Transfer(BagStruct& destination) {
    unsigned int oldBal = destination.Balance();
    destination.Mint(size);
    unsigned int delta = destination.Balance() - oldBal;
    size -= delta;
}