#ifndef PHOTOGRAPHER_H
#define PHOTOGRAPHER_H

#include "core/employee.h"
#include "utilities/exceptions.h"

//employee photographer, that can progress on and complete orders, consume materials and submit photographer reports
class Photographer: public Employee {
    private:
        IClock *clock;
        //program-wide up-to-date material repository
        MaterialRepository* material_repository;
        PhotoReportRepository* photoreport_repository;
        //photographer-specific material repository that rather than storing the materials' amount in stock, stores how much of it was consumed
        MaterialRepository* consumed_materials;
        
    public:
        Photographer(OrderRepository* order_repository, std::string emp_name, IClock *clock, MaterialRepository* material_repository, 
        PhotoReportRepository* photoreport_repository) : Employee(order_repository, emp_name), clock(clock), material_repository(material_repository), photoreport_repository(photoreport_repository) {
            this->consumed_materials = new MaterialRepository();
        }

        //Used only during XML reading
        Photographer(OrderRepository* order_repository, int emp_id, std::string emp_name, IClock *clock, MaterialRepository* material_repository, 
        PhotoReportRepository* photoreport_repository) : Employee(order_repository, emp_id, emp_name), 
        clock(clock), material_repository(material_repository), photoreport_repository(photoreport_repository) {
            this->consumed_materials = new MaterialRepository();
        }

        //custom destructor to make sure consumed_materials is destroyed
        ~Photographer() override;   

        //returns photographer's class name
        std::string getEmpType();

        //changes order status based on input
        void switchOrderStatus(Order* changedorder, CompletionStatus compl_status);

        //adds a material to the photographer-specific material repository of consumed materials, used in submitReport()
        void consumeMaterial(std::string mat_type, unsigned int quantity);

        //returns photographer-specific material repository of consumed materials
        std::map<std::shared_ptr<Material>, int> getConsumedMaterials();

        //creates and adds a report to the photographer report repository
        //currently does not consider date of creation but likely should in future so as to avoid submitting old completed orders
        int submitReport();
};


#endif
