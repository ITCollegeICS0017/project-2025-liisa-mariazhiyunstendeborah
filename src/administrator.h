#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "employees.h"

class Administrator: public Employee {
    private:
        InMemoryMaterialManager* material_manager;
        ReceptReportManager* receptreport_manager;
        PhotoReportManager* photoreport_manager;

    public:
        Administrator(InMemoryOrderManager* order_manager, std::string emp_name, InMemoryMaterialManager* material_manager, ReceptReportManager* receptreport_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager, emp_name), material_manager(material_manager), receptreport_manager(receptreport_manager), photoreport_manager(photoreport_manager) { }

        std::string getEmpType();

        std::map<int, std::shared_ptr<ReceptReport>> listReceptReports();

        std::map<int, std::shared_ptr<PhotoReport>> listPhotoReports();

        std::vector<std::shared_ptr<Material>> listMaterials();

        void addMaterial(std::string mat_type, unsigned int quantity);

        void removeMaterial(std::string mat_type);
};

#endif