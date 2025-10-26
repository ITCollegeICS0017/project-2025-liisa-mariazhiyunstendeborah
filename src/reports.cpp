#include "reports.h"

Report::Report(int creator_id) : creator_id(creator_id) {
    auto now = std::chrono::system_clock::now();
    date_created = std::chrono::floor<std::chrono::days>(now);
}

void Report::saveReport() {
    //In case we need to save it as a pdf or other.
    return;
}


void PhotoReport::addConsumedMaterial(std::string mat_type, int quantity) {
    //I: should I add another check for instock being 0 or
    //negative here? don't think so
    consumed_materials[mat_type] += quantity;
}
