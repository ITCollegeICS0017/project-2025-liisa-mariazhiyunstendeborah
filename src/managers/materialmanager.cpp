#include "materialmanager.h"

std::vector<std::shared_ptr<Material>>& MaterialManager::getMaterials() {
    return materials;
    //E: ?
}

void MaterialManager::addMaterial(std::shared_ptr<Material> material)  {
    if (!findMaterialbyType(material->mat_type)) {
    materials.push_back(material);
    } else {
        throw std::invalid_argument("Material already exists!");
    }
}

void MaterialManager::editMaterial(const std::shared_ptr<Material>& updated_mat)  {
    if (!findMaterialbyType(updated_mat->mat_type)) {
        throw std::invalid_argument("Material not found!");
    } else {
        for (auto& material : materials) {
            if (material->mat_type == updated_mat->mat_type) {
                material = updated_mat;
                return;
            }
        }
    }
}

void MaterialManager::deleteMaterial(std::string mat_type)  {
    if (!findMaterialbyType(mat_type)) {
        throw std::invalid_argument("Material does not exist to be deleted!");
    } else {
        materials.erase(std::remove_if(materials.begin(), materials.end(), [mat_type](const std::shared_ptr<Material>& material) { return material->mat_type == mat_type; }), materials.end());
    }
}

Material* MaterialManager::findMaterialbyType(std::string mat_type) {
    for (const auto& material : materials) {
        if (material->mat_type == mat_type) {
            return material.get();
        }
    }
    return nullptr;
}
