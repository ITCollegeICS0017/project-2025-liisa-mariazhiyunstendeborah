#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "material.h"

class MaterialManager {
    private:
//Todo: make this into a vector or storing with int, otherwise mat_type is stored twice...
        std::vector<std::shared_ptr<Material>> materials;

    public:
        MaterialManager() = default;

        ~MaterialManager() = default;

        std::vector<std::shared_ptr<Material>>& getMaterials() ;

        void addMaterial(std::shared_ptr<Material> material) ;

        void editMaterial(const std::shared_ptr<Material>& updated_mat) ;

        void deleteMaterial(std::string mat_type) ;

        Material* findMaterialbyType(std::string mat_type);
};

#endif
