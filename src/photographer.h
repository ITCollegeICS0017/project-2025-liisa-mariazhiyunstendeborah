#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include "employees.h"

class Photographer: public Employee {
    private:
        IClock& clock;
        InMemoryMaterialManager* material_manager;
        PhotoReportManager* photoreport_manager;
        InMemoryMaterialManager* consumed_materials;

        std::map<std::shared_ptr<Material>, int> getConsumedMaterials();
    public:
        Photographer(InMemoryOrderManager* order_manager, std::string emp_name, IClock& clock, InMemoryMaterialManager* material_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager, emp_name), clock(clock), material_manager(material_manager), photoreport_manager(photoreport_manager) {
            this->consumed_materials = new InMemoryMaterialManager();
 }

        std::string getEmpType();

        void switchOrderStatus(Order* changedorder, CompletionStatus compl_status);

        void consumeMaterial(std::string mat_type, unsigned int quantity);


        int submitReport();

        ~Photographer() override;
};


#endif