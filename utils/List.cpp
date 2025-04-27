#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Iterator.cpp"
#include "Iterable.cpp"
/*
    La idea es crear una clase que implemente
    listas dinamicas y asi lograr una implementacion 
    bastante bien estructurada. 

    Se hace la implementacion con arreglos.
*/
template <typename U>
class List : public Iterable<U>
{
    private:
        static const int DEFAULT_INITIAL_SIZE = 10;
        static constexpr double DEFAULT_RESIZE = 1.7;

        U* array;
        int capacity;
        int length;


        void resize()
        {
            int NEW_CAPACITY = capacity*DEFAULT_RESIZE;
            U* help = array;
            array = new U[NEW_CAPACITY];

            for(int i = 0; i < length; i++)
                array[i] = help[i];

            delete[] help;
            capacity = NEW_CAPACITY;
        }
    public:
        List(int INITIAL_SIZE)
        {
            array = new U[INITIAL_SIZE];
            capacity = INITIAL_SIZE;
            length = 0;
        }

        List() : List(DEFAULT_INITIAL_SIZE) {}

        void add(const U& item, int index)
        {
            if(length < index || index < 0)
                return;
            
            if(length == capacity) 
                resize();

            for(int i = length-1; index < i; i--)
                array[i+1] = array[i];
            
            array[index] = item;
            length++;
        }

        // add last*
        void add(const U& item)
        {
            add(item, length);
        }

        U pop(int index)
        {
            if(length < index || index < 0 || length == 0)
                throw std::out_of_range("Index out of bounds");

            U item = array[index];
            for(int i = index; i < length - 1; i++)
                array[i] = array[i+1];

            length--;
            return item;
        }

        U pop()
        {
            return pop(0);
        }

        bool isEmpty()
        {
            return length == 0;
        }

        int size() const
        {
            return length;
        }

        U* getArray() const
        {
            return array;
        }

        void clear()
        {
            delete[] array;
            length = 0;
            array = new U[DEFAULT_INITIAL_SIZE];
            capacity = DEFAULT_INITIAL_SIZE;
        }

        U& operator[](int index) const
        {
            if (index < 0 || index >= length) {
                throw std::invalid_argument("Index out of the range");
            }

            return this->array[index];
        }

        friend std::ostream& operator<<(std::ostream& os, const List& list)
        {
            os << "[";
            for(int i = 0; i < list.length; i++)
            {
                os << list.array[i];
                if(i != list.length - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }
        
        Iterator<U> begin() const { return Iterator(array); }
        Iterator<U> end() const { return Iterator(array + length); }
};

#endif