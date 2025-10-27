#include "employees.h"

int Receptionist::makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days) {
    auto order = std::make_shared<Order>(client, service, in_x_days);
    return order_manager->addOrder(order);
}

void Receptionist::assignOrder(Order* assign, int emp_id){
    if (assign != nullptr) {
        assign->assigned_emp_id = emp_id;
    } else {
        //E: handle error
    }
}

int Receptionist::submitReport(int emp_id){
    auto completed_orders = order_manager->getCompletedOrders();
    auto total_profits = order_manager->calculateProfits(completed_orders);
    auto receptreport = std::make_shared<ReceptReport>(emp_id, completed_orders, total_profits);
    return receptreport_manager->addReport(receptreport);
}

void Photographer::switchOrderStatus(Order* changedorder, CompletionStatus compl_status){
    if (changedorder != nullptr) {
        changedorder->compl_status = compl_status;
    } else {
        //E: handle error
    }
}

void Photographer::consumeMaterial(std::shared_ptr<Material> material, int quantity){
    if (!material_manager->findMaterialbyType(material->mat_type)) {
        std::cout << "Material doesn't exist!";
    } else {
    material->stock_qty -= quantity;
    material_manager->editMaterial(material);
    consumed_materials->addMaterial(material);
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

int Photographer::submitReport(int emp_id){
    auto report = std::make_shared<PhotoReport>(emp_id, getConsumedMaterials());
    return photoreport_manager->addReport(report);
}

Photographer::~Photographer() {
    delete this->consumed_materials;
}

std::vector<std::shared_ptr<Material>> Administrator::listMaterials(){
    return material_manager->getMaterials();
}

void Administrator::addMaterial(std::string mat_type, int quantity){
    Material* material = material_manager->findMaterialbyType(mat_type);
    if (material != nullptr) {
        material->stock_qty += quantity;
        material_manager->editMaterial(std::shared_ptr<Material>(material));
    }
    material_manager->addMaterial(std::make_shared<Material>(mat_type, quantity));
}

void Administrator::removeMaterial(std::string mat_type){
    material_manager->deleteMaterial(mat_type);
}
