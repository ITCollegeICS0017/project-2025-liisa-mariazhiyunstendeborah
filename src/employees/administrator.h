#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "core/employee.h"

//administrator employee, which can create, add and delete materials, as well as see reports and all materials
class Administrator: public Employee {
    private:
        MaterialRepository* material_repository;
        ReceptReportRepository* receptreport_repository;
        PhotoReportRepository* photoreport_repository;

    public:
        Administrator(OrderRepository* order_repository, std::string emp_name, MaterialRepository* material_repository, 
        ReceptReportRepository* receptreport_repository, PhotoReportRepository* photoreport_repository) : Employee(order_repository, emp_name), 
        material_repository(material_repository), receptreport_repository(receptreport_repository), photoreport_repository(photoreport_repository) { }

        //Used only during XML reading 
        Administrator(OrderRepository* order_repository, int emp_id, std::string emp_name, MaterialRepository* material_repository, 
        ReceptReportRepository* receptreport_repository, PhotoReportRepository* photoreport_repository) : Employee(order_repository, emp_id, emp_name), 
        material_repository(material_repository), receptreport_repository(receptreport_repository), photoreport_repository(photoreport_repository) { }

        //returns string of administrator's class name
        std::string getEmpType();

        //returns a map reports by receptionist(s)
        std::map<int, std::shared_ptr<ReceptReport>> listReceptReports();

        //returns a map of reports by photographer(s)
        std::map<int, std::shared_ptr<PhotoReport>> listPhotoReports();

        //returns a vector of materials
        std::vector<std::shared_ptr<Material>> listMaterials();

        //adds to or creates a material, might be better renamed or split
        void addMaterial(std::string mat_type, unsigned int quantity);

        //deletes a material entirely
        void deleteMaterial(std::string mat_type);
};

#endif