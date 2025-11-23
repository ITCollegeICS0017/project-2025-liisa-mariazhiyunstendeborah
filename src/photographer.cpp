#include "photographer.h"

std::string Photographer::getEmpType() {
    return "Photographer";
}

void Photographer::switchOrderStatus(Order* changedorder, CompletionStatus compl_status){
    if (changedorder != nullptr) {
        changedorder->compl_status = compl_status;
    } else {
        throw std::invalid_argument("Passed in a nullptr!");
    }
}

void Photographer::consumeMaterial(std::string mat_type, unsigned int quantity){
    auto material = material_manager->findMaterialbyType(mat_type);
    if (!material) {
        throw std::invalid_argument("Material not found!");
    } else if (material->stock_qty < quantity) {
        throw std::invalid_argument("Not enough of this material in stock!");
    }
    material->stock_qty -= quantity;
    material = consumed_materials->findMaterialbyType(mat_type);
    if (!material) {
        consumed_materials->addMaterial(std::make_shared<Material>(mat_type, quantity));
    } else {
        consumed_materials->editMaterial(std::make_shared<Material>(mat_type, material->stock_qty + quantity));
    }
}

std::map<std::shared_ptr<Material>, int> Photographer::getConsumedMaterials() {
    std::map<std::shared_ptr<Material>, int> ret;
    auto cons_mats = consumed_materials->getMaterials();
    for (auto cons_mat : cons_mats) {
        ret.insert({cons_mat, cons_mat->stock_qty});
    }
    return ret;
}

int Photographer::submitReport(){
    auto report = std::make_shared<PhotoReport>(emp_id, clock, getConsumedMaterials());
    return photoreport_manager->addReport(report);
}

Photographer::~Photographer() {
    delete this->consumed_materials;
}