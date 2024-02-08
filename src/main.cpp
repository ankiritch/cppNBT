#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    //std::list<char> buffer = {n.TAG_Compound, 0, 4, 'n', 'a', 'm', 'e', n.TAG_End};

    //n.setBuffer();

    //n.writeNBT();

    nbt::COMPOUND root;
    root.name = "root";

    nbt::BYTE aByte;
    aByte.name = "aByte";
    aByte.payload = 'b';

    nbt::STRING aString;
    aString.name = "aString";
    aString.payload = "Hello World!";

    root.payload.push_back(aByte);
    root.payload.push_back(aString);

    std::list<nbt::NBT_DATATYPES> localData;

    localData.push_back(root);

    getch();
    return 0;

}