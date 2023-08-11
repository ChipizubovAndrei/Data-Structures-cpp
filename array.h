#include <iostream>

namespace StaticArray
{
    template <typename T, std::size_t N>
    void insert(T(&array)[N], T value, int id)
    {
        if (id < N && id > 0){
            T* arr_temp = array + id;
            if (N - id - 1 > 0){
                for (int i = N - id - 1; i >= 0; --i){
                    arr_temp[i+1] = arr_temp[i];
                }
            }
            array[id] = value;
        }

    }

    template <typename T, std::size_t N>
    void remove(T(&array)[N], int id)
    {
        if (id < N && id > 0){
            T* arr_temp = array + id;
            for (int i = 0; i < N - id - 1; ++i){
                arr_temp[i] = arr_temp[i+1];
            }
            array[N-1] = (T)0;
        }

    }

    template <typename T, std::size_t N>
    void print(T(&array)[N])
    {
        for (int i = 0; i < N; ++i){
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
class DynamicArray
{
private:
    // размер массива (количество элементов в массиве, доступных пользователю)
    int m_size;
    // "вместимость" массива, то есть размер выделенной памяти для хранения элементов.
    int m_capacity;
    // указатель на область памяти, где хранятся сами элементы массива.
    T* m_data;
public:
    // Конструктор по умолчанию
    DynamicArray()
    {
        m_size = 0;
        m_capacity = 0;
        m_data = NULL;
    }

    // Конструктор с заданным размером
    explicit DynamicArray(int capacity):
        m_size(0), m_capacity(capacity)
    {
        if (m_capacity != 0) {
            m_data = new T [m_capacity]{};
        } else {
            m_data = 0;
        }
        
    }

    // Конструктор копирования
    DynamicArray(const DynamicArray<T>& other)
    {
        m_size = other.m_size;
        m_capacity = m_size;
        m_data = NULL;
        if (m_size != 0){
            m_data = new T[m_size]{};
        } else {
            m_data = 0;
        }
        for (int i = 0; i < m_size; ++i){
            m_data[i] = other.m_data[i];
        }
    }
    // Деструктор
    ~DynamicArray()
    {
        delete [] m_data;
    }

    // Оператор копирования
    DynamicArray& operator=(DynamicArray const& other) {
        if (m_size != 0) {
            delete [] m_data;
        }
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        if (m_size != 0) {
            m_data = new T [m_size];
        } else {
            m_data = 0;
        }
        for (int i = 0; i < m_size; ++i){
            m_data[i] = other.m_data[i];
        }
        return *this;
    }

    T & operator[](int id) {
        return m_data[id];
    }

    int size() const
    {
        return m_size;
    }

    // Удалить элеменит по индексу
    void erase(int id)
    {
        if (id < m_size) {
            for (int i = id; i < m_size - 1; ++i) {
                m_data[i] = m_data[i+1];
            }
            m_data[m_size-1] = 0;
            --m_size;
        }
    }

    // Вставить элемент в конец списка
    void push_back(T _value)
    {
        if (m_size + 1 > m_capacity && m_capacity != 0) {
            T* temp = m_data;
            m_data = new T [m_capacity*2]{};
            for (int i = 0; i < m_size; ++i) {
                m_data[i] = temp[i];
            }
            delete [] temp;
            m_capacity = m_capacity * 2;
        }
        m_data[m_size] = _value;
        ++m_size;
    }

    // Вывести содержимое m_data
    void print() const
    {
        if (m_size != 0){
            for (int i = 0; i < m_size; ++i) {
                std::cout << m_data[i] << " ";
            }
            std::cout << std::endl;
        } else {
            std::cout << "Array is empty" << std::endl;
        }

    }

    // Вставить элемент в массив
    void insert(T _value, int id)
    {
        if (id < m_capacity) {
            if (id == m_size) {
                m_data[id] = _value;
                ++m_size;
            } else if (id < m_size) {
                for (int i = m_size; i > id; --i) {
                    m_data[i] = m_data[i - 1];
                }
                m_data[id] = _value;
                ++m_size;
            }
            
        }
    }

    // Очистить очистить содержимое массива
    void clear()
    {
        delete [] m_data;
        m_data = 0;
        m_size = 0;
        m_capacity = 0;
    }

};