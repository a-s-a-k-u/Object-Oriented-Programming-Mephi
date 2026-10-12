#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <memory>
#include <iterator>

template<typename Type>
class Vector {
protected:
    Type* value;
    size_t size;
    size_t capacity;
    [[nodiscard]] bool Capacity_Okay() const noexcept {
        if (size == capacity){return true;}
        return false;
    }
public:
    class Iterator;

    explicit Vector() noexcept{
        size = 0;
        capacity = 2;
        value = new Type[capacity];
    }

    Vector(const Vector& clas) noexcept{
        size = clas.size;
        capacity = clas.capacity;
        value = new Type[capacity];
        for (size_t i = 0; i < size; i++) value[i] = clas.value[i];
    }


    Vector(Vector&& clas) noexcept {
        size = clas.size;
        capacity = clas.capacity;
        value = clas.value;
        clas.value = nullptr;
        clas.size = 0;
        clas.capacity = 0;
    }

    Vector& operator=(const Vector& clas) noexcept{
        if (&clas == this) return *this;
        delete[] value;
        this->size = clas.size;
        this->capacity = clas.capacity;
        value = new Type[capacity];
        for (size_t i = 0; i < size; i++) {
            this->value[i] = clas.value[i];
        }
        return *this;
    }

    Vector& operator= (Vector&& clas) noexcept{
        if (&clas == this) return *this;
        delete[] value;
        size = clas.size;
        capacity = clas.capacity;
        value = clas.value;
        clas.value = nullptr;
        clas.size = 0;
        clas.capacity = 0;
        return *this;
    }

    void push_back(Type&& a) {
        if (capacity == 0) {
            capacity++;
            value = new Type[capacity];
        }
        if (Capacity_Okay()) {
            capacity *= 2;
            Type* new_value = new Type[capacity];
            if (std::is_trivially_copyable_v<Type>) {
                std::memcpy(new_value, value, size * sizeof(Type));
            }
            else {
                for (size_t i = 0; i < size; i++) {
                    new_value[i] = std::move_if_noexcept(value[i]);
                }
            }
            delete[] value;
            value = new_value;
        }
        value[size] = std::move(a);
        size++;
    }

    void push_back(const Type& a) {
        if (capacity == 0) {
            capacity++;
            value = new Type[capacity];
        }
        if (Capacity_Okay()) {
            capacity *= 2;
            Type* new_value = new Type[capacity];
            if (std::is_trivially_copyable_v<Type>) {
                std::memcpy(new_value, value, size * sizeof(Type));
            }
            else {
                for (size_t i = 0; i < size; i++) {
                    new_value[i] = std::move_if_noexcept(value[i]);
                }
            }
            delete[] value;
            value = new_value;
        }
        value[size] = a;
        size++;
    }

    void pop() {
        if (empty()) return;
        size--;
    }

    bool empty() const {
        return size == 0;
    }

    size_t GetSize() const { return size; }
    size_t GetCapacity() const { return capacity; }

    Type& operator[] (size_t index) { return value[index]; }
    const Type& operator[] (size_t index) const { return value[index]; }

    Iterator begin() { return Iterator(value); }
    Iterator end() { return Iterator(value + size); }

    const Iterator begin() const { return Iterator(value); }
    const Iterator end() const { return Iterator(value + size); }

    const Iterator cbegin() const { return Iterator(value); }
    const Iterator cend() const { return Iterator(value + size); }

    ~Vector() {
        delete[] value;
    }

    class Iterator {
        Type* current;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = Type*;
        using reference = Type&;

        /**
         *ЯВНЫЙ ПУБЛИЧНЫЙ ДЕСТРУКТОР
         */
        ~Iterator() = default;  // <-- ЭТО ВАЖНО!

        /**
         *Конструктор по умолчанию
         */
        Iterator() noexcept : current(nullptr) {}

        /**
         * Конструктор с парамметром - иттератором
         * @param first
         */
        explicit Iterator(Type* first) noexcept : current(first){}

        /**
         *Правило пяти - ВСЕ public
         */
        Iterator(const Iterator&) = default;
        Iterator(Iterator&&) = default;
        Iterator& operator=(const Iterator&) = default;
        Iterator& operator=(Iterator&&) = default;

        /**
         * Используем difference_type вместо int
         */
        Iterator operator+ (std::ptrdiff_t value) const noexcept {
            return Iterator(current + value);
        }

        Iterator operator- (std::ptrdiff_t value) const noexcept {
            return Iterator(current - value);
        }

        /**
         * Составные присваивания
         */
        Iterator& operator+= (std::ptrdiff_t n) noexcept {
            current += n;
            return *this;
        }

        Iterator& operator-= (std::ptrdiff_t n) noexcept {
            current -= n;
            return *this;
        }

        /**
         *Разность между итераторами
         */
        std::ptrdiff_t operator-(const Iterator& sec) const noexcept {
            return current - sec.current;
        }

        /**
         *Индексация
         */
        Type& operator[] (std::ptrdiff_t index) const noexcept {
            return *(current + index);
        }

        /**
         *Инкремент/декремент
         */
        Iterator operator++ (int) noexcept {
            Iterator temp = *this;
            ++current;
            return temp;
        }

        Iterator operator-- (int) noexcept {
            Iterator temp = *this;
            --current;
            return temp;
        }

        Iterator& operator++ () noexcept {
            ++current;
            return *this;
        }

        Iterator& operator-- () noexcept {
            --current;
            return *this;
        }

        /**
         * Операторы сравнения
         */
        bool operator< (const Iterator& other) const noexcept {
            return current < other.current;
        }

        bool operator> (const Iterator& other) const noexcept {
            return current > other.current;
        }

        bool operator<= (const Iterator& other) const noexcept {
            return current <= other.current;
        }

        bool operator>= (const Iterator& other) const noexcept {
            return current >= other.current;
        }

        bool operator!=(const Iterator& other) const noexcept {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const noexcept {
            return current == other.current;
        }

        /**
         * Разыменование
         */
        Type& operator*() const noexcept {
            return (*current);
        }

        Type* operator->() const noexcept {
            return current;
        }

        /**
         *Комуникативность для собственно проверки через static_assert
         * @param n
         * @param it
         * @return
         */
        friend Iterator operator+ (std::ptrdiff_t n, const Iterator& it) noexcept {
            return Iterator(it.current + n);
        }


    };

    static_assert(std::random_access_iterator<Iterator>);
};

#endif // VECTOR_H