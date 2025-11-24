#include "photographer.h"

std::string Photographer::getEmpType() { return "Photographer"; }

// checks that the order to be changed exists
void Photographer::switchOrderStatus(Order* changedorder,
                                     CompletionStatus compl_status) {
  if (changedorder != nullptr) {
    changedorder->compl_status = compl_status;
  } else {
    throw std::invalid_argument("Passed in a nullptr!");
  }
}

// Checks if entered material exists in global material repository
// if the material does not exist, throws an error;
// if the material's stock quantity is less than the quantity to be consumed,
// throws an error; if material found, the consumed quantity is subtracted from
// the stock quantity. Next, checks that the material does not exist in the
// photographer-specific consumed_materials repository, if the material exists
// in consumed_materials, consumed quantity increases by the input quantity; if
// the material does not exist in consumed_materials, it is created with the
// input quantity.
void Photographer::consumeMaterial(std::string mat_type,
                                   unsigned int quantity) {
  auto material = material_repository->findMaterialbyType(mat_type);
  if (!material) {
    throw std::invalid_argument("Material not found!");
  } else if (material->stock_qty < quantity) {
    throw std::invalid_argument("Not enough of this material in stock!");
  }
  material->stock_qty -= quantity;
  material = consumed_materials->findMaterialbyType(mat_type);
  if (!material) {
    consumed_materials->addMaterial(
        std::make_shared<Material>(mat_type, quantity));
  } else {
    consumed_materials->editMaterial(
        std::make_shared<Material>(mat_type, material->stock_qty + quantity));
  }
}

// returns map of photographer-specific consumed materials
std::map<std::shared_ptr<Material>, int> Photographer::getConsumedMaterials() {
  std::map<std::shared_ptr<Material>, int> ret;
  auto cons_mats = consumed_materials->getMaterials();
  for (auto cons_mat : cons_mats) {
    ret.insert({cons_mat, cons_mat->stock_qty});
  }
  return ret;
}

// uses getConsumedMaterials to create the photographer report
int Photographer::submitReport() {
  auto report =
      std::make_shared<PhotoReport>(emp_id, clock, getConsumedMaterials());
  return photoreport_repository->addReport(report);
}

// custom destructor to make sure consumed_materials is destroyed
Photographer::~Photographer() { delete this->consumed_materials; }