#ifndef NBT_H
#define NBT_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <variant>
#include <cstdint>
#include <map>

class nbt {
    public:
        //Tags
        static const char TAG_End{0x00};
        static const char TAG_Byte{0x01};
        static const char TAG_Short{0x02};
        static const char TAG_Int{0x03};
        static const char TAG_Long{0x04};
        static const char TAG_Float{0x05};
        static const char TAG_Double{0x06};
        static const char TAG_Byte_Array{0x07};
        static const char TAG_String{0x08};
        static const char TAG_List{0x09};
        static const char TAG_Compound{0x0a};
        static const char TAG_Int_Array{0x0b};
        static const char TAG_Long_Array{0x0c}; 
        

        nbt(std::string path, std::ios::openmode mode);
        void writeNBT(std::list<char> buffer);
        void setBuffer(std::list<char> newBuffer);


        enum class NbtType{BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY, NONE};

        struct NbtData;

        using NbtPayloadTypes = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::list<int8_t>, std::string, std::list<int32_t>, std::list<int64_t>, std::list<std::string>, std::list<NbtData>>;

        struct Payload {
            //enum PayloadGroup{Single, Multi} group{};
            NbtPayloadTypes value;

            // Payload();
            // Payload(NbtPayloadTypes valueArg);
        };

        struct NbtData {
            private:
                char tag;
            public:
                NbtType type{};
                std::string name;
                //Payload payload;
                NbtPayloadTypes payload;
                NbtType listType{NbtType::NONE}; //only when type is LIST is it not NONE

                void setTag();
                bool isCorrectType();
                bool convertToCorrectType();
                bool setPayload(NbtPayloadTypes newPayload);

                NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg = NbtType::NONE); 
        };


    private:
        std::ofstream outfile;
        std::list<char> buffer;

        void pushNumber(auto payload, std::list<char> &buffer);
};

#endif