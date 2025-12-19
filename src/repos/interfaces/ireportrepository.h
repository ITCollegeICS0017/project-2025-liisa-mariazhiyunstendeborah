#ifndef IREPORTREPOSITORY_H
#define IREPORTREPOSITORY_H

#include <map>
#include <memory>

//Report repository, sets report ids, performs CRUD operations, finds reports by their id
template <typename ReportT>
class IReportRepository {
    public:
        IReportRepository() = default;
        virtual ~IReportRepository() = default;

        virtual int addReport(std::shared_ptr<ReportT> report) = 0;

        virtual void editReport (int reportid, std::shared_ptr<ReportT> updatedReport) = 0;

        virtual void deleteReport(int reportid) = 0;
};

#endif