//
// Created by Roman Gostilo on 29.03.2022.
//

#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <utility>

template <typename T>
class vector {
public:
    vector(): m_capacity(0),
              m_size(0),
              m_data(nullptr)
    {

    }


    vector(const vector& other): m_size(other.m_size),
                                 m_capacity(other.m_capacity),
                                 m_data(m_capacity == 0 ? nullptr : new T[other.m_capacity])
    {
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i] = other.m_data[i];
        }
    }

    // move constructor
    vector(vector&& other): m_size(other.m_size),
                            m_capacity(other.m_capacity),
                            m_data(other.m_data)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    vector(std::size_t size, const T& value) : m_capacity(size), m_size(size), m_data((m_capacity == 0) ? nullptr : new T(m_capacity)){
        for (std::size_t i = 0; i < size; i++){
            m_data[i] = value;
        }
    }

    vector(std::initializer_list<T> list) : m_capacity(list.size()),
                                            m_size(list.size()),
                                            m_data(list.size() == 0 ? nullptr : new T[list.size()])
    {
        std::size_t i = 0;
        for (const T& elem : list){
            m_data[i++] = elem;
        }
    }

    ~vector(){
        delete[] m_data;
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    vector& operator=(const vector& other){
        if (*this != other){
            delete[] m_data;
            m_data = nullptr;
            m_capacity = other.m_capacity;
            m_size = other.m_size;
            m_data = other.m_capacity == 0 ? nullptr : new T[other.m_capacity];
            for (std::size_t i = 0; i < other.m_size; i++){
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }

    // move assigngment
    vector& operator=(vector&& other){
        if (*this != other){
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            delete[] m_data;
            m_data = other.m_data;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    T& operator[](std::size_t index) {
        assert(index < m_size);
        return m_data[index];
    }

    const T& operator[](std::size_t index) const{
        assert(index < m_size);
        return m_data[index];

    }

    void clear(){
        delete[] m_data;
        m_size = 0;

        m_data = new T[m_capacity];
    }

    void push_back(const T& value) {
        if (m_size == m_capacity) {
            m_capacity = m_capacity == 0 ? 1 : 2 * m_capacity;
            T* new_data = new T[m_capacity];
            for (std::size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
        }
        m_data[m_size++] = value;
    }

    // push_back(rvalue ref)
    void push_back(T&& value){
        if (m_size == m_capacity) {
            m_capacity = m_capacity == 0 ? 1 : 2 * m_capacity;
            T* new_data = new T[m_capacity];
            for (std::size_t i = 0; i < m_size; ++i) {
                new_data[i] = m_data[i];
            }
            delete[] m_data;
            m_data = new_data;
        }
        m_data[m_size++] = std::move(value);
    }

    void pop_back(){
        m_size = m_size > 0 ? m_size - 1 : 0;
    }

    void resize(std::size_t size) {
        if (size > m_size) {
            if (size > m_capacity) {
                m_capacity = size;
                T* new_data = new T[m_capacity];
                for (std::size_t i = 0; i < m_size; ++i) {
                    new_data[i] = m_data[i];
                }
                delete[] m_data;
                m_data = new_data;
            }
        }
        m_size = size;
    }

    void reserve(std::size_t new_capacity){
        if (new_capacity > m_size){
            T* new_data = new T[new_capacity];
            for (std::size_t i = 0; i < m_size; i++){
                new_data[i] = m_data[i];
            }
            m_capacity = new_capacity;
            delete[] m_data;
            m_data = new_data;
        }
    }

    std::size_t size() const {
        return m_size;
    }

private:
    std::size_t m_capacity;
    std::size_t m_size;
    T* m_data;
};