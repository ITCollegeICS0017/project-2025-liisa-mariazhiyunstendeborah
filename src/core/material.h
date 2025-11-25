#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

class Material{
    public:
        // mat_type should be unique
        std::string mat_type;
        //stock quantity
        unsigned int stock_qty = 0;

        Material(std::string mat_type) : mat_type(mat_type) { }

        //constructor with specified stock_qty
        Material(std::string mat_type, unsigned int stock_qty) : mat_type(mat_type), stock_qty(stock_qty) { }

        virtual ~Material() = default;
};

#endif
