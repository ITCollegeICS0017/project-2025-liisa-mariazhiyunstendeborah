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
        std::string emp_name;

        Employee(OrderManager* order_manager, std::string emp_name) : order_manager(order_manager), emp_name(emp_name) { }

        virtual std::string getEmpType() = 0;

        virtual ~Employee() = default;
};


//Note: most likely, when there are no employees, the
//first employee should always be the administrator

class ReceptReportManager;
class Receptionist: public Employee {
    private:
        ReceptReportManager* receptreport_manager;

    public:
        Receptionist(OrderManager* order_manager, std::string emp_name, ReceptReportManager* receptreport_manager) : Employee(order_manager, emp_name), receptreport_manager(receptreport_manager) { }

        std::string getEmpType();

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
        MaterialManager* consumed_materials;

    public:
        Photographer(OrderManager* order_manager, std::string emp_name, MaterialManager* material_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager, emp_name), material_manager(material_manager), photoreport_manager(photoreport_manager) {
            this->consumed_materials = new MaterialManager();
 }

        std::string getEmpType();

        void switchOrderStatus(Order* changedorder, CompletionStatus compl_status);

        void consumeMaterial(std::shared_ptr<Material> material, int quantity);

        std::map<std::shared_ptr<Material>, int> getConsumedMaterials();

        int submitReport(int emp_id);

        ~Photographer() override;
};


class Administrator: public Employee {
    private:
        MaterialManager* material_manager;
        ReceptReportManager* receptreport_manager;
        PhotoReportManager* photoreport_manager;

    public:
        Administrator(OrderManager* order_manager, std::string emp_name, MaterialManager* material_manager, ReceptReportManager* receptreport_manager, PhotoReportManager* photoreport_manager) : Employee(order_manager, emp_name), material_manager(material_manager), receptreport_manager(receptreport_manager), photoreport_manager(photoreport_manager) { }

        std::string getEmpType();

        std::map<int, std::shared_ptr<ReceptReport>> listReceptReports();

        std::map<int, std::shared_ptr<PhotoReport>> listPhotoReports();

        std::vector<std::shared_ptr<Material>> listMaterials();

        void addMaterial(std::shared_ptr<Material> material, int quantity);

        void removeMaterial(std::string mat_type);
};

#endif
