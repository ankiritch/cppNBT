#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    nbt::COMPOUND root;
    root.name = "root";

    nbt::INT myInt;
    myInt.name = "MyIntName";
    myInt.payload = 1337;

    nbt::COMPOUND sCompound;
    sCompound.name = "sCompound";
    sCompound.payload.push_back(myInt);

    root.payload.push_back(myInt);
    root.payload.push_back(sCompound);

    std::list<char> buffer;
    // buffer.push_back(0x0a);
    // buffer.push_back(0x00);
    // buffer.push_back(0x00);


    buffer = n.nbtDataToWritableArray(root);

    // buffer.push_back(0x00);

    n.writeNBT(buffer);

    //getch();
    return 0;

}