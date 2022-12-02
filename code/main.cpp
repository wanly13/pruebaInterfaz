#include "blockchain.h"
#include <chrono>
//#include <vector>
#include <fstream>
#include <sstream>

int menu(BlockChain &cadena);
void test(BlockChain &cadena);
void insert_data(BlockChain &cadena);
vector<DataD *> loadCSV(string file);
void newTest(BlockChain &cadea);

int main()
{
    BlockChain cadena = BlockChain();
    int i;
    while (i != 6)
    {
        i = menu(cadena);
    };
    return 0;
};

/* int menu(BlockChain &cadena)
{
    int var = 0;
    cout << endl
         << "\t\t\tGENERADOR DE BLOCKCHAIN" << endl
         << endl
         << "1. Generar bloques aleatorios" << endl
         << "2. Insertar transacciones (4 por bloque)" << endl
         << "3. buscar bloque" << endl
         << "4. new_test" << endl
         << "5. Buscar por nombre"<<endl
         << "6. salir" << endl;
    do
    {
        cout << "Ingrese Opcion: ";
        cin >> var;
    } while (var != 1 && var != 2 && var != 3 && var != 4 && var != 5 && var > 5 && var < 1);

    if (var == 1)
    {
        cout << endl
             << "\t\t\tGENERANDO BLOQUES ALEATORIOS..." << endl;
        test(cadena);
    }
    else if (var == 2)
    {
        int v = 0;
        do
        {
            cout << "Cuantas Transacciones ingresara? (multiplo de 4, minimo 4): ";
            cin >> v;
        } while (v <= 0 || v % 4 != 0);
        int tr = v / 4;
        for (int i = 0; i < tr; i++)
        {
            insert_data(cadena);
        }
    }
    else if (var == 3)
    {
        string c;
        cout << endl
             << "ingrese hashcode: ";
        cin >> c;
        cadena.find(c);
    }
    else if (var == 4)
    {
        newTest(cadena);
    }
    else if(var == 5){
        string name;
        cout<<"Ingrese el nombre: "; cin>>name;
        //getline(cin, name);
        cadena.findByName(name);
    }
    else
        return 6;
};
 */
/* 
void newTest(BlockChain &cadena){
    //insercion de data de un bloque
    
    cout << "Ingrese la informacion por filas separadas por comas...\n";
    int n_f = 4;
    int count = 0;
    vector<DataD*> data(n_f);
    string fila;
    while (count!=n_f)
    {
        cin>>fila;
        int n_words = 1;
        for (auto i : fila)
        {
            if (i == ',')
                n_words++;
        }
        vector<string> fila_to_b(n_words);
        string temp = "";
        int pos = 0;
        for (auto i : fila)
        {
            if (i == ',')
            {

                fila_to_b[pos] = temp;
                pos++;
                temp = "";
            }
            else if(i == fila[fila.size()-1]){
                fila_to_b[pos] = temp;
             }
            else
            {
                temp += i;
            }
        }
        DataD* dt = new DataD(fila_to_b);
        data[count] = dt;
        count++;
    }
    cadena.insert_block(data);
}
 */

/*
void insert_data(BlockChain &cadena)
{
    vector<DataD *> reg;
    float m;
    string e;
    string r;
    string t;
    string f;
    for (int i = 0; i < 4; i++)
    {
        cout << endl
             << "Transaccion " << i + 1 << ": " << endl;
        cout << "Ingrese monto: ";
        cin >> m;
        cout << "Persona que envia(solo Nombre): ";
        cin >> e;
        cout << "Destinatario(Solo Nombre): ";
        cin >> r;
        char y;
        do
        {
            cout << "Desea ingresar fecha y hora automaticamente? (s/n): ";
            cin >> y;
        } while (y != 's' && y != 'n' && y != 'S' && y != 'N');
        if (y == 'n' || y == 'N')
        {
            cout << "Ingrese Hora: ";
            cin >> t;
            cout << "Ingrese Fecha: ";
            cin >> f;
        }
        else
        {
            time_t ti = std::time(nullptr);
            tm *now = std::localtime(&ti);
            f = to_string(now->tm_mday);
            f += '/';
            f += to_string(now->tm_mon + 1);
            f += '/';
            f += to_string(now->tm_year - 100);

            auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
            t = to_string(now->tm_hour);
            t += ':';
            t += to_string(now->tm_min);
            cout << "Fecha actual: " << f << endl;
            cout << "Hora actual: " << t << endl;
        }
        DataD *reg1 = new DataD({to_string(m), e, r, t, f});
        reg.push_back(reg1);
    }
    cadena.insert_block(reg);
};*/

void test(int op , BlockChain &cadena, string &nonce, string &hash, string & hash_prev){

    if (op == 2)
    {
        vector<DataD *> reg;
        vector<DataD *> transacciones = loadCSV("MOCK_DATA2.csv");
        for (int i = 0; i < transacciones.size(); i++)
        
        {
            if (i % 4 == 0 && i != 0)
            {
                cadena.insert_block(reg);
                reg.clear();
            }
            reg.push_back(transacciones[i]);
        }
    }
    else if (op == 1) //transacciones bancarias :)
    {
        vector<DataD *> reg;
        DataD *reg1 = new DataD({"5000", "Pepe", "Pepa", "11:53", "Aug 25, 2022"});
        DataD *reg2 = new DataD({"35", "Piero", "Carla", "10:31", "Sep 11, 2001"});
        DataD *reg3 = new DataD({"559", "Daniela", "Carla", "13:24", "Jan 19, 2022"});
        DataD *reg4 = new DataD({"789", "Andrea", "Sofia", "15:06", "Apr 29, 2022"});
        string nonce1="";
        string hash_1= "";
        string hash_prev_1="";


        reg = {reg1, reg2, reg3, reg4};
        cadena.insert_block(reg, nonce1, hash_1,hash_prev_1);
//bloque 1
    //nonce1, hahs1, hash_prev
        
/*
        reg1 = new DataD({"500", "Sara", "Pepa", "16:48", "Oct 23, 2022"});
        reg2 = new DataD({"4578", "Tamara", "Esteban", "12:50", "Apr 16, 2022"});
        reg3 = new DataD({"234.6", "Wilson", "Gabriela", "18:20", "Aug 5, 2022"});
        reg4 = new DataD({"333.3", "Victor", "Katia", "11:28", "Feb 18, 2022"});

        reg = {reg1, reg2, reg3, reg4};
        cadena.insert_block(reg);

        reg1 = new DataD({"56.36", "Victor", "Sara", "9:37", "Jun 5, 2022"});
        reg2 = new DataD({"1000000.63", "Carlos", "Piero", "12:50", "Jun 23, 2022"});
        reg3 = new DataD({"5548", "Esteban", "Pepa", "1:03", "Nov 30, 2022"});
        reg4 = new DataD({"325.20", "Mario", "Pepe", "19:23", "Dec 31, 2022"});

        reg = {reg1, reg2, reg3, reg4};
        cadena.insert_block(reg);

        reg1 = new DataD({"345346.35", "Carla", "Tamara", "7:59", "Mar 25, 2022"});
        reg2 = new DataD({"25978", "Daniela", "Wilson", "6:12", "Apr 5, 2022"});
        reg3 = new DataD({"97245.20", "Gabriela", "Andrea", "8:33", "May 7, 2022"});
        reg4 = new DataD({"1.50", "Esteban", "Sara", "9:50", "Jul 9, 2022"});

        reg = {reg1, reg2, reg3, reg4};
        cadena.insert_block(reg);*/
    };
};

/* vector<DataD *> loadCSV(string file)
{
    vector<DataD *> data;
    fstream fin;
    fin.open(file, ios::in);
    vector<string> row;
    string line, word, temp;
    int i = 0;
    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        if (i++ == 0)
            continue;
        stringstream s(line);
        while (getline(s, word, ';'))
        {
            row.push_back(word);
        }
        vector<string> d(row.size());
       // if (row.size() == 5)
        //{
            d = {row[0], row[1], row[2], row[3], row[4]};
            DataD *t = new DataD(d);
            data.push_back(t);
        //}
    }
    return data;
} */
