#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "block.h"

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    Node(){ 
        this->next = nullptr;
    }

    Node(T value){
        this->data = value;
        this->next = nullptr;
    }

    void killSelf(){
        if(next!=nullptr) next->killSelf();
        delete this;
    }    
};

// TODO: Implement all methods
template <typename T>
class ForwardList
{
private:
    Node<T> *head;
    int nodes;

public:
    ForwardList()
    {
        nodes = 0;
    }

    ~ForwardList()
    {
        head->killSelf();
    }
    T front();
    T back();
    void push_front(T);
    void push_back(T);
    T pop_front();
    T pop_back();
   // T insert(T, int);
   // bool remove(int);
    T &operator[](int);
   bool is_empty();
    int size();
   // void clear();
    //void sort();
    //bool is_sorted();
   // void reverse();
    //std::string name();
};

//=========================================

template <typename T>
T ForwardList<T>::front() //✅
{                         // o1
    if (is_empty())
        throw("lista vacia");
    else
        return head->data;
};

template <typename T>
T ForwardList<T>::back() //✅
{                        // on
    if (is_empty())
        throw("lista vacia");
    else if (nodes == 1)
        return front();
    else
    {
        Node<T> *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;

        return temp->data;
    }
};

template <typename T>
void ForwardList<T>::push_front(T data) //✅
{
    if (is_empty())
    {
        head = new Node<T>(data);
        nodes = 1;
    }
    else
    {
        Node<T> *new_node = new Node<T>(data);
        new_node->next = head;
        head = new_node;
        nodes++;
    }
};

template <typename T>
void ForwardList<T>::push_back(T data) //
{
    if (is_empty())
    {
        head = new Node<T>(data);
        nodes = 1;
    }
    else
    {
        Node<T> *new_node = new Node<T>(data);
        
        if (nodes == 1)
            head->next = new_node;
        else
        {
            Node<T> *temp = head;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = new_node;
        }
        nodes++;
    }
};

template <typename T>
T ForwardList<T>::pop_front()
{
    if (is_empty())
        throw("lista vacia");
    else
    {
        T dato = head->data;
        if (nodes == 1)
        {
            Node<T> *temp = head;
            head = new Node<T>;
            delete temp;
            nodes = 0;
        }
        else
        {
            Node<T> *temp = head;
            head = head->next;
            temp->next = nullptr;
            delete temp;
            nodes--;
        }
        return dato;
    }
};

template <typename T>
T ForwardList<T>::pop_back()
{
    if (is_empty())
        throw("sin definir");
    else
    {
        T dato;
        if (nodes == 1)
        {
            dato = head->data;
            Node<T> *temp = head;
            head = new Node<T>;
            temp->killSelf();
            nodes = 0;
        }
        else
        {
            Node<T> *temp = head;
            while (temp->next->next != nullptr)
                temp = temp->next;
            dato = temp->next->data;
            temp->next->killSelf();
            temp->next = nullptr;
            nodes--;
        }
        return dato;
    }
};

template <typename T>
bool ForwardList<T>::is_empty()
{
    return nodes == 0;
};

template <typename T>
T &ForwardList<T>::operator[](int pos)
{
    Node<T> *temp = head;
    if (pos >= nodes)
        throw("sobrepasa el limite");
    else
    {
        Node<T> *temp = head;
        for (int i = 0; i < pos; i++)
            temp = temp->next;
        return temp->data;
    }
};

template <typename T>
int ForwardList<T>::size()
{
    return nodes;
};

/*

template <typename T>
T ForwardList<T>::insert(T data, int pos)
{
    if (pos >= nodes)
        throw("sobrepasa el limite");
    else
    {
        if (pos == 0)
            push_front(data);
        else if (pos == nodes - 1)
            push_back(data);
        else
        {
            Node<T> *temp1 = head;
            int count = 0;
            while (count != pos - 1)
            {
                temp1 = temp1->next;
                count++;
            }
            Node<T> *temp2 = new Node<T>;
            temp2->data = data;
            temp2->next = temp1->next;
            temp1->next = temp2;
            nodes++;
        }
    }
};

template <typename T>
bool ForwardList<T>::remove(int pos)
{
    if (is_empty())
        throw("sin definir");
    else if (pos < nodes)
    {
        if (pos == 0)
            pop_front();
        else if (pos == nodes - 1)
            pop_back();
        else
        {
            Node<T> *temp1 = head;
            Node<T> *temp2 = head;
            int count = 0;
            while (count != pos)
            {
                temp2 = temp2->next;
                if (count != 0)
                    temp1 = temp1->next;
                count++;
            }
            temp1->next = temp2->next;
            temp2->next = nullptr;
            temp2->killSelf();
        }
        nodes--;
        return true;
    }
    else
        return false;
};

template <typename T>
T &ForwardList<T>::operator[](int pos)
{
    Node<T> *temp = head;
    if (pos >= nodes)
        throw("sobrepasa el limite");
    else
    {
        Node<T> *temp = head;
        for (int i = 0; i < pos; i++)
            temp = temp->next;
        return temp->data;
    }
};



template <typename T>
int ForwardList<T>::size()
{
    return nodes;
};

template <typename T>
void ForwardList<T>::clear()
{
    head->killSelf();
    head = new Node<T>;
    nodes = 0;
};

template <typename T>
void ForwardList<T>::sort() // bubble sort
{
    if (is_empty() || nodes == 1)
        throw("");
    else
    {
        for (int i = 0; i < nodes; i++)
        {
            Node<T> *temp1 = head;
            Node<T> *temp2 = head->next;
            do
            {
                if (temp1->data > temp2->data)
                {
                    T aux = temp2->data;
                    temp2->data = temp1->data;
                    temp1->data = aux;
                }
                temp1 = temp1->next;
                temp2 = temp2->next;
            } while (temp2 != nullptr);
        }
    }
};

template <typename T>
bool ForwardList<T>::is_sorted()
{
    Node<T> *temp = head;
    while (temp->next != nullptr)
    {
        if (temp->data > temp->next->data)
            return false;
        temp = temp->next;
    }
    return true;
};

template <typename T>
void ForwardList<T>::reverse() // pide complejidad On
{
    if (is_empty() || nodes == 1)
        throw("");
    else
    {
        Node<T> *temp1 = nullptr;
        Node<T> *temp2 = head;
        while (temp2 != nullptr)
        {
            Node<T> *temp3 = temp2->next;
            temp2->next = temp1;
            temp1 = temp2;
            temp2 = temp3;
        };
        head = temp1;
    }
};

template <typename T>
std::string ForwardList<T>::name()
{
    return "ForwardList";
};
*/
#endif