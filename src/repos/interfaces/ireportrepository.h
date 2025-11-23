#ifndef IREPORTREPOSITORY_H
#define IREPORTREPOSITORY_H

#include <map>
#include <memory>

template <typename ReportT>
class IReportManager {
    public:
        IReportManager() = default;
        virtual ~IReportManager() = default;

        virtual int addReport(std::shared_ptr<ReportT> report) = 0;

        virtual void editReport (int reportid, std::shared_ptr<ReportT> updatedReport) = 0;

        virtual void deleteReport(int reportid) = 0;
};

#endif