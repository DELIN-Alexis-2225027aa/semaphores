#include "src/Analysts.h"
#include "src/Incident.h"
#include "src/SyncTools.h"
#include <thread>
#include <iostream>

int main() {
    SyncTools syncTools;

    std::thread analyst(&Analysts::processIncident, Analysts(syncTools));

    std::thread incidents[10];
    for (int i = 0; i < 10; ++i) {
        incidents[i] = std::thread(&Incident::handleIncident, Incident(syncTools, i + 1));
    }

    for (int i = 0; i < 10; ++i) {
        incidents[i].join();
    }

    analyst.join();

    return 0;
}
