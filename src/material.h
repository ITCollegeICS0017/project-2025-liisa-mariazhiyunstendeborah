#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material{
    public:
        // mat_type is unique
        std::string mat_type;
        unsigned int stock_qty = 0;

        Material(std::string mat_type) : mat_type(mat_type) { }
        Material(std::string mat_type, unsigned int stock_qty) : mat_type(mat_type), stock_qty(stock_qty) { }

        virtual ~Material() = default;
};

#endif
