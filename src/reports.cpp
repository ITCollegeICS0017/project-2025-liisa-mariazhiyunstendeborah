#include "reports.h"

Report::Report(int creator_id) : creator_id(creator_id) {
    auto now = std::chrono::system_clock::now();
    date_created = std::chrono::floor<std::chrono::days>(now);
}

void Report::saveReport() {
    //In case we need to save it as a pdf or other.
    return;
}
