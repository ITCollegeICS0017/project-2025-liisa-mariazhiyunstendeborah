#include "material.h"

void Material::ConsumeMaterial(int quantity) {
    if (stock_qty != 0 && stock_qty <= quantity) {
        stock_qty -= quantity;
    } else {
        //Error code. Apparently u can do bools for this
        //stuff.
    }
}
