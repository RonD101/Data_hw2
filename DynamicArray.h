#ifndef HW2_DYNAMIC_ARRAY_H
#define HW2_DYNAMIC_ARRAY_H
#define EXPAND_FACTOR 2

template<class T>
class DynamicArray {
    T *data;
    int length;
    int current;
public:
    class BadAccess;
    explicit DynamicArray(int size = 2);
    DynamicArray(const DynamicArray<T> &a);
    ~DynamicArray();
    DynamicArray &operator=(const DynamicArray<T> &a);

    int quantity() const { return current; }
    int size() const;

    T &operator[](int index);
    const T &operator[](int index) const;

    void push_back(T value);
    void expand();
    void shrink();
    void pop();

};

template<class T>
void DynamicArray<T>::pop() {
    if(current <= 0)
        return;
    current -= 1;
    if(current < size()/(2 * EXPAND_FACTOR))
        shrink();
}

template<class T>
void DynamicArray<T>::shrink() {
    int new_size = size() / EXPAND_FACTOR;
    T* new_data = new T[new_size];
    for (int i = 0; i < new_size; ++i)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    length = new_size;
}

template<class T>
void DynamicArray<T>::expand() {
    int new_size = EXPAND_FACTOR* size();
    T* new_data = new T[new_size];
    for (int i = 0; i < size(); ++i)
        new_data[i] = data[i];
    delete[] data;
    data = new_data;
    length = new_size;
}

template<class T>
void DynamicArray<T>::push_back(T value){
    if(size() == current)
        expand();
    data[current] = value;
    current++;
}

template<class T>
DynamicArray<T>::DynamicArray(int size) {
    data = new T[size];
    length = size;
    current = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &a) {
    data = new T[a.size()];
    length = a.size();
    current = a.current;
    for (int i = 0; i < a.size(); ++i)
            data[i] = a[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T> &a) {
    if (this == &a)
        return *this;
    T *temp_array = new T[a.size()];
    delete[] data;
    current = a.current;
    for (int i = 0; i < a.size(); ++i) {
        try {
            temp_array[i] = a[i];
        }
        catch (const std::exception &e) {
            delete[] temp_array;
            throw e;
        }
    }
    data = temp_array;
    length = a.size();
    return *this;
}

template<class T>
int DynamicArray<T>::size() const {
    return length;
}

template<class T>
T &DynamicArray<T>::operator[](int index) {
    if (index < 0 || index >= this->size())
        throw DynamicArray::BadAccess();
    return data[index];
}

template<class T>
const T &DynamicArray<T>::operator[](int index) const {
    if (index < 0 || index >= this->size())
        throw DynamicArray::BadAccess();
    return data[index];
}

template <class T>
class DynamicArray<T>::BadAccess : public std::exception {
        public:
            const char* what() const noexcept override {
                return "Bad Access";
            }
    };

#endif //HW2_DYNAMIC_ARRAY_H