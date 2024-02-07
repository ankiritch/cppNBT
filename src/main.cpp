#include <iostream>
#include <fstream>
#include <conio.h>

#include <nbt.h>
#include <list>

int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    std::list<char> buffer = {n.TAG_Compound, 0, 4, 'n', 'a', 'm', 'e', n.TAG_End};

    n.setBuffer(buffer);

    n.writeNBT();


    //getch();
    return 0;

}