#include "employees.h"

std::string Receptionist::getEmpType() {
    return "Receptionist";
}

int Receptionist::makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days) {
    auto order = std::make_shared<Order>(client, service, in_x_days, clock);
    return order_manager->addOrder(order);
}

//Todo: consoleui must make sure that employee eixsts
void Receptionist::assignOrder(Order* assign, int emp_id){
    if (assign != nullptr) {
        assign->assigned_emp_id = emp_id;
    } else {
        throw std::invalid_argument("Passed in a nullptr!");
    }
}

int Receptionist::submitReport(){
    auto completed_orders = order_manager->getCompletedOrders();
    auto total_profits = order_manager->calculateProfits(completed_orders);
    auto receptreport = std::make_shared<ReceptReport>(emp_id, clock, completed_orders, total_profits);
    return receptreport_manager->addReport(receptreport);
}

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
    } else {
    material->stock_qty -= quantity;
    //consumed_materials->editMaterial(std::make_shared<Material>(mat_type, quantity));
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

void Administrator::addMaterial(std::shared_ptr<Material> material, unsigned int quantity){
    auto mat = material_manager->findMaterialbyType(material->mat_type);
    if (mat != nullptr) {
        material->stock_qty += quantity;
        material_manager->editMaterial(material);
    } else {
    material->stock_qty = quantity;
    material_manager->addMaterial(material);
    }
}

void Administrator::removeMaterial(std::string mat_type){
    material_manager->deleteMaterial(mat_type);
}
