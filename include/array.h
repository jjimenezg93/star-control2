#ifndef UGINE_ARRAY_H
#define UGINE_ARRAY_H

#include "types.h"

#define CAPACITY_INC 128

template <typename T>
class Array {
public:
    Array(uint32 initialCapacity = 0);
    Array(const Array<T>& other);
    ~Array() { delete [] buffer; }

    Array<T>& operator=(const Array<T>& other);
    T& operator[](uint32 pos) { return buffer[pos]; }
    const T& operator[](uint32 pos) const { return buffer[pos]; }

    void Reserve(uint32 capacity);
    uint32 Size() const { return size; }
    void Add(const T& elem);
    void Set(uint32 index, const T& elem) { buffer[index] = elem; }
    T& First() { return buffer[0]; }
    const T& First() const { return buffer[0]; }
    T& Last() { return buffer[size-1]; }
    const T& Last() const { return buffer[size-1]; }
    void RemoveLast() { RemoveAt(Size()-1); }
    void RemoveAt(int index);
    void Remove(T& elem);
    void RemoveEach(T& elem);
    void Clear();
    void Sort(bool (*compareFunc)(T&, T&));
private:
    T* buffer;
    uint32 size;
    uint32 capacity;
};

template <typename T>
Array<T>::Array(uint32 initialCapacity) : buffer(0), size(0), capacity(0) {
    if ( initialCapacity > 0  &&  initialCapacity < CAPACITY_INC ) initialCapacity = CAPACITY_INC;
    //buffer = new T[initialCapacity];
    Reserve(initialCapacity);
    //capacity = initialCapacity;
}

template <typename T>
Array<T>::Array(const Array<T>& other) : buffer(0), size(0), capacity(0) {
    buffer = new T[other.capacity];
    for ( uint32 i = 0; i < other.size; i++ ) buffer[i] = other.buffer[i];
    size = other.size;
    capacity = other.capacity;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    T* oldBuffer = buffer;
    buffer = new T[other.capacity];
    for ( uint32 i = 0; i < other.size; i++ ) buffer[i] = other.buffer[i];
    size = other.size;
    capacity = other.capacity;
    if ( oldBuffer ) delete [] oldBuffer;
    return *this;
}

template <typename T>
void Array<T>::Reserve(uint32 cap) {
    if ( cap > capacity ) {
        capacity = cap;
        T* oldBuffer = buffer;
        buffer = new T[capacity];
        for ( uint32 i = 0; i < size; i++ ) buffer[i] = oldBuffer[i];
        if ( oldBuffer ) delete [] oldBuffer;
    }
}

template <typename T>
void Array<T>::Add(const T& elem) {
    if ( capacity == size ) Reserve(capacity + CAPACITY_INC);
    buffer[size++] = elem;
}

template <typename T>
void Array<T>::RemoveAt(int index) {
    for ( uint32 i = index+1; i < size; i++ ) buffer[i-1] = buffer[i];
    size--;
}

template <typename T>
void Array<T>::Remove(T& elem) {
    for ( uint32 i = 0; i < size; i++ ) {
        if ( buffer[i] == elem ) {
            RemoveAt(i);
            break;
        }
    }
}

template <typename T>
void Array<T>::RemoveEach(T& elem) {
    int i = 0;
    while ( i < size ) {
        if ( buffer[i] == elem ) {
            RemoveAt(i);
        } else {
            i++;
        }
    }
}

template <typename T>
void Array<T>::Clear() {
    delete [] buffer;
    buffer = new T[CAPACITY_INC];
    size = 0;
    capacity = CAPACITY_INC;
}

template <typename T>
void Array<T>::Sort(bool (*compareFunc)(T&, T&)) {
    // An array of zero or one elements is already sorted
    if ( Size() <= 1 ) return;

    // Select pivot
    uint32 pivotIndex = Size()/2;
    T pivot = buffer[pivotIndex];

    // Create less and greater arrays
    Array<T> less, greater;
    for ( uint32 i = 0; i < Size(); i++ ) {
        T node = buffer[i];
        if ( i != pivotIndex ) {
            if ( compareFunc(node, pivot) ) less.Add(node);
            else greater.Add(node);
        }
    }

    // Apply quicksort to both arrays
    less.Sort(compareFunc);
    greater.Sort(compareFunc);

    // Clear array and add values in order
    Clear();
    for ( uint32 i = 0; i < less.Size(); i++ ) Add(less[i]);
    Add(pivot);
    for ( uint32 i = 0; i < greater.Size(); i++ ) Add(greater[i]);
}

#undef CAPACITY_INC

#endif // UGINE_ARRAY_H
