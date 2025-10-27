#include "materialmanager.h"

std::vector<std::shared_ptr<Material>>& MaterialManager::getMaterials() {
    return materials;
    //E: ?
}

void MaterialManager::addMaterial(std::shared_ptr<Material> material)  {
    materials.push_back(material);
}

void MaterialManager::editMaterial(const std::shared_ptr<Material>& updated_mat)  {
    for (auto& material : materials) {
        if (material->mat_type == updated_mat->mat_type) {
            material = updated_mat;
            return;
        }
    }
    //E: if not found, make known
}

void MaterialManager::deleteMaterial(std::string mat_type)  {
    materials.erase(std::remove_if(materials.begin(), materials.end(), [mat_type](const std::shared_ptr<Material>& material) { return material->mat_type == mat_type; }), materials.end());
}

Material* MaterialManager::findMaterialbyType(std::string mat_type) {
    for (const auto& material : materials) {
        if (material->mat_type == mat_type) {
            return material.get();
        }
    }
    return nullptr;
    //E: if not found, make known
}
