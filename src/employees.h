#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include "order.h"
#include "material.h"
#include "reports.h"
#include "ordermanager.h"
#include "reportmanager.h"
#include "materialmanager.h"

class OrderManager;

class Employee {
    protected:
        OrderManager* order_manager;

    public:
        Employee(OrderManager* order_manager) : order_manager(order_manager) { }
//Todo: Add getEmpType() that returns the employee type in string (case-sensitive!)
//Todo:
        virtual ~Employee() = default;
};


//Note: most likely, when there are no employees, the
//first employee should always be the administrator

class ReceptReportManager;
class Receptionist: public Employee {
    private:
        ReceptReportManager* receptreport_manager;

    public:
        Receptionist(OrderManager* order_manager, ReceptReportManager* receptreport_manager) : Employee(order_manager), receptreport_manager(receptreport_manager) { }

        int makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days);

        void assignOrder(Order* assign, int emp_id);

        int submitReport(int emp_id);
};

class MaterialManager;
class PhotoReportManager;
class Photographer: public Employee {
    private:
        MaterialManager* material_manager;
        PhotoReportManager* photoreport_manager;
        std::map<std::shared_ptr<Material>, int> consumed_materials;

    public:
        Photographer(OrderManager* order_manager, MaterialManager* material_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager), material_manager(material_manager), photoreport_manager(photoreport_manager) { }

        void switchOrderStatus(Order* changedorder, CompletionStatus compl_status);

        void consumeMaterial(std::shared_ptr<Material> material, int quantity);

        const std::map<std::shared_ptr<Material>, int>& getConsumedMaterials();

        int submitReport(int emp_id);
};


class Administrator: public Employee {
    private:
        MaterialManager* material_manager;
        ReceptReportManager* receptreport_manager;
        PhotoReportManager* photoreport_manager;

    public:
    Administrator(OrderManager* order_manager, MaterialManager* material_manager, ReceptReportManager* receptreport_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager), material_manager(material_manager), receptreport_manager(receptreport_manager), photoreport_manager(photoreport_manager) { }

    std::map<int, std::shared_ptr<ReceptReport>> listReceptReports();

    std::map<int, std::shared_ptr<PhotoReport>> listPhotoReports();

    std::vector<std::shared_ptr<Material>> listMaterials();

    void addMaterial(std::string mat_type, int quantity);

    void removeMaterial(std::string mat_type);
};

#endif
