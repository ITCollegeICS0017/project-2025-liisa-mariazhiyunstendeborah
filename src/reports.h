#ifndef REPORTS_H
#define REPORTS_H

#include <string>
#include <map>
#include <memory>
#include "order.h"

class Report {
    public:
        int creator_id;
        std::chrono::year_month_day date_created;

        Report(int creator_id);

        virtual ~Report() = default;

        //to be defined if need be
        virtual void saveReport();
};

class ReceptReport : public Report {
    public:
        std::map<int, std::shared_ptr<Order>> compl_orders;
        int total_revenue;

        ReceptReport(int creator_id, std::map<int, std::shared_ptr<Order>> compl_orders, int total_revenue) : Report(creator_id), compl_orders(compl_orders), total_revenue(total_revenue) { }

};

class PhotoReport : public Report{
    public:
        std::map<std::string, int> consumed_materials;
        //I: date created

        PhotoReport(int creator_id, const std::map<std::string, int>& consumed_materials) : Report(creator_id), consumed_materials(consumed_materials) { }

        void addConsumedMaterial(std::string mat_type, int quantity);
};

#endif
