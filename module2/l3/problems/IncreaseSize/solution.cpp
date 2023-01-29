template<typename T>
void IncreaseSize(T*& buffer, unsigned int oldSize, unsigned int newSize) {
    T* newBuffer = new T[newSize];
    for (unsigned int i = 0; i < oldSize; ++i) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}