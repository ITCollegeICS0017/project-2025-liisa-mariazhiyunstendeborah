#ifndef REPORTREPOSITORY_H
#define REPORTREPOSITORY_H

#include "interfaces/ireportrepository.h"
#include "core/reports.h"
#include "utilities/exceptions.h"

template <typename ReportT>
class ReportRepository : public IReportRepository<ReportT> {
    protected:
        //ids are set incrementally starting from next_id
        int next_id = 1;

    public:
		std::map<int, std::shared_ptr<ReportT>> reports;

        ReportT* findReport(int reportid);

        //Additional function to find reports by creator_id can be added if necessary.

        int addReport(std::shared_ptr<ReportT> report);

        void editReport (int reportid, std::shared_ptr<ReportT> updatedReport);

        void deleteReport(int reportid);
};

//returns nullptr rather than an error, as that makes it easier to use it to check if a report exists
template <typename ReportT>
ReportT* ReportRepository<ReportT>::findReport(int reportid) {
    auto iter = reports.find(reportid);
    if (iter != reports.end()) {
        return iter->second.get();
    }
    return nullptr;
}

//checks if a report's default id has been changed, if so it sets the report's id to next_id (which is then incremented) and adds it to the report repository
//if the above is false, throws an error
template <typename ReportT>
int ReportRepository<ReportT>::addReport(std::shared_ptr<ReportT> report) {
    if (report->reportid == 0) {
        int reportid = next_id++;
        report->reportid = reportid;
        reports.insert({reportid, report});
        return reportid;
    } else {
        throw DuplicateObjectException("Report with ID: " + std::to_string(report->reportid));
    }
}

template <typename ReportT>
void ReportRepository<ReportT>::editReport (int reportid, std::shared_ptr<ReportT> updatedReport) {
    if (!findReport(reportid)) {
        throw MissingObjectException("Report with ID: " + std::to_string(reportid));
    } else {
        reports.at(reportid) = updatedReport;
    }
}

template <typename ReportT>
void ReportRepository<ReportT>::deleteReport(int reportid) {
    if (!findReport(reportid)) {
        throw MissingObjectException("Report with ID: " + std::to_string(reportid));
    } else {
        reports.erase(reportid);
    }
}

class ReceptReportRepository : public ReportRepository<ReceptReport> {
};

class PhotoReportRepository : public ReportRepository<PhotoReport> {
};

#endif
