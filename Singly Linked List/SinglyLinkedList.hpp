#pragma once

#include <iostream>
#include <stdexcept>
#include <ctime>
#include <string>

#define __GENERATE__ALL__SYMBOLS__

template <typename T>
class List
{
private:
    struct Node
    {
        // Points on next link of list
        Node *pNext;

        // Variable to store data
        T m_data;

        // Different constructors
        explicit Node() : pNext(nullptr) {}
        explicit Node(const T &__data) : m_data(__data) {}
        explicit Node(Node *__next = nullptr) : pNext(__next) {}
        explicit Node(Node *__next = nullptr, T __data = T()) : pNext(__next), m_data(__data) {}

        // Virtual default destructor
        virtual ~Node() = default;
    };

    // Points on the head of list (on the 1st element)
    Node *pHead;

    // Variable to store size of list
    size_t m_size;

protected:
    // Copying data from object to current object
    inline void copy(const List<T> &__list)
    {
        pHead = __list->pHead;
        m_size = __list->m_size;
    }

    // Zeroing out data from passed object
    inline void clear(const List<T> &__list)
    {
        // Deallocating memory from head of the list
        delete __list->pHead;
        // Zeroing out pointer on head of the list
        __list->pHead = nullptr;
        // Zeroing out size of lits
        m_size = 0UL;
    }

    // Returns random string
    // define __GENERATE__ALL__SYMBOLS__ if you want to generate all symbols
    // define __GENERATE__ONLY__DIGITS__ if you want to generate only digits
    std::string generate_rdm_str(const size_t &lenght) const
    {
        /* Hint: You must declare at the top following line:
        #define __GENERATE__ALL__SYMBOLS__ for generate string consisting of all symbols
        or
        #define __GENERATE__ONLY__DIGITS__ for generate string consisting of only digits */

#ifdef __GENERATE__ALL__SYMBOLS__
        static constexpr char symbols[]{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz`1234567890-=~!@#$%^&*()_+[]{}\\|/\'\",.<>:; "};
#endif

#ifdef __GENERATE__ONLY__DIGITS__
        static constexpr char onlyDigits[]{"1234567890"};
#endif

        // Declaring variable for store random string inside
        std::string rndmString{};

        // Generating random string
        for (size_t iter = 0; iter < lenght; iter++)
        {
#ifdef __GENERATE__ALL__SYMBOLS__
            rndmString += symbols[rand() % (sizeof(symbols) - 1)];
#endif

#ifdef __GENERATE__ONLY__DIGITS__
            rndmString += onlyDigits[rand() % (sizeof(onlyDigits) - 1)];

            // To avoid numbers like 03, 045, 00 etc.
            // At first, convert string to int
            // then clear string
            // then convert int to string
            int rndmNum = std::stoi(rndmString);
            rndmString.clear();
            rndmString = std::to_string(rndmNum);
#endif
        }

        return rndmString;
    }

public:
    // Zero-argument, default ctor
    explicit List<T>() : pHead(nullptr), m_size(0UL) {}

    // Copy constructor
    explicit List<T>(const List<T> &__list) { copy(__list); }

    // Move constructor
    explicit List<T>(List<T> &&__list)
    {
        copy(__list);
        clear(__list);
    }

    // Assignment operator
    List<T> &operator=(const List<T> &__list)
    {
        // Checking self-assignment
        if (this == &__list)
            return *this;

        // Copying data from passed object to current object
        copy(__list);

        // Returning current object
        return *this;
    }

    // Move assignment operator
    List<T> &operator=(List<T> &&__list) noexcept
    {
        // Checking self-assignment
        if (this == &__list)
            return *this;

        // Zeroing out current object
        clear(this);
        // Copying data from passed object to current object
        copy(__list);
        // Zeroing out passed object
        clear(__list);

        // Returning current object
        return *this;
    }

    // Virtual default destructor
    virtual ~List<T>() { clear(); }

    // Returns size of list
    inline size_t size() const { return m_size; }

    // Adding element to end of the singly linked list
    void push_back(const T &__data);

    // Overloading operator '[]'
    // Returns data from 'list[__index]' element
    // If array out of bounds -> throw exception
    T &operator[](const size_t &__index) const;

    // Returns list with random elements. Passes number of elements as 'size_t', minimal number and maximal number as integers
    // Filling with integers
    List<T> &fill_random(const size_t &__elements, const int &__from, const int &__to);

    // Returns list with random elements. Passes number of elements as 'size_t', minimal number and maximal number as float numbers
    // Filling with float numbers
    List<T> &fill_random(const size_t &__elements, const float &__from, const float &__to);

    // Returns list with random elements. Passes number of elements as 'size_t', minimal number and maximal number as float numbers
    // Filling with double numbers
    List<T> &fill_random(const size_t &__elements, const double &__from, const double &__to);

    // Returns list with random elements. Passes number of elements as 'size_t', length of string
    // Filling with string
    List<T> &fill_random(const size_t &__elements, const size_t &__length);

    // Removes first element of list
    void pop_front();

    // Removes all links in current list
    void clear();

    // Adding element to front of list
    void push_front(const T &__data);

    // Adding an element to the list at the specified index
    void insert(const T &__data, const size_t &__index);

    // Removing element in specified index of list
    void remove_at(const size_t &__index);

    // Removing last link of list
    void pop_back();

    // Prints list to terminal
    // If parameter is false -> method will print just elemens
    // If parameter is true -> method will print by elements according following template: list[index] = element
    void show(bool isBeautyPrint = false) const;
};

template <typename T>
void List<T>::push_back(const T &__data)
{
    // If 1st element of list is empty
    if (pHead == nullptr)
    {
        // Calling constructor of 'Node' struct
        pHead = new Node(__data);
    }
    // Otherwise 1st element is not empty
    else
    {
        // Initializing current pointer on object with head of list
        Node *pCurr{pHead};

        // Until we find last element which is points to null
        while (pCurr->pNext != nullptr)
        {
            // Assigning next link to current link of list
            pCurr = pCurr->pNext;
        }
        // Writing data to next link of list
        pCurr->pNext = new Node(__data);
    }

    // Incremeting size when we add element
    m_size++;
}

template <typename T>
T &List<T>::operator[](const size_t &__index) const
{
    // Initializing couter for iterate in list
    size_t counter{};

    // Initializing current pointer on object with head of list
    Node *pCurr{pHead};

    // Until we find last element which is points to null
    while (pCurr != nullptr)
    {
        // If we found desired element -> return it's data
        if (counter == __index)
        {
            return pCurr->m_data;
        }
        // Otherwise -> move to next link of list
        pCurr = pCurr->pNext;
        // And incrementing counter
        counter++;
    }
    // Throwing exception about out of range
    std::cout << "Index out of list range. " << std::endl;
    throw new std::out_of_range("");
}

template <typename T>
List<T> &List<T>::fill_random(const size_t &__elements, const int &__from, const int &__to)
{
    srand(time(nullptr));
    for (size_t index = 0UL; index < __elements; index++)
    {
        push_back(rand() % __to + __from);
    }
    return *this;
}

template <typename T>
List<T> &List<T>::fill_random(const size_t &__elements, const float &__from, const float &__to)
{
    srand(time(nullptr));
    for (size_t index = 0UL; index < __elements; index++)
    {
        push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (__to - __from)));
    }
    return *this;
}

template <typename T>
List<T> &List<T>::fill_random(const size_t &__elements, const double &__from, const double &__to)
{
    srand(time(nullptr));
    for (size_t index = 0UL; index < __elements; index++)
    {
        push_back(static_cast<double>(rand()) / static_cast<double>(RAND_MAX / (__to - __from)));
    }
    return *this;
}

template <typename T>
List<T> &List<T>::fill_random(const size_t &__elements, const size_t &__length)
{
    srand(time(nullptr));
    for (size_t index = 0UL; index < __elements; index++)
    {
        push_back(generate_rdm_str(__length));
    }
    return *this;
}

template <typename T>
void List<T>::show(bool isBeautyPrint) const
{
    // If list is empty -> print that list is empty
    if (pHead == nullptr)
        std::cout << "List is empty " << std::endl;
    // Otherwise:
    else
    {
        // Initializing variable to store index of certain link of the list
        size_t index{};

        // Initializing pointer to current link of list
        Node *pCurr{pHead};

        // Untill current pointer not equals to null pointer -> printing data from this pointer
        while (pCurr != nullptr)
        {
            if (isBeautyPrint == true)
                std::cout << "list[" << index << "] = " << pCurr->m_data << std::endl;
            else
                std::cout << pCurr->m_data << std::endl;

            // Assigning next pointer to current pointer to switch to another link of list
            pCurr = pCurr->pNext;

            // Incrementing index of link of the list
            index++;
        }
    }
}

template <typename T>
void List<T>::pop_front()
{
    // Initializing variable to store reference on first link of list
    Node *temp_head{pHead};

    // Assigning next element to head element, then we can delete head link
    pHead = pHead->pNext;

    // Deallocating memory of temporaly head of list
    delete temp_head;

    // Zeroing out this temporaly pointer
    temp_head = nullptr;

    // Decrementing size of list, because we are removing link of list
    m_size--;
}

template <typename T>
void List<T>::clear()
{
    // Until size of list not null
    // When 'm_size' = 0 -> means false
    while (m_size)
    {
        // Removing elements
        pop_front();
    }
}

template <typename T>
void List<T>::push_front(const T &__data)
{
    // Calling constructor of class 'Node' to initialize new head element
    pHead = new Node(pHead, __data);

    // Incrementing size of list
    m_size++;
}

template <typename T>
void List<T>::insert(const T &__data, const size_t &__index)
{
    // If specified index is 0 -> pushing data to head of the list
    if (__index == 0UL)
    {
        push_front(__data);
    }
    // Otherwise -> find specified index -> pushing element to previous
    else
    {
        // Initializing previous pointer as head of the list
        Node *pPrev{pHead};

        // Iteration by indeces in list
        for (size_t index = 0UL; index < __index - 1UL; index++)
        {
            // Assigning next pointer of to previous
            pPrev = pPrev->pNext;
        }

        // Calling constructor of 'Node'
        // Assigning temporaly pointer to next link of list (from previous)
        pPrev->pNext = new Node(pPrev->pNext, __data);

        // Incrementing size of list
        m_size++;
    }
}

template <typename T>
void List<T>::remove_at(const size_t &__index)
{
    // If specified index is 0 -> deleting head of the list
    if (__index == 0UL)
    {
        pop_front();
    }
    // Otherwise -> find specified index -> deleting desired element
    else
    {
        // Initializing previous pointer as head of the list
        Node *pPrev{pHead};

        // Iteration by indeces in list
        for (size_t index = 0UL; index < __index - 1UL; index++)
        {
            // Assigning next pointer of to previous
            pPrev = pPrev->pNext;
        }

        // Initializing pointer at element which we want to delete, which will points on next link of list
        Node *pDel = pPrev->pNext;

        // Assigning
        pPrev->pNext = pDel->pNext;

        // Deallocating memory from pointer at desired element to delete
        delete pDel;

        // Zeroing out this pointer
        pDel = nullptr;

        // Decrementing size of list
        m_size--;
    }
}

template <typename T>
void List<T>::pop_back()
{
    // Deleting last link of list
    remove_at(m_size - 1);
}
