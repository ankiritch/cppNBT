
#include <nbt.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <typeinfo>
#include <any>

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg) {
    if (!isCorrectType()) {
        throw std::invalid_argument("Invalid type");
    }
    type = typeArg;
    name = nameArg;
    payload = valueArg;

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    setTag();
}

void nbt::NbtData::setTag() {
    switch (type) {
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

bool nbt::NbtData::convertToCorrectType() {
    try {
        switch (type) {
            case NbtType::BYTE:
                payload = std::get<int8_t>(payload);
                return true;
                break;
            case NbtType::SHORT:
                payload = std::get<int16_t>(payload);
                return true;
                break;
            case NbtType::INT:
                payload = std::get<int32_t>(payload);
                return true;
                break;
            case NbtType::LONG:
                payload = std::get<int64_t>(payload);
                return true;
                break;
            case NbtType::FLOAT:
                payload = std::get<float>(payload);
                return true;
                break;
            case NbtType::DOUBLE:
                payload = std::get<double>(payload);
                return true;
                break;
            case NbtType::BYTE_ARRAY:
                payload = std::get<std::list<int8_t>>(payload);
                return true;
                break;
            case NbtType::STRING:
                payload = std::get<std::string>(payload);
                return true;
                break;
            case NbtType::LIST:
                payload = std::get<std::list<NbtData>>(payload); //check if all NbtData is of correct type
                return true;
                break;
            case NbtType::COMPOUND:
                payload = std::get<std::list<NbtData>>(payload);
                return true;
                break;
            case NbtType::INT_ARRAY:
                payload = std::get<std::list<int32_t>>(payload);
                return true;
                break;
            case NbtType::LONG_ARRAY:
                payload = std::get<std::list<int64_t>>(payload);
                return true;
                break;
            default:
                return false;
                break;
        }
    }
    catch (...) {
        return false;
    }
}

bool nbt::NbtData::isCorrectType() {
    switch (type) {
        case NbtType::BYTE:
            if (std::holds_alternative<int8_t>(payload)) {
                return true;
            }
            break;
        case NbtType::SHORT:
            if (std::holds_alternative<int16_t>(payload)) {
                return true;
            }
            break;
        case NbtType::INT:
            if (std::holds_alternative<int32_t>(payload)) {
                return true;
            }
            break;
        case NbtType::LONG:
            if (std::holds_alternative<int64_t>(payload)) {
                return true;
            }
            break;
        case NbtType::FLOAT:
            if (std::holds_alternative<float>(payload)) {
                return true;
            }
            break;
        case NbtType::DOUBLE:
            if (std::holds_alternative<double>(payload)) {
                return true;
            }
            break;
        case NbtType::BYTE_ARRAY:
            if (std::holds_alternative<std::list<int8_t>>(payload)) {
                return true;
            }
            break;
        case NbtType::STRING:
            if (std::holds_alternative<std::string>(payload)) {
                return true;
            }
            break;
        case NbtType::LIST:
            if (std::holds_alternative<std::list<NbtData>>(payload)) { //check if all NbtData is of correct type
                for (auto &element : std::get<std::list<NbtData>>(payload)) {
                    if ((!element.isCorrectType()) && listType == element.type) {
                        return false;
                    }
                }
                return true;
            }
            break;
        case NbtType::COMPOUND:
            if (std::holds_alternative<std::list<NbtData>>(payload)) {
                return true;
            }
            break;
        case NbtType::INT_ARRAY:
            if (std::holds_alternative<std::list<int32_t>>(payload)) {
                return true;
            }
            break;
        case NbtType::LONG_ARRAY:
            if (std::holds_alternative<std::list<int64_t>>(payload)) {
                return true;
            }
            break;
        default:
            return false;
            break;
    }
    if (convertToCorrectType()) {
        std::cout << name << " type converted\n";
        return true;
    }
    else {
        return false;
    }
};

// nbt::Payload::Payload() {}

// nbt::Payload::Payload(NbtPayloadTypes valueArg) {
//     value = valueArg;
// }


nbt::nbt(std::string path, std::ios::openmode mode) {
    outfile.open(path, mode);
}

void nbt::writeNBT(std::list<char> buffer) {
    for (char c : buffer) {
        outfile << c;
    }
}

void nbt::pushNumber(auto payload, std::list<char> &buffer) {
    for (int i = (sizeof(payload)-1); i >= 0; i--) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        buffer.push_back((payload >> 8*i) & 0xFF);
        #pragma GCC diagnostic pop
    }

    return;
}

void nbt::setBuffer(std::list<char> newBuffer) {
    buffer = newBuffer;
}


// using NBT_VECTOR_VARIANT = std::variant<std::string, char, nbt::NBT_SINGLE_PAYLOAD_DATATYPES, nbt::NBT_MULTI_PAYLOAD_DATATYPES>;
// using nbtVector = std::vector<NBT_VECTOR_VARIANT>;

// template <typename T>
// struct nbtVisitor {
//     nbtVector toReturn;

//     nbtVector operator()(T nbtData) {
//         std::visit([&](const auto& data) {
//             toReturn.push_back(data.TAG);
//             toReturn.push_back(data.name);
//             toReturn.push_back(data.payload);

//             if constexpr (std::is_same_v<decltype(data), nbt::LIST>) {
//                 toReturn.push_back(data.datatypeTag);
//             }
//         }, nbtData);
//         return toReturn;
//     }
// };


// std::list<char> nbt::nbtDataToWritableArray(NBT_DATATYPES nbtData) {
//     std::list<char> buffer;

//     //get nbt data as easily accessible vector
//     nbtVector data = std::visit(nbtVisitor<decltype(nbtData)>{}, nbtData);  
    
//     //Compound, list, ... -> Call recursively, insert returned buffer arrays nbtInto buffer and create header
//     //Other -> Return buffer

//     char currentTag{std::get<char>(data[0])};
//     std::string name = std::get<std::string>(data[1]);

//     //Push header (tag, name length, name), all dataypes have this
//     buffer.push_back(currentTag);
//     pushNumber((int16_t)name.size(), buffer); //name length size should be 2B

//     for (char c : name) {
//         buffer.push_back(c);
//     }


//     //Single value data types
//     if ((currentTag <= 6 || currentTag == 8) && currentTag != 0) {
//         //return header + payload as binary

        
//         //Push payload     

        
//         //NBT_SINGLE_PAYLOAD_DATATYPES payload = std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]); //produces error in variant 'std::bad_variant_access': what():  std::get: wrong index for variant

//         switch (currentTag) { //1: Byte, 2: Short, 3: Int, 4: Long, 5: Float, 6: Double, 8: String
//             case 1: {
//                 int8_t typePayload = std::get<int8_t>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(typePayload, buffer);
//                 break;
//             }
//             case 2: {
//                 int16_t typePayload = std::get<int16_t>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(typePayload, buffer);
//                 break;
//             }
//             case 3: {
//                 int32_t typePayload = std::get<int32_t>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(typePayload, buffer);
//                 break;
//             }
//             case 4: {
//                 int64_t typePayload = std::get<int64_t>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(typePayload, buffer);
//                 break;
//             }
//             case 5: {
//                 float typePayload = std::get<float>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(static_cast<int32_t>(typePayload), buffer);
//                 break;
//             }
//             case 6: {
//                 double typePayload = std::get<double>(std::get<NBT_SINGLE_PAYLOAD_DATATYPES>(data[2]));
//                 pushNumber(static_cast<int64_t>(typePayload), buffer);
//                 break;
//             }
//             case 8: { 
//                 std::string typePayload = std::get<std::string>(data[2]);
//                 pushNumber((int16_t)typePayload.size(), buffer);
//                 for (char c : typePayload) {
//                     buffer.push_back(c);
//                 }
//                 break;
//             }
//         }


//     } else if (currentTag == 0x0a) { //compound

//         //Get payload as one of the NBT_VECTOR_VARIANT types
//         NBT_MULTI_PAYLOAD_DATATYPES unconvertedPayload = std::get<NBT_MULTI_PAYLOAD_DATATYPES>(data[2]);
//         //Get payload as one of the NBT_MULTI_PAYLOAD_DATATYPES types
//         std::list<NBT_DATATYPES> payload = std::get<std::list<NBT_DATATYPES>>(unconvertedPayload);
//         std::list<char> compoundBuffer;

//         //Add each element in compound
//         for (NBT_DATATYPES d : payload) {
//             compoundBuffer = nbtDataToWritableArray(d);

//             for (char c : compoundBuffer) {
//                 buffer.push_back(c);
//             }
//         }

//         //End compound
//         buffer.push_back(0x00);

//     } else {
        
//     }

//     return buffer;
// }




