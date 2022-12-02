#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "bst_m.h"
#include "block.h"
#include "forward.h"

using namespace std;
class BlockChain
{
private:
    ForwardList<Block *> chain; // <hashcode, bloque>
    int n_elements;             // number of elements;
    BSTree<int> searchTree;     // para busquedas.

public:
    BlockChain() { this->n_elements = 0; };
    ~BlockChain()
    {
        searchTree.~BSTree();
        chain.~ForwardList();
        delete this;
    };
    int size();
    bool is_empty();
    // bool find(); //falta implementar
    void insert_block(vector<DataD *> reg, string &nonce, string &hash, string & hash_prev);
    void find(string hashcode);
    void modifyDataOfBlock();
    void addNamesToTree();
    void findByName(string name);
    bool isValid();
};

//modificacion
void BlockChain::insert_block(vector<DataD *> reg, string &nonce, string &hash, string & hash_prev)
{
    int index = n_elements + 1;
    string *cod = nullptr;
    if (n_elements == 0)
    {
        cod = nullptr;
    }
    else
    {
        cod = &(chain.front()->get_hash());
    };
    Block *newBlock = new Block(reg, n_elements + 1);
    // newBlock->prev = chain.front();//apunta al anterior
    newBlock->setPrevHashcode(cod);
    chain.push_front(newBlock);
    addNamesToTree();
    // aqui ya tengo la data en el blockchain, ahora tengo que buscar nombres y setearlos al arbol
    this->n_elements++;

    cout << "######################################################################################" << endl
         << endl
         << "\t\t\t\tBLOQUE NRO: " << index << endl
         << endl
         << "NONCE: " << newBlock->get_nonce() << endl
         << "NRO TRANSACCIONES:  " << 4 << endl
         << endl;
    newBlock->show_data();
    string ph;
    if (newBlock->get_prev_hash() == nullptr)
        ph = '0';
    else
        ph = *(newBlock->get_prev_hash());
    cout << "CODIGO HASH PREVIO: " << ph << endl
         << "CODIGO HASH: " << newBlock->get_hash() << endl
         << endl
         << "######################################################################################" << endl
         << endl;

    nonce= newBlock->get_nonce();
    hash=  newBlock->get_hash();
    hash_prev= *(newBlock->get_prev_hash());


};

bool BlockChain::isValid()
{
}

void BlockChain::find(string hashcode)
{
    clock_t t;
    t = clock();
    srand(time(NULL));

    for (int i = 0; i < chain.size(); i++)
    {
        if (chain[i]->get_hash() == hashcode)
        {
            cout << endl
                 << "Se encontro el bloque..." << endl;
            cout << "######################################################################################" << endl
                 << endl
                 << "\t\t\t\tBLOQUE NRO: " << chain[i]->get_index() << endl
                 << endl
                 << "NONCE: " << chain[i]->get_nonce() << endl;
            // it->show_data();
            cout << "CODIGO HASH PREVIO: " << *(chain[i]->get_prev_hash()) << endl
                 << "CODIGO HASH: " << chain[i]->get_hash() << endl
                 << endl
                 << "######################################################################################" << endl
                 << endl;
            double dif = (clock() - t) / (double)CLOCKS_PER_SEC;
            cout << "Exec Time con busqueda lineal: " << dif << endl;
            return;
        }
    }
    cout << "No se encontro el bloque...\n";
}

int BlockChain::size()
{
    return this->n_elements;
}

bool BlockChain::is_empty()
{
    return this->n_elements == 0;
}

void BlockChain::modifyDataOfBlock() // for secure test
{
}

void BlockChain::findByName(string name)
{
    clock_t t;
    t = clock();
    srand(time(NULL));

    searchTree.findAndShow(name);

    double dif = (clock() - t) / (double)CLOCKS_PER_SEC;
    cout << "Exec Time con busqueda logaritmica: " << dif << endl;
}

void BlockChain::addNamesToTree()
{
    string name;
    int j = 0;
    for (auto &it : chain.front()->getDataBlock())
    {

        for (auto i : it->get_data())
        {
            for (auto k : i)
            {
                if (!((int(k) > 64 && int(k) < 90) || (int(k) > 96 && int(k) < 123)))
                    break;
                if (k == i.back())
                {
                    // encontre un nombre
                    searchTree.insert(i, chain.front(), j);
                    break;
                }
            }
        }
        j++;
    }
}

#endif