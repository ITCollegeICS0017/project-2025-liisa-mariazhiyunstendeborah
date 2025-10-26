#include "materialmanager.h"

std::map<std::string, std::shared_ptr<Material>>& MaterialManager::getMaterials() {
    return materials;
    //E: ?
}

void MaterialManager::addMaterial(const std::string& mat_type, std::shared_ptr<Material> material)  {
    auto iter = materials.find(mat_type);
    if (iter != materials.end()) {
        materials.at(mat_type) = material;
    } else {
        //E: better E
    }
}

void MaterialManager::editMaterial(std::string& mat_type, std::shared_ptr<Material> updated_mat)  {
    //E: ?
    materials.at(mat_type) = updated_mat;
}

void MaterialManager::deleteMaterial(std::string mat_type)  {
    materials.erase(mat_type);
}

Material* MaterialManager::findMaterial(std::string mat_type) {
    auto iter = materials.find(mat_type);
    if (iter != materials.end()) {
        return iter->second.get();
    }
    //E:
    return nullptr;
}
