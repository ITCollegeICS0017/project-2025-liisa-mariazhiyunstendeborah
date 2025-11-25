#include "administrator.h"

std::string Administrator::getEmpType() { return "Administrator"; }

std::map<int, std::shared_ptr<ReceptReport>>
Administrator::listReceptReports() {
  return receptreport_repository->reports;
}

std::map<int, std::shared_ptr<PhotoReport>> Administrator::listPhotoReports() {
  return photoreport_repository->reports;
}

std::vector<std::shared_ptr<Material>> Administrator::listMaterials() {
  return material_repository->getMaterials();
}

// checks if the material exists in the material_repository.
// If it does not exist, material is created using the mat_type and entered
// quantity. If the specified material does exist, its quantity is increased by
// the input quantity.
void Administrator::addMaterial(std::string mat_type, unsigned int quantity) {
  auto mat = material_repository->findMaterialbyType(mat_type);
  if (mat != nullptr) {
    mat->stock_qty += quantity;
  } else {
    auto material = std::make_shared<Material>(mat_type, quantity);
    material_repository->addMaterial(material);
  }
}

// deletes a material entirely.
void Administrator::deleteMaterial(std::string mat_type) {
  try {
  material_repository->deleteMaterial(mat_type);
  } catch (const MissingObjectException& e) {
    throw MaterialNotFound(mat_type);
  }
}
