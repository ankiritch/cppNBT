
#include <nbt.h>

#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <typeinfo>
#include <any>

void logToConsole(std::string m1, std::string m2="") {
    std::cout <<"[NBT]: "<< m1 + " " + m2 << std::endl;
}

nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes valueArg, NbtType listTypeArg) {
    type = typeArg;
    name = nameArg;
    payload = valueArg;
    //payloadPtr = &payload;

    if (type == NbtType::LIST) {
        listType = listTypeArg;
    }

    if (!isCorrectType()) {
        throw std::runtime_error("Invalid type");
    }

    setTag();
}

// nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, NbtPayloadTypes *valueArg, NbtType listTypeArg) {
//     type = typeArg;
//     name = nameArg;
//     payloadPtr = valueArg;

//     if (type == NbtType::LIST) {
//         listType = listTypeArg;
//     }

//     if (!isCorrectType()) {
//         throw std::runtime_error("Invalid type");
//     }

//     setTag();
// }

// nbt::NbtData::NbtData(NbtType typeArg, std::string nameArg, std::list<NbtData*> valuePtrArg, NbtType listTypeArg) { //
//     type = typeArg;
//     name = nameArg;
//     payloadPtr = (NbtPayloadTypes*) &(payloadPtrList.front());

//     //Push all pointers to payload to list
//     // for (NbtData element : std::get<std::list<NbtData>>(payload)) {
//     //     element.saveNbtData(); //Save as otherwise inaccessible later
//     //     payloadPtrList.push_back(&element);
//     // }


//     //Push all pointers to outside to list
//     for (NbtData* element : valuePtrArg) {
//         payloadPtrList.push_back(element);
//     }

//     if (type == NbtType::LIST) {
//         listType = listTypeArg;
//     }

//     if (!isCorrectType()) {
//         throw std::runtime_error("Invalid type");
//     }
// }

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

bool nbt::NbtData::intToCorrectType() {
    NbtPayloadTypes* currentPayloadPtr;
    std::list<int8_t> tempByteArray;
    std::list<int64_t> tempLongArray;
    try {
            switch (type) {
                case NbtType::BYTE:
                    setPayload(static_cast<int8_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::SHORT:
                    setPayload(static_cast<int16_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::INT:
                    setPayload(static_cast<int32_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::LONG:
                    setPayload(static_cast<int64_t>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::FLOAT:
                    setPayload(static_cast<float>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::DOUBLE:
                    setPayload(static_cast<double>(std::get<int>(getPayload())));
                    return true;
                    break;
                case NbtType::BYTE_ARRAY:
                    currentPayloadPtr = getPayloadPtr();
                    for (int element : std::get<std::list<int>>(*currentPayloadPtr)) {
                        tempByteArray.push_back(static_cast<int8_t>(element));
                    }
                    *currentPayloadPtr = tempByteArray;
                    return true;
                    break;
                case NbtType::LONG_ARRAY:
                    currentPayloadPtr = getPayloadPtr();
                    for (int element : std::get<std::list<int>>(*currentPayloadPtr))  {
                        tempLongArray.push_back(static_cast<int64_t>(element));
                    }
                    return true;
                    break;
                default:
                    return false; //string, list, compound, int_array do not have directly convertible payload
                    break;
            }
        }
        catch (...) {
            return false;
        }
}


bool nbt::NbtData::isCorrectType() {
    // std::list<NbtData*> currentPayloadPtrList;
    // if (type == NbtType::LIST) {
    //     try {
    //         currentPayloadPtrList = payloadPtrList;
    //     }
    //     catch (...) {
    //         logToConsole("Failed to get payloadPtrList");
    //         return false;
    //     }
    // }

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
            // for (NbtData* elementPtr : currentPayloadPtrList) {
            //     NbtData element = *elementPtr;
            //     if (listType != element.type) {
            //         throw std::runtime_error("List contains invalid type");
            //     }
            //     if ((!element.isCorrectType())) {
            //             logToConsole(std::string(element.name) + " element in list conversion failed.");
            //             return false;
            //     }

            //     *elementPtr = element;
            // }

            for (NbtData& element : std::get<std::list<NbtData>>(payload)) {
                if (listType != element.type) {
                    throw std::runtime_error("List contains invalid type");
                }
                if ((!element.isCorrectType())) {
                        logToConsole(std::string(element.name) + " element in list conversion failed.");
                        return false;
                }
            }
            return true;
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
    if (intToCorrectType()) { //if not list try converting
        logToConsole(name, "type converted.");
        return true;
    }
    else {
        logToConsole(name, "conversion failed.");
        return false;
    }
};

bool nbt::NbtData::setPayload(NbtPayloadTypes newPayload) {
    NbtPayloadTypes oldPayload{payload};
    // NbtPayloadTypes* oldPayloadPtr{payloadPtr};

    //set local, point to it
    payload = newPayload;
    //payloadPtr = &payload;

    if (!isCorrectType()) {
        payload = oldPayload;
        //payloadPtr = oldPayloadPtr;
        logToConsole(name , "attempted to set invalid type.");
    }

    return true;
}

// bool nbt::NbtData::setPayload(NbtPayloadTypes *newPayload) {
//     NbtPayloadTypes* oldPayloadPtr{payloadPtr};

//     //point to original
//     payloadPtr = newPayload;

//     if (!isCorrectType()) {
//         payloadPtr = oldPayloadPtr;
//         logToConsole(name, "attempted to set invalid type.");
//     }

//     return true;
// }

nbt::NbtPayloadTypes nbt::NbtData::getPayload() {
    // if (type != NbtType::LIST || type != NbtType::COMPOUND) {
    //     return *payloadPtr;        
    // } else {
    //     return payloadPtrList;
    // }
    return payload;
}

nbt::NbtPayloadTypes* nbt::NbtData::getPayloadPtr() {

    // if (type != NbtType::LIST || type != NbtType::COMPOUND) {
    //     return payloadPtr;
    // } else {
    //     return ((NbtPayloadTypes*) &payloadPtrList);
    // }
    return &payload;
}

// std::list<nbt::NbtData*> nbt::NbtData::getPayloadPtrList() {
//     return payloadPtrList;
// }

// std::list<nbt::NbtData*>* nbt::NbtData::getPayloadPtrListPtr() {
//     return &payloadPtrList;
// }

nbt::nbt(std::string path, std::ios::openmode mode) {
    outfile.open(path, mode);
}

void nbt::writeNBT() {
    std::cout << "Writing NBT file" << std::endl;
    for (char c : buffer) {
        outfile << c;
    }
}

template<>
void nbt::pushData<float>(float data, std::list<int8_t> &buffer) {
    buffer.push_back(1);
    std::cout << data << std::endl;
    return;
}

template <>
void nbt::pushData<double>(double data, std::list<int8_t> &buffer) {
    buffer.push_back(1);
    std::cout << data << std::endl;
    return;
}

template <>
void nbt::pushData<std::string>(std::string data, std::list<int8_t> &buffer) {
    return pushString(data, buffer);
}

template<typename T>
void nbt::pushData(T data, std::list<int8_t> &buffer) {
    for (int i = (sizeof(data)-1); i >= 0; i--) {
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wconversion"
        buffer.push_back((data >> 8*i) & 0xFF);
        #pragma GCC diagnostic pop
    }
    return;
}

void nbt::pushString(std::string str, std::list<int8_t> &buffer) {
    for (char c : str) {
        buffer.push_back(c);
    }
    return;
}

void nbt::setBuffer(std::list<int8_t> newBuffer) {
    buffer = newBuffer;
}

int8_t nbt::NbtData::getTag() {
    return tag;
}

void mergeBuffers(std::list<int8_t> &buffer1, std::list<int8_t> buffer2) {
    buffer1.splice(buffer1.end(), buffer2);
}

std::list<int8_t> nbt::nbtToCharList(NbtData nbtData) {
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wconversion"


    std::list<int8_t> currentBuffer{};

    pushData<int8_t>(nbtData.getTag(), currentBuffer);
    pushData<int16_t>(nbtData.name.size(), currentBuffer);
    pushData<std::string>(nbtData.name, currentBuffer);


    switch (nbtData.type) {
        case NbtType::BYTE:
            pushData<int8_t>(std::get<int8_t>(nbtData.payload), currentBuffer);
            break;
        case NbtType::SHORT:
            pushData<int16_t>(std::get<int16_t>(nbtData.payload), currentBuffer);
            break;
        case NbtType::INT:
            pushData<int32_t>(std::get<int32_t>(nbtData.payload), currentBuffer);
            break;
        case NbtType::LONG:
            pushData<int64_t>(std::get<int64_t>(nbtData.payload), currentBuffer);
            break;
        case NbtType::FLOAT:
            pushData<float>(std::get<float>(nbtData.payload), currentBuffer);
            break;
        case NbtType::DOUBLE:
            pushData<double>(std::get<double>(nbtData.payload), currentBuffer);
            break;
        case NbtType::BYTE_ARRAY:
            pushData<int32_t>(std::get<std::list<int8_t>>(nbtData.payload).size(), currentBuffer);
            for (int8_t element : std::get<std::list<int8_t>>(nbtData.payload)) {
                pushData<int8_t>(element, currentBuffer);
            }
            break;
        case NbtType::STRING:
            pushData<int16_t>(std::get<std::string>(nbtData.payload).size(), currentBuffer);
            pushData<std::string>(std::get<std::string>(nbtData.payload), currentBuffer);
            break;
        case NbtType::LIST:
            //pushData<int8_t>(nbtData.listType, currentBuffer); TODO
            pushData<int32_t>(std::get<std::list<NbtData>>(nbtData.payload).size(), currentBuffer);
            for (NbtData element : std::get<std::list<NbtData>>(nbtData.payload)) {
                mergeBuffers(currentBuffer, nbtToCharList(element));
                pushData<int8_t>(0x00, currentBuffer);
            }
            break;
        case NbtType::COMPOUND:
            for (NbtData element : std::get<std::list<NbtData>>(nbtData.payload)) {
                mergeBuffers(currentBuffer, nbtToCharList(element));
            }
            pushData<int8_t>(0x00, currentBuffer);
            break;
        case NbtType::INT_ARRAY:
            pushData<int32_t>(std::get<std::list<int32_t>>(nbtData.payload).size(), currentBuffer);
            for (int32_t element : std::get<std::list<int32_t>>(nbtData.payload)) {
                pushData<int32_t>(element, currentBuffer);
            }
            break;
        case NbtType::LONG_ARRAY:
            pushData<int32_t>(std::get<std::list<int64_t>>(nbtData.payload).size(), currentBuffer);
            for (int64_t element : std::get<std::list<int64_t>>(nbtData.payload)) {
                pushData<int64_t>(element, currentBuffer);
            }
            break;
        case NbtType::NONE:
            pushData<int8_t>(0x00, currentBuffer);
            break;
    }
    
    #pragma GCC diagnostic pop
    return currentBuffer;
}

// auto nbt::NbtData::getCorrectTypePayload() {
//     switch (type) {
//         case NbtType::BYTE:
//             return std::get<int8_t>(payload);
//             break;
//         case NbtType::SHORT:
//             return std::get<int16_t>(payload);
//             break;
//         case NbtType::INT:
//             return std::get<int32_t>(payload);
//             break;
//         case NbtType::LONG:
//             return std::get<int64_t>(payload);
//             break;
//         case NbtType::FLOAT:
//             return std::get<float>(payload);
//             break;
//         case NbtType::DOUBLE:
//             return std::get<double>(payload);
//             break;
//         case NbtType::BYTE_ARRAY:
//             return std::get<std::list<int8_t>>(payload);
//             break;
//         case NbtType::STRING:
//             return std::get<std::string>(payload);
//             break;
//         case NbtType::LIST:
//             return std::get<std::list<NbtData>>(payload);
//             break;
//         case NbtType::COMPOUND:
//             return std::get<std::list<NbtData>>(payload);
//             break;
//         case NbtType::INT_ARRAY:
//             return std::get<std::list<int32_t>>(payload);
//             break;
//         case NbtType::LONG_ARRAY:
//             return std::get<std::list<int64_t>>(payload);
//             break;
//         case NbtType::NONE:
//             return 0;

//     }
//     return 0;
// }

void nbt::bufferNbt() {

}