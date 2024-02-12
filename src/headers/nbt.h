#ifndef NBT_H
#define NBT_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <variant>
#include <cstdint>
#include <memory>

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

        using NbtPayloadTypes = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::string, std::list<int8_t>, std::list<int32_t>, std::list<int64_t>, std::list<std::string>, std::list<NbtData>>;

        struct Payload {
            //enum PayloadGroup{Single, Multi} group{};
            NbtPayloadTypes value;
            NbtType listType{NbtType::NONE}; //only when type is LIST is it not NONE

            Payload() {
            }
            
            Payload(NbtPayloadTypes valueArg) {
                value = valueArg;
            }

            Payload(NbtPayloadTypes valueArg, NbtType listTypeArg) {
                value = valueArg;

                if (listTypeArg == NbtType::LIST) {
                    listType = listTypeArg;
                } 
            }


        };

        struct NbtData {
            private:
                char tag;
            public:
                NbtType type{};
                std::string name;
                Payload payload;

                void setTag(NbtType typeArg) {
                    switch (typeArg) {
                        case NbtType::BYTE:
                            tag = TAG_Byte;
                            break;
                        case NbtType::SHORT:
                            tag = TAG_Short;
                            break;
                        case NbtType::INT:
                            tag = TAG_Int;
                            break;
                        case NbtType::LONG:
                            tag = TAG_Long;
                            break;
                        case NbtType::FLOAT:
                            tag = TAG_Float;
                            break;
                        case NbtType::DOUBLE:
                            tag = TAG_Double;
                            break;
                        case NbtType::BYTE_ARRAY:
                            tag = TAG_Byte_Array;
                            break;
                        case NbtType::STRING:
                            tag = TAG_String;
                            break;
                        case NbtType::LIST:
                            tag = TAG_List;
                            break;
                        case NbtType::COMPOUND:
                            tag = TAG_Compound;
                            break;
                        case NbtType::INT_ARRAY:
                            tag = TAG_Int_Array;
                            break;
                        case NbtType::LONG_ARRAY:
                            tag = TAG_Long_Array;
                            break;

                        case NbtType::NONE:
                            break;

                    }
                }

                bool isCorrectType(NbtType type, NbtPayloadTypes &valueArg) {
                    switch (type) {
                        case NbtType::BYTE:
                            if (std::holds_alternative<int8_t>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::SHORT:
                            if (std::holds_alternative<int16_t>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::INT:
                            if (std::holds_alternative<int32_t>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::LONG:
                            if (std::holds_alternative<int64_t>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::FLOAT:
                            if (std::holds_alternative<float>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::DOUBLE:
                            if (std::holds_alternative<double>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::BYTE_ARRAY:
                            if (std::holds_alternative<std::list<int8_t>>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::STRING:
                            if (std::holds_alternative<std::string>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::LIST:
                            if (std::holds_alternative<std::list<NbtData>>(valueArg)) { //check if all NbtData is of correct type
                                return true;
                            }
                            break;
                        case NbtType::COMPOUND:
                            if (std::holds_alternative<std::list<NbtData>>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::INT_ARRAY:
                            if (std::holds_alternative<std::list<int32_t>>(valueArg)) {
                                return true;
                            }
                            break;
                        case NbtType::LONG_ARRAY:
                            if (std::holds_alternative<std::list<int64_t>>(valueArg)) {
                                return true;
                            }
                            break;
                        default:
                            return false;
                            break;
                    }
                    return false;
                };

                NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg = NbtType::NONE) {
                    if (!isCorrectType(typeArg, valueArg)) {
                        throw std::invalid_argument("Invalid type");
                    }
                    type = typeArg;
                    name = nameArg;
                    if (listTypeArg != NbtType::LIST) {
                        payload = Payload(valueArg);
                    } else {
                        payload = Payload(valueArg, listTypeArg);
                    }
                    setTag(type);
                }
                
        };


    private:
        std::ofstream outfile;
        std::list<char> buffer;

        void pushNumber(auto payload, std::list<char> &buffer);


};

#endif

/* To delete later, previously: nbt, public */
//All possible data types, contain name, payload, and tag (lists: datatypeTag)
//use vector later to store data

//Forward declaration to use in NBT_DATATYPES
// struct BYTE;
// struct SHORT;
// struct INT;
// struct LONG;
// struct FLOAT;
// struct DOUBLE;
// struct BYTE_ARRAY;
// struct STRING;
// struct LIST;
// struct COMPOUND;
// struct INT_ARRAY;
// struct LONG_ARRAY;

// using NBT_DATATYPES = std::variant<BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY, LONG_ARRAY>;
// using NBT_SINGLE_PAYLOAD_DATATYPES = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::string>;
// using NBT_MULTI_PAYLOAD_DATATYPES = std::variant<std::list<int8_t>, std::list<int32_t>, std::list<int64_t>, std::list<std::string>, std::list<NBT_DATATYPES>>;
// using NBT_PAYLOAD_DATATYPES = std::variant<int8_t, int16_t, int32_t, int64_t, float, double, std::list<int8_t>, std::list<int32_t>, std::list<int64_t>, std::string, std::list<NBT_DATATYPES>>;


// std::list<char> nbtDataToWritableArray(NBT_DATATYPES nbtData);

// struct BYTE {
//     std::string name;
//     int8_t payload;
//     const char TAG{0x01};
// };
// struct SHORT {
//     std::string name;
//     int16_t payload;
//     const char TAG{0x02};
// };
// struct INT {
//     std::string name;
//     int32_t payload;
//     const char TAG{0x03};
// };
// struct LONG {
//     std::string name;
//     int64_t payload;
//     const char TAG{0x04};
// };
// struct FLOAT {
//     std::string name;
//     float payload;
//     const char TAG{0x05};
// };
// struct DOUBLE {
//     std::string name;
//     double payload;
//     const char TAG{0x06};
// };
// struct BYTE_ARRAY {
//     std::string name;
//     std::list<int8_t> payload;
//     const char TAG{0x07};
// };
// struct STRING {
//     std::string name;
//     std::string payload;
//     const char TAG{0x08};
// };
// struct LIST {
//     std::string name;
//     char datatypeTag;
//     std::list<NBT_DATATYPES> payload;
//     const char TAG{0x09};
// };
// struct COMPOUND {
//     std::string name;
//     std::list<NBT_DATATYPES> payload;
//     const char TAG{0x0a};
// };
// struct INT_ARRAY {
//     std::string name;
//     std::list<int32_t> payload;
//     const char TAG{0x0b};
// };
// struct LONG_ARRAY {
//     std::string name;
//     std::list<int64_t> payload;
//     const char TAG{0x0c};
// };