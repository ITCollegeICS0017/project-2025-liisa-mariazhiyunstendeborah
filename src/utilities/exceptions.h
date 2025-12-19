#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

//Abstract exception class
class CustomException : public std::exception {
    protected:
        std::string err_msg;
    
    public:
        CustomException(const std::string& err_msg) : err_msg(err_msg) {}

        const char* what() const noexcept override;
};

//Abstract repository exception class
class ObjectException : public CustomException {
    protected:
        std::string obj_identifier;
    
    public:
        ObjectException(const std::string& err_msg, const std::string& obj_identifier) : CustomException(err_msg), obj_identifier(obj_identifier) {}

        const std::string& getObjIdentifier();
}; 

//Occurs when using Repository.addObject() if a duplicate object is found
class DuplicateObjectException : public ObjectException {
    public:
        DuplicateObjectException(const std::string& obj_identifier) : ObjectException("Object already exists in repository: " + obj_identifier, obj_identifier) {}
};

//Occurs when using Repository.deleteObject() or Repository.editObject() if object is not found 
class MissingObjectException : public ObjectException {
    public:
        MissingObjectException(const std::string& obj_identifier) : ObjectException("Object does not exist in repository: " + obj_identifier, obj_identifier) {}
};

//Occurs when using Administrator.deleteMaterial(), Photographer.consumeMaterial() to propogate repo error if material is not found in global material repository
class MaterialNotFound : public CustomException {
    protected:
        std::string mat_type;
    
    public:
        MaterialNotFound(const std::string& mat_type) : CustomException("Material not found: " + mat_type), mat_type(mat_type) {}

        const std::string& getMaterialType();
};

//Occurs when using Photographer.consumeMaterial() if material consumption quantity is more than material stock quantity in global material repository 
class InvalidConsumption : public CustomException {
    protected:
        int stock_qty;
    
    public:
        InvalidConsumption(const int& stock_qty) : CustomException("Invalid consumption, stock quantity = " + std::to_string(stock_qty)), stock_qty(stock_qty) {}
};

#endif
