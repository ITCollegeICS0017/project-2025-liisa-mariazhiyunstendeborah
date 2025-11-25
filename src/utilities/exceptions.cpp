#include "exceptions.h"

const char* CustomException::what() const noexcept {
    return err_msg.c_str();
}

const std::string& ObjectException::getObjIdentifier() {
    return obj_identifier;
}

const std::string& MaterialNotFound::getMaterialType() {
    return mat_type;
}
