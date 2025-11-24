#include "materialrepository.h"

std::vector<std::shared_ptr<Material>>& MaterialRepository::getMaterials() {
  return materials;
}

void MaterialRepository::addMaterial(std::shared_ptr<Material> material) {
  if (!findMaterialbyType(material->mat_type)) {
    materials.push_back(material);
  } else {
    throw std::invalid_argument("Material already exists!");
  }
}

void MaterialRepository::editMaterial(
    const std::shared_ptr<Material>& updated_mat) {
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

void MaterialRepository::deleteMaterial(std::string mat_type) {
  if (!findMaterialbyType(mat_type)) {
    throw std::invalid_argument("Material does not exist to be deleted!");
  } else {
    materials.erase(
        std::remove_if(materials.begin(), materials.end(),
                       [mat_type](const std::shared_ptr<Material>& material) {
                         return material->mat_type == mat_type;
                       }),
        materials.end());
  }
}

// Upon not finding a material, returns a nullptr rather than return an error,
// so it's easier to use in other functions for checking if a material exists.
Material* MaterialRepository::findMaterialbyType(std::string mat_type) {
  for (const auto& material : materials) {
    if (material->mat_type == mat_type) {
      return material.get();
    }
  }
  return nullptr;
}
