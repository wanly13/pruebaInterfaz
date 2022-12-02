#ifndef BLOCK_H
#define BLOCK_H

//#include "librerias.h"
#include "sha256.h"
#include<vector>

struct DataD //to modify to admit any type of input, not only transactions
{
private:
    vector<string> data;
    /*
    float monto;
    string emisor;
    string receptor;
    string time;
    string date;
    */
public:
    DataD() = default;
    DataD( vector<string> data){
        this->data = data;
        //insertNamesToBST(data); call this function on blockchain class
        //hacer string matching para la busqueda
    }
    /*
    DataD(float _monto, string _emisor, string _receptor, string _time, string _date)
    {
        this->monto = _monto;
        this->emisor = _emisor;
        this->receptor = _receptor;
        this->time = _time;
        this->date = _date;
    }
    */
    ~DataD() = default;
    // getters:
    vector<string> get_data(){
        return this->data;
    }
    /*
    float get_monto() { return this->monto; };
    string get_emisor() { return this->emisor; };
    string get_receptor() { return this->receptor; };
    string get_time() { return this->time; };
    string get_date() { return this->date; };
    */
};
class Block
{
private:
    vector<DataD*> dataBlock; // arreglo de registros
    string * prev_hashcode = nullptr;
    string hashcode;
    string generateHashcode();
    int nonce; // iniciar codigo hash con 4 0's
    int index;
    int rand_value;
    //int reg_capacity;
    //Block * prev; //puedo avanzar si y solo si el codigo hash sea el previo del siguiente

public:
    Block();
    Block(vector<DataD*> dataBlock, int _index) // testear otros tamaños
    {
        this->nonce = 0;
        this->index = _index;
        this->dataBlock = dataBlock;
        this->rand_value = 0;
        //this->hashcode = generateHashcode();
    };
    ~Block()
    {
        for (auto &it: dataBlock)
        {
            it->~DataD();
        }
        dataBlock.~vector();
    };

    void setPrevHashcode(string *prev_hashcode)
    {
        this->prev_hashcode = prev_hashcode;
        this->hashcode = generateHashcode();
    }
    string& get_hash() {return this->hashcode;};
    string* get_prev_hash() {return this->prev_hashcode;};
    int get_nonce() {return this->nonce;};
    void show_data();
    bool validHashcode();
    int get_index(){return this->index;};
    vector<DataD*> getDataBlock(){return this->dataBlock;}
};

bool Block::validHashcode() //valida si el codigo hash que se obtiene con los demas atributos del bloque Y EL CODIGO HASH PREVIO es que mismo del actual
{
    string to_hash = "";
    for (auto &it:dataBlock)
    {
        for(auto &i:it->get_data()){
            to_hash += i;
        }
    }
    to_hash += to_string(nonce);
    char nuevo[sizeof(to_hash) + 1];
    strcpy(nuevo, to_hash.c_str());
    if(SHA256(nuevo, rand_value).first == hashcode)return true;
    else return false;
}

string Block::generateHashcode() // el codigo hash depende de todos los valores del conjunto de registros, lo cual lo hace mas seguro
{
    string to_hash = "";
    for (auto &it: dataBlock)
    {
        for(auto &i:it->get_data()){
            to_hash += i;
        }
    }
    to_hash += to_string(index);
    if(prev_hashcode!=nullptr)
        to_hash += *prev_hashcode;
    
    string sha;
    clock_t t;
    t=clock();
    cout<<endl<<"Buscando Nonce para Bloque "<<this->index<<"...";
    int count=0;
    srand(time(NULL));
    while (true)
    {
        int valor = 1000 + rand() % 9999;
        //cout <<endl<<"testing nonce " << valor << endl;
        string a = to_string(valor);
        string b = to_hash;
        a += b;
        char nuevo[sizeof(a) + 1];
        strcpy(nuevo, a.c_str());
        pair<string,int> result = SHA256(nuevo, rand_value);
        sha = result.first;
        //cout <<"hashcode: " << sha << endl;
        string c = "";
        c += sha[0];
        c += sha[1];
        c += sha[2];
        c += sha[3];
        count+=1;
        if (c == "0000"){
            double dif = (clock()-t)/(double)CLOCKS_PER_SEC;
            cout<<"!Nonce encontrado en: "<<dif<<" segundos"<<endl
                <<"(Se probaron "<<count<<" Nounces)"<<endl;
            this->nonce = valor;
            this->rand_value = result.second;
            break;
        }
    }

    return sha;
};

void Block::show_data(){
    int i=1;
    for(auto &it: dataBlock){
        cout<<"Data #"<<i<<":"<<endl;
            for(auto j:it->get_data()){
                cout<<j<<", ";
            }
            cout<<endl<<endl;
            i+=1;
    }
};

#endif