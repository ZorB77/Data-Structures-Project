#include <iostream>
#include <string.h>
#include "HasitoTabla.h"

int main()
{
    HashTable<int,int> HT;
    
 
    HT.Insert(2, 8);
    HT.Insert(1, 2);
    HT.Insert(7, 6);
   
    //std::cout << HT.Search(2);
   
     return 0;
}

