#include "administrator.h"

std::string Administrator::getEmpType() {
    return "Administrator";
}

std::map<int, std::shared_ptr<ReceptReport>> Administrator::listReceptReports() {
    return receptreport_manager->reports;
}

std::map<int, std::shared_ptr<PhotoReport>> Administrator::listPhotoReports() {
    return photoreport_manager->reports;
}

std::vector<std::shared_ptr<Material>> Administrator::listMaterials(){
    return material_manager->getMaterials();
}

void Administrator::addMaterial(std::string mat_type, unsigned int quantity){
    auto mat = material_manager->findMaterialbyType(mat_type);
    if (mat != nullptr) {
        mat->stock_qty += quantity;
    } else {
    auto material = std::make_shared<Material>(mat_type, quantity);
    material_manager->addMaterial(material);
    }
}

void Administrator::removeMaterial(std::string mat_type){
    material_manager->deleteMaterial(mat_type);
}
