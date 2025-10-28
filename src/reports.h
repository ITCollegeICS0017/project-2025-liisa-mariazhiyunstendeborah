#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <map>
#include <memory>
#include "order.h"
#include "material.h"
#include "clocks.h"

class Report {
    public:
        int reportid = 0;
        int creator_id;
        IClock& clock;
        std::chrono::year_month_day date_created;

        Report(int creator_id, IClock& clock);

        virtual ~Report() = default;
};

class ReceptReport : public Report {
    public:
        std::map<int, std::shared_ptr<Order>> compl_orders;
        int total_revenue;

        ReceptReport(int creator_id, IClock& clock, std::map<int, std::shared_ptr<Order>> compl_orders, int total_revenue) : Report(creator_id, clock), compl_orders(compl_orders), total_revenue(total_revenue) { }

};

class PhotoReport : public Report{
    public:
        std::map<std::shared_ptr<Material>, int> consumed_materials;

        PhotoReport(int creator_id, IClock& clock, std::map<std::shared_ptr<Material>, int> consumed_materials) : Report(creator_id, clock), consumed_materials(consumed_materials) { }
};

#endif
