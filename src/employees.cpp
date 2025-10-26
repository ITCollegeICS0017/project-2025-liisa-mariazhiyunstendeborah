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

//Todo: consumed_materials is unsynced w materials
//some way to make this consumption automatically take an effect on the materials
void Photographer::consumeMaterial(std::string mat_type, int quantity){
    consumed_materials[mat_type] += quantity;
}

const std::map<std::string, int>& Photographer::getConsumedMaterials() {
    return consumed_materials;
}

int Photographer::submitReport(int emp_id){
    auto report = std::make_shared<PhotoReport>(emp_id, consumed_materials);
    //I: should consumed_materials be cleared after each
    //submission?
    return photoreport_manager->addReport(report);
}

//These should likely be implemented higher up, or else here with a reporttostring function as reports do not need
//to be private. To be implemented upon more knowledge of the consoleui.
/*
std::map<int, std::shared_ptr<ReceptReport>> Administrator::listReceptReports() {

}

std::map<int, std::shared_ptr<PhotoReport>> Administrator::listPhotoReports() {
}
*/

std::map<std::string, std::shared_ptr<Material>> Administrator::listMaterials(){
    return material_manager->getMaterials();
}

void Administrator::addMaterial(std::string mat_type, int quantity){
    auto material = std::make_shared<Material>(mat_type, quantity);
    material_manager->addMaterial(mat_type, material);
}

void Administrator::removeMaterial(std::string mat_type){
    material_manager->deleteMaterial(mat_type);
}
