#include "src/IncidentU.h"
#include "src/AnalystU.h"
#include "src/SyncToolsU.h"
#include <thread>

int main() {
    SyncToolsU syncTools;
    std::thread analyst(&AnalystU::processIncident, AnalystU(syncTools));
    std::thread incidents[10];
    for (int i = 0; i < 10; ++i) {incidents[i] = std::thread(&IncidentU::handleIncident, IncidentU(syncTools, i + 1));  }
    for (int i = 0; i < 10; ++i) { incidents[i].join(); analyst.join(); return 0;}
}
