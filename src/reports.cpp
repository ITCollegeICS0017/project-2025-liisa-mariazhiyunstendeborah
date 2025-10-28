#include "reports.h"

Report::Report(int creator_id, IClock& clock) : creator_id(creator_id), clock(clock) {
    auto now = clock.now();
    date_created = std::chrono::floor<std::chrono::days>(now);
}

void Report::saveReport() {
    //In case we need to save it as a pdf or other.
    return;
}
