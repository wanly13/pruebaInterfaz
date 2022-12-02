#ifndef BSTREE_H
#define BSTREE_H

#include "block.h"
//#include "iterator.h"
#include <queue>
#include <string>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include<stack>

using namespace std;

template <typename T>
struct NodeBT
{

    T data;
    NodeBT *left;
    NodeBT *right;
    string name; //nombre
    list<pair<Block*, int>> whereToFind; //donde aparece ese nombre

    NodeBT() : left(nullptr), right(nullptr) {}
    NodeBT(string _name) : left(nullptr), right(nullptr), name(_name){
        /*
        T x;
        for(auto i:_name)
            x+=int(i);
        this->data = x;
    */
    }
    //void addLocation(Block* loc){
    //    whereToFind.push_back(loc);
    //}
    void KillSelf()
    {
        if (this->right != nullptr)
            this->right->KillSelf();
        if (this->left != nullptr)
            this->left->KillSelf();
        whereToFind.~list();
        delete this;
    }
};



template <typename T>
class BSTree
{
//public:
  //  typedef BSTIterator<T> iterator;

private:
    NodeBT<T> *root;

    //=========================Implementacion==========================
public:
    BSTree() : root(nullptr) {}
    void insert(string name, Block* b, int j)
    {
        cout<<"Name adding..."<<name<<endl;
        
        int x=0;
        for(auto i:name){
            x+=int(i);
        }
        NodeBT<T> *its = find(this->root, x);
        if (its==nullptr)
            insert(this->root, x, name, b, j);
        else its->whereToFind.push_back({b,j});
    };

    void findAndShow(string name){
        int x = 0;
        for(auto i:name){
            x+=int(i);
        }
        int count=1;
        NodeBT<T> *its = find(this->root, x);
        if (its != nullptr){
            if (its->name == name){
               cout<<"Se encontro el Nombre..."<<endl
                   <<"Mostrando Informacion..."<<endl<<endl;
                for(auto i: its->whereToFind)
                {
                    cout<<"Data #"<<count<<':'<<endl;
                    for(auto l: (i.first->getDataBlock()[i.second]->get_data())){
                        cout<<l<<", ";
                    }
                    count++;
                    cout<<endl<<endl;
                }
            } 
            else cout<<"El nombre no se encuentra el el BlockChain"<<endl;
        }
       
        
    }
    bool find(string name)//summa de ascci del nombre
    {
        int x = 0;
        for(auto i:name){
            x+=int(i);
        }

        NodeBT<T> *its = find(this->root, x);
        if (its != nullptr){
            if (its->name == name)
                return true;
            else return false;
        }
        else
            return false;
    };

    string displayInOrder()
    {
        string cadena;
        recorridoInOrder(this->root, cadena);
        return cadena;
    };

    string displayPreOrder()
    {
        string cadena;
        recorridoPreOrder(this->root, cadena);
        return cadena;
    };

    string displayPostOrder()
    {
        string cadena;
        recorridoPostOrder(this->root, cadena);
        return cadena;
    };

    int height()
    {
        return height(this->root) - 1;
    };

    T minValue()
    {
        return (minValue(this->root))->data;
    };

    T maxValue()
    {
        return (maxValue(this->root))->data;
    };

    void remove(T value)
    {
        NodeBT<T> *temp = find(this->root, value); // TEMP ACCEDE DIRECTAMENTE AL NODO, YA Q FIND DEVUELVE UN NODO POR REFERENCIA, ENTONCES PUEDO HACER DELETE
        if (temp != nullptr)
            remove(temp);
    };

    bool isBalanced()
    {
        return isBalanced(this->root);
    };

    int size()
    {
        return size(this->root);
    };

    bool isFull() // es aquel en el que todos los nodos tienen 0 o 2 hijos
    {
        return isFull(this->root);
    };

    T successor(T value) // Retornar el valor siguiente de "value" en el arbol
    {
        NodeBT<T> *temp = root;
        NodeBT<T> *temp2 = nullptr;
        bool s = find_sucessor(temp, value, temp2);
        if (s)
            return temp2->data;
        else
            throw("no existe el valor en el arbol");
    };

    T predecessor(T value) // Retornar el valor anterior de "value" en el arbol
    {
        NodeBT<T> *temp = root;
        NodeBT<T> *temp2 = nullptr;
        bool s = find_predecessor(temp, value, temp2);
        if (s)
            return temp2->data;
        else
            throw("no existe el valor en el arbol");
    };

    void clear()
    { // Liberar todos los nodos (usar root->KillSelf)
        this->root->KillSelf();
        this->root = nullptr;
    };

    void buildFromOrderedArray(T *array, int n) // dado un array ordenado construir un arbol binario balanceado
    {
        clear();
        this->root = new NodeBT<T>();
        buildFromOrderedArray(this->root, array, 0, n);
    };
    string displayBFS()
    {
        NodeBT<T> *temp = this->root; // Recorrido en anchura (BreadthFirstSearch)
        return displayBFS(temp);
    };
    string displayDFS()
    { // Recorrido en profundidad (DepthFirstSearch)
        NodeBT<T> *temp = this->root;
        return displayDFS(temp);
    };
    /*
    iterator begin(BSTIterator<int>::Type _) // Retorna el inicio del iterador
    {
        iterator ite = iterator(this->&root, _);
        return ite;
    };    
    iterator end() // Retorna el final del iterador
    {
        iterator ite = iterator(&(maxValue(this->root)), InOrder);
    };
    */
    
    ~BSTree()
    {
        this->root->KillSelf();
    }; // Destructor del arbol

    void show_tree()
    {
        show_inorder(this->root);
    };

public:
    NodeBT<T> *insert(NodeBT<T> *&node, T value, string name, Block* b, int j)
    {
        if (node == nullptr)
        {
            node = new NodeBT<T>(name);
            node->data = value;
            node->whereToFind.push_back({b,j});
            node->left = node->right = nullptr;
        }
        else if (value < node->data)
            return insert(node->left, value, name, b, j);
        else if (value > node->data)
            return insert(node->right, value, name, b, j);
        return nullptr;
    };

    NodeBT<T> *find(NodeBT<T> *&node, T value) // envio por referencia a node porque find lo uso en otra funcion donde modifico el nodo encontrado
    {
        if (node == nullptr)
            return nullptr;
        else if (value < node->data)
            return find(node->left, value);
        else if (value > node->data)
            return find(node->right, value);
        else
            return node;
    };

    bool find_sucessor(NodeBT<T> *node, T value, NodeBT<T> *&scs)
    {
        if (node == nullptr)
        {
            scs = nullptr;
            return false;
        }
        else if (value < node->data)
        {
            scs = node;
            return find_sucessor(node->left, value, scs);
        }
        else if (value > node->data)
        {
            return find_sucessor(node->right, value, scs);
        }
        else if (value == node->data)
        {
            // return node;
            if (node->right != nullptr)
            {
                scs = minValue(node->right);
            }
            return true;
        }
    };

    bool find_predecessor(NodeBT<T> *node, T value, NodeBT<T> *&scs)
    {
        if (node == nullptr)
        {
            scs = nullptr;
            return false;
        }
        else if (value < node->data)
        {
            return find_predecessor(node->left, value, scs);
        }
        else if (value > node->data)
        {
            scs = node;
            return find_predecessor(node->right, value, scs);
        }
        else if (value == node->data)
        {
            // return node;
            if (node->left != nullptr)
            {
                scs = maxValue(node->left);
            }
            return true;
        }
    };

    NodeBT<T> *find_parent(NodeBT<T> *&node, T value)
    {
        if (node == nullptr)
            return nullptr;
        if (node->left != nullptr)
        {
            if (node->left->data == value)
                return node;
            else if (value < node->left->data || value < node->data)
                return find_parent(node->left, value);
        }
        if (node->right != nullptr)
        {
            if (node->right->data == value)
                return node;
            else if (value > node->right->data || value > node->data)
                return find_parent(node->right, value);
        }
    };

    void recorridoInOrder(NodeBT<T> *node, string &cadena)
    {
        if (node == nullptr)
            return;
        recorridoInOrder(node->left, cadena);
        cadena += to_string(node->data);
        cadena += ' ';
        recorridoInOrder(node->right, cadena);
    };

    void recorridoPreOrder(NodeBT<T> *node, string &cadena)
    {
        if (node == nullptr)
            return;
        cadena += to_string(node->data);
        cadena += ' ';
        recorridoPreOrder(node->left, cadena);
        recorridoPreOrder(node->right, cadena);
    };

    void recorridoPostOrder(NodeBT<T> *node, string &cadena)
    {
        if (node == nullptr)
            return;
        recorridoPostOrder(node->left, cadena);
        recorridoPostOrder(node->right, cadena);
        cadena += to_string(node->data);
        cadena += ' ';
    };

    int height(NodeBT<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
        {
            int left_height = height(node->left);
            int right_height = height(node->right);
            return max(left_height, right_height) + 1;
        }
    };

    NodeBT<T> *minValue(NodeBT<T> *&node)
    {
        if (node == nullptr)
            return node;
        else if (node->left != nullptr)
            return minValue(node->left);
        else
            return node;
    };

    NodeBT<T> *maxValue(NodeBT<T> *&node)
    {
        if (node == nullptr)
            return node;
        else if (node->right != nullptr)
            return maxValue(node->right);
        else
            return node;
    };

    void remove(NodeBT<T> *&node)
    {
        if (node->left == nullptr && node->right == nullptr) // si es hoja simplemente elimino el nodo y cambio el puntero del padre hacia ese nodo como nullptr
        {
            NodeBT<T> *temp = node;
            NodeBT<T> *temp2 = nullptr;
            if (&node != &(this->root)) // si no es el root, busco a su padre (evaluar )
            {
                temp2 = find_parent(this->root, node->data);
                if (temp2->data > node->data)
                    temp2->left = nullptr;
                else
                    temp2->right = nullptr;
            }
            node->KillSelf();
            temp = nullptr;
        }
        else if (node->left && node->right) // si es padre remplazo su data por el maximo valor del subarbol izquierdo
        {
            NodeBT<T> *temp = maxValue(node->left);
            T tv = temp->data;
            remove(temp);
            node->data = tv;
        }
        else
        {
            if (node->left == nullptr)
            {
                NodeBT<T> *temp = minValue(node->right);
                T tv = temp->data;
                remove(temp);
                node->data = tv;
            }

            else
            {
                NodeBT<T> *temp = maxValue(node->left);
                T tv = temp->data;
                remove(temp);
                node->data = tv;
            }
        }
    };

    bool isBalanced(NodeBT<T> *node)
    {
        int right_h;
        int left_h;
        if (node == nullptr)
            return true;
        left_h = height(node->left) - 1;
        right_h = height(node->right) - 1;

        if (abs(left_h - right_h) <= 1 && isBalanced(node->left) && isBalanced(node->right))
            return true;
        else
            return false;
    }

    int size(NodeBT<T> *node)
    {
        if (node == nullptr)
            return 0;
        else
            return (size(node->left) + 1 + size(node->right));
    };

    bool isFull(NodeBT<T> *node)
    { // falta probar!! 🧐
        // es aquel en el que todos los nodos tienen 0 o 2 hijos
        if (node->left != nullptr && node->right != nullptr)
        {
            return (isFull(node->left) + isFull(node->right));
        }
        if (node->left == nullptr && node->right == nullptr)
        {
            return true;
        }
        else
            return false;
    };

    void buildFromOrderedArray(NodeBT<T> *&node, T *array, int range_left, int range_right)
    {
        int mid = (range_left + range_right - 1) / 2;
        node->data = array[mid];
        if (mid != range_left)
        {
            if (array[(mid + 1 + range_right - 1) / 2] != root->data)
            {
                node->right = new NodeBT<T>();
                buildFromOrderedArray(node->right, array, mid + 1, range_right);
            }
        }
        if (mid % 2 == 0 && &node == &root)
            mid += 1;
        if (mid != range_left)
        {
            node->left = new NodeBT<T>();
            buildFromOrderedArray(node->left, array, range_left, mid);
        }
    };

    string displayBFS(NodeBT<T> *node)
    {
        
        string cadena;
        queue<NodeBT<T> *> cola;
        cola.push(node);
        int t = node->data;

        while (!cola.empty())
        {
            node = cola.front();
            if(node->data>t) t = node->data;
            if(node->data<t){
                cout<<endl;
                t=node->data;
                }

            cout<<cola.front()->data<<" ";
            
            cadena += to_string((cola.front())->data);
            cadena+=' ';
            cola.pop();
            if (node->left != nullptr)
            {
                cola.push(node->left);
            }
            if (node->right != nullptr)
            {
                cola.push(node->right);
            }
        }
        cout<<endl;
        return cadena;
    };

    string displayDFS(NodeBT<T> *node)
    {
        string cadena;
        stack<NodeBT<T> *> pila;
        pila.push(node);
        while (!pila.empty())
        {
            node = pila.top();
            cadena += to_string((pila.top())->data);
            cadena+=' ';
            pila.pop();
            if (node->right != nullptr)
            {
                pila.push(node->right);
            }
            if (node->left != nullptr)
            {
                pila.push(node->left);
            }
        }
        return cadena;
    };

    void swap(NodeBT<T> *&a, NodeBT<T> *&b) // intercambiar values de 2 nodos, (sin usar por ahora 🤨 )
    {
        T d = a->data;
        a->data = b->data;
        b->data = d;
    }

    void show_inorder(NodeBT<T> *node)
    {
        if (node == nullptr)
            return;
        show_inorder(node->left);
        cout << node->data << " ";
        show_inorder(node->right);
    };
};

#endif
