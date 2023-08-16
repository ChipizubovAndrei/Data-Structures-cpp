#include <iostream>

template <typename T>
class Node
{
public:
    T value;
    Node<T>* next;

    Node() : value(0), next(nullptr) {}

    explicit Node(T _value) : value(_value), next(nullptr) {}

    explicit Node(T _value, Node* _next) : value(_value), next(_next) {}
};

template <typename T>
class DoubleNode : public Node<T>
{
public:
    DoubleNode<T>* prev;
    DoubleNode<T>* next;

    DoubleNode(): Node<T>()
    {
        next = nullptr;
        prev = nullptr;
    }

    DoubleNode(T _value): Node<T>(_value)
    {
        next = nullptr;
        prev = nullptr;
    }

    DoubleNode(T _value, DoubleNode<T>* _prev, DoubleNode<T>* _next): Node<T>(_value)
    {
        prev = _prev;
        next = _next;
    }
};

/*
Дописать передачу классу в качетве параметра только значения !!
*/
template <typename T>
class SinglyLinkedList
{
public:

    SinglyLinkedList() : head(nullptr), tail(nullptr) {}

    SinglyLinkedList(T _hvalue)
    {
        Node<T>* temp = new Node<int>(_hvalue);
        head = temp;
        tail = temp;
        lenght = 1;
    }

    SinglyLinkedList(T _hvalue, T _tvalue)
    {
        Node<T>* temp_t = new Node<int>(_tvalue);
        Node<T>* temp_h = new Node<int>(_hvalue, temp_t);
        head = temp_h;
        tail = temp_t;
        lenght = 2;
    }

    SinglyLinkedList<T>(const SinglyLinkedList<T>& other)
    {
        head = new Node<T>(*other.head);
        Node<T>* tempThis = head;
        Node<T>* tempOther = other.head;
        while (tempOther->next) {
            tempThis->next = new Node<T>(*tempOther->next);
            tempThis = tempThis->next;
            tempOther = tempOther->next;
        }
        tail = new Node<T>(*tempOther);
        tail->next = nullptr;
    }

    SinglyLinkedList<T>& operator= (const SinglyLinkedList<T>& other)
    {
        head = new Node<T>(*other.head);
        Node<T>* tempThis = head;
        Node<T>* tempOther = other.head;
        while (tempOther->next) {
            tempThis->next = new Node<T>(*tempOther->next);
            tempThis = tempThis->next;
            tempOther = tempOther->next;
        }
        tail = new Node<T>(*tempOther);
        tail->next = nullptr;
        return *this;
    }

    virtual ~SinglyLinkedList()
    {
            if (!is_empty()) {
                Node<int>* temp = head;
                head = head->next;
                while(head) {
                    delete temp;
                    temp = head;
                    head = head->next;
            }
            head = nullptr;
            tail = nullptr;
        }
    }

    virtual void reverse()
    {
        if(head && head->next && head->next->next){
            Node<int>* left = head;
            Node<int>* right = head->next->next;
            head = head->next;
            left->next = nullptr;
            tail = left;
            while(right) {
                head->next = left;
                left = head;
                head = right;
                right = right->next;
            }
            head->next = left;
        }
    }

    // Метод вставляет значение в конец списка
    virtual void push_back(T _value)
    {
        if (!is_empty()) {
            Node<T>* temp = new Node<int>(_value);
            tail->next = temp;
            tail = temp;
        } else {
            Node<T>* temp = new Node<int>(_value);
            head = temp;
            tail = temp;
        }
        ++lenght;

    }

    virtual Node<T>* find(T _value) const
    {
        Node<T>* temp = head;
        while(temp && temp->value != _value) temp = temp->next;
        return (temp && temp->value == _value) ? temp : nullptr;
    }

    // Метод удаляет элемент списка по значению
    virtual void erase(T _value)
    {
        if (head->value == _value) {
            Node<int>* temp = head;
            head = head->next;
            delete temp;
        } else {
            Node<int>* temp = head;
            while (temp && temp->next->value != _value) temp = temp->next;
            if (temp && temp->next->value == _value) {
                Node<int>* rmNode = temp->next;
                if (rmNode == tail) {
                    tail = temp;
                }
                temp->next = rmNode->next;
                delete rmNode;
            }
        }

    }

    virtual bool is_empty() const 
    {
        return head == nullptr;
    }

    // Метод выводит содержимое списка
    virtual void print() const
    {
        if (is_empty()){
            std::cout << "List is empty" << std::endl;
        } else {
            Node<int>* temp = head;
            while (temp) {
                std::cout << temp->value << " ";
                temp = temp->next;
            }
            std::cout <<std::endl;
        }

    }

    virtual int size() const
    {
        return lenght;
    }

    // Метод проверяет, содержится ли искомый элемент в списке
    virtual bool is_contains(T _value) const
    {
        Node<int>* temp = head;
        if (!is_empty()) {
            while (temp && temp->value != _value) temp = temp->next;
            return (temp && temp->value == _value) ? true : false;
        } else {
            return false;
        }
        
    }

    virtual void clear()
    {
        if (!is_empty()){
            Node<int>* temp = head;
            head = head->next;
            while(head) {
                delete temp;
                temp = head;
                head = head->next;
            }
            head = nullptr;
            tail = nullptr;
        }

    }
private:
    Node<T>* head;
    Node<T>* tail;
protected:
    int lenght = 0;
};

template <typename T>
class DoubleLinkedList : public SinglyLinkedList<T>
{
public:
    DoubleLinkedList() : SinglyLinkedList<T>()
    {
        head = nullptr;
        tail = nullptr;
    }

    DoubleLinkedList(T _hvalue) : SinglyLinkedList<T>(_hvalue)
    {
        tail = nullptr;
        head = new DoubleNode<T>(_hvalue, tail);
    }

    DoubleLinkedList(T _hvalue, T _tvalue) : SinglyLinkedList<T>(_hvalue, _tvalue)
    {
        tail = new DoubleNode<T>(_tvalue, head, nullptr);
        head = new DoubleNode<T>(_hvalue, nullptr, tail);
        tail->prev = head;
        
    }

    void push_back(T _value)
    {
        if (SinglyLinkedList<T>::is_empty()){
            head = new DoubleNode<T> (_value, nullptr, tail);
            tail = nullptr;
        } else {
            DoubleNode<T>* temp = new DoubleNode<T>(_value, tail, nullptr);
            tail->next = temp;
            tail = temp;
        }
        SinglyLinkedList<T>::lenght++;
    }

    void print() const
    {
        if (SinglyLinkedList<T>::is_empty()){
            std::cout << "List is empty" << std::endl;
        } else {
            DoubleNode<T>* temp = head;
            while(temp) {
                std::cout << temp->value << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
    }

private:
    DoubleNode<T>* head;
    DoubleNode<T>* tail;
};
