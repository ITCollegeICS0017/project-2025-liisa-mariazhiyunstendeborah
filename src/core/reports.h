#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <map>
#include <memory>
#include "order.h"
#include "material.h"
#include "utilities/clocks.h"

//abstract report class
class Report {
    public:
        //reportid set to a valid value once added to a corresponding report repository
        int reportid = 0;
        //creator_id is the emp_id of the employee who created it
        int creator_id;
        IClock& clock;
        std::chrono::year_month_day date_created;

        Report(int creator_id, IClock& clock);

        virtual ~Report() = default;
};

//receptionist's reports, meant to report completed orders of a day + the total revenue from them
//created using the Receptionist.submitReport()
class ReceptReport : public Report {
    public:
        //map of completed orders
        std::map<int, std::shared_ptr<Order>> compl_orders;
        int total_revenue;

        ReceptReport(int creator_id, IClock& clock, std::map<int, std::shared_ptr<Order>> compl_orders, int total_revenue) : Report(creator_id, clock), compl_orders(compl_orders), total_revenue(total_revenue) { }

};

//photographer's reports, meant to report on consumed materials (not attached to any specific order)
//created using the Photographer.submitReport() and the Photographer's temporary photoreport_repository
class PhotoReport : public Report{
    public:
        //map of consumed materials that stores the material consumed and its total quantity consumed
        std::map<std::shared_ptr<Material>, int> consumed_materials;

        PhotoReport(int creator_id, IClock& clock, std::map<std::shared_ptr<Material>, int> consumed_materials) : Report(creator_id, clock), consumed_materials(consumed_materials) { }
};

#endif
