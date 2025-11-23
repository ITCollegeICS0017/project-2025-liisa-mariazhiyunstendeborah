#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include "interfaces/ireportmanager.h"
#include "core/reports.h"

template <typename ReportT>
class ReportManager {
    protected:
        int next_id = 1;

    public:
		std::map<int, std::shared_ptr<ReportT>> reports;

        ReportT* findReport(int reportid);

        //Additional function to find reports by creator_id can be added if necessary.

        int addReport(std::shared_ptr<ReportT> report);

        void editReport (int reportid, std::shared_ptr<ReportT> updatedReport);

        void deleteReport(int reportid);
};
template <typename ReportT>
ReportT* ReportManager<ReportT>::findReport(int reportid) {
    auto iter = reports.find(reportid);
    if (iter != reports.end()) {
        return iter->second.get();
    }
    return nullptr;
}

template <typename ReportT>
int ReportManager<ReportT>::addReport(std::shared_ptr<ReportT> report) {
    if (report->reportid == 0) {
        int reportid = next_id++;
        report->reportid = reportid;
        reports.insert({reportid, report});
        return reportid;
    } else {
        throw std::invalid_argument("Report already exists!");
    }
}

template <typename ReportT>
void ReportManager<ReportT>::editReport (int reportid, std::shared_ptr<ReportT> updatedReport) {
    if (!findReport(reportid)) {
        throw std::invalid_argument("Report not found!");
    } else {
        reports.at(reportid) = updatedReport;
    }
}

template <typename ReportT>
void ReportManager<ReportT>::deleteReport(int reportid) {
    if (!findReport(reportid)) {
        throw std::invalid_argument("Report does not exist to be deleted!");
    } else {
    //E: e.g. if reportid not found
        reports.erase(reportid);
    }
}

class ReceptReportManager : public ReportManager<ReceptReport> {
};

class PhotoReportManager : public ReportManager<PhotoReport> {
};

#endif
