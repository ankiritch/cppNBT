#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

#include <nbt.h>


int main() {

    std::string path = "../data/data.dat";
    std::ios::openmode mode =std::ios::binary;



    nbt n(path, mode);

    nbt::INT myInt;
    myInt.name = "MyIntName";
    myInt.payload = 1337;

    std::list<char> buffer;
    buffer.push_back(0x0a);
    buffer.push_back(0x00);
    buffer.push_back(0x00);

    std::list<char> s_buffer = n.nbtDataToWritableArray(myInt);

    for (char c : s_buffer) {
        buffer.push_back(c);
    }

    
    myInt.payload = 89;
    myInt.name = "AnotherInt";

    std::list<char> t_buffer = n.nbtDataToWritableArray(myInt);

    for (char c : t_buffer) {
        buffer.push_back(c);
    }

    buffer.push_back(0x00);

    n.writeNBT(buffer);

    //getch();
    return 0;

}