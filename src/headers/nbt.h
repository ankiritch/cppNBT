#include <iostream>
#include <fstream>
#include <list>

class nbt {
    public:
        const char TAG_End{0x00};
        const char TAG_Byte{0x01};
        const char TAG_Short{0x02};
        const char TAG_char{0x03};
        const char TAG_Long{0x04};
        const char TAG_Float{0x05};
        const char TAG_Double{0x06};
        const char TAG_Byte_Array{0x07};
        const char TAG_String{0x08};
        const char TAG_List{0x09};
        const char TAG_Compound{0x0a};
        const char TAG_char_Array{0x0b};
        const char TAG_Long_Array{0x0c};

        nbt(std::string path, std::ios::openmode mode);
        
        void writeNBT();
        void setBuffer(std::list<char> newBuffer);

    private:
        std::ofstream outfile;
        std::list<char> buffer;
};