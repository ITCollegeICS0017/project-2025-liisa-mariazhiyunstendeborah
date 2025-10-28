#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <map>
#include <memory>
#include "reports.h"

template <typename ReportT>
class ReportManager {
    protected:
        int next_id = 1;

    public:
		std::map<int, std::shared_ptr<ReportT>> reports;

        ReportManager() = default;
        virtual ~ReportManager() = default;

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
    //E:
    return nullptr;
}

template <typename ReportT>
int ReportManager<ReportT>::addReport(std::shared_ptr<ReportT> report) {
    int reportid = next_id++;
    report->reportid = reportid;
    reports.insert({reportid, report});
    return reportid;
}

template <typename ReportT>
void ReportManager<ReportT>::editReport (int reportid, std::shared_ptr<ReportT> updatedReport) {
    //E: if reportid not ofund for example
    reports.at(reportid) = updatedReport;
}

template <typename ReportT>
void ReportManager<ReportT>::deleteReport(int reportid) {
    //E: e.g. if reportid not found
    reports.erase(reportid);
}

class ReceptReportManager : public ReportManager<ReceptReport> {
};

class PhotoReportManager : public ReportManager<PhotoReport> {
};

#endif
