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
        void pushData(auto number, std::list<int8_t> &buffer);
        void pushString(std::string str, std::list<int8_t> &buffer);
        //Every function above should be private after testing


        //Tags
        static const int8_t TAG_End{0x00};
        static const int8_t TAG_Byte{0x01};
        static const int8_t TAG_Short{0x02};
        static const int8_t TAG_Int{0x03};
        static const int8_t TAG_Long{0x04};
        static const int8_t TAG_Float{0x05};
        static const int8_t TAG_Double{0x06};
        static const int8_t TAG_Byte_Array{0x07};
        static const int8_t TAG_String{0x08};
        static const int8_t TAG_List{0x09};
        static const int8_t TAG_Compound{0x0a};
        static const int8_t TAG_Int_Array{0x0b};
        static const int8_t TAG_Long_Array{0x0c}; 
        

        nbt(std::string path, std::ios::openmode mode);
        
        void writeNBT();
        void bufferNbt();
        void setBuffer(std::list<int8_t> newBuffer);

        


        enum class NbtType{BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY, NONE};

        struct NbtData;

        using NbtPayloadTypes = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::list<int8_t>, std::string, std::list<int32_t>, std::list<int64_t>, std::list<std::string>, std::list<NbtData>>;//, std::list<NbtData*>>;

        // template <typename T>
        // struct Payload {
        //     T value;
        // };

        //template <typename T>
        struct NbtData {
            private:
                int8_t tag;
                //NbtPayloadTypes* payloadPtr;

                //used only when type is LIST
                //std::list<nbt::NbtData*> payloadPtrList;
            public:
                NbtType type{};
                std::string name;
                NbtType listType{NbtType::NONE};

                void setTag();
                int8_t getTag();

                bool isCorrectType();
                bool intToCorrectType();
                NbtPayloadTypes payload;

                bool setPayload(NbtPayloadTypes newPayload);
                //bool setPayload(NbtPayloadTypes* newPayload);

                NbtPayloadTypes getPayload();
                auto getCorrectTypePayload();

                NbtPayloadTypes* getPayloadPtr();

                //std::list<nbt::NbtData*> getPayloadPtrList();
                //std::list<nbt::NbtData*>* getPayloadPtrListPtr();

                std::list<NbtData> getListPayload(int index=0);
                NbtData getListPayloadElement(int index=0);
                NbtData* getListPayloadElementPtr(int index=0);


                NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg = NbtType::NONE); 
                // NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes* valueArg, NbtType listTypeArg = NbtType::NONE); 

                // NbtData(NbtType typeArg, std::string nameArg, std::list<NbtData*> valuePtrArg, NbtType listTypeArg = NbtType::NONE); //
        };

        std::list<int8_t> nbtToCharList(NbtData nbtData);

    private:
        std::ofstream outfile;
        std::list<int8_t> buffer;

};

#endif