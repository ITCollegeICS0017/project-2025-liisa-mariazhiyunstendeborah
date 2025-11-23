#ifndef MATERIALREPOSITORY_H
#define MATERIALREPOSITORY_H

#include <algorithm>
#include "interfaces/imaterialrepository.h"
#include "core/material.h"

class MaterialManager {
    private:
        std::vector<std::shared_ptr<Material>> materials;

    public:
        std::vector<std::shared_ptr<Material>>& getMaterials();

        void addMaterial(std::shared_ptr<Material> material);

        void editMaterial(const std::shared_ptr<Material>& updated_mat);

        void deleteMaterial(std::string mat_type);

        Material* findMaterialbyType(std::string mat_type);
};

#endif
