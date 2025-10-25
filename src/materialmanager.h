#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <map>
#include <memory>
#include "material.h"

class MaterialManager {
    private:
        std::map<std::string, std::shared_ptr<Material>> materials;

    public:
        MaterialManager() = default;

        ~MaterialManager() = default;

        std::map<std::string, std::shared_ptr<Material>>& getMaterials() ;

        void addMaterial(const std::string& mat_type, std::shared_ptr<Material> material) ;

        void editMaterial(std::string& mat_type, std::shared_ptr<Material> updated_mat) ;

        void deleteMaterial(std::string mat_type) ;

        Material* findMaterial(std::string mat_type);
};

#endif
