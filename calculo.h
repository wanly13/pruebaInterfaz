#ifndef CALCULO_H
#define CALCULO_H

#include "./code/blockChain.h"

void test(int op , string &nonce, string &hash, string & hash_prev){
  BlockChain cadena = BlockChain();
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

    
};



#endif
