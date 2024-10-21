#include "Analysts.h"
#include "SyncTools.h"
#include <iostream>
#include <thread>
#include <chrono>

Analysts::Analysts(SyncTools &syncTools) : syncTools(syncTools) {}

void Analysts::processIncident() {
    while (true) {
        syncTools.waitIncidentReady();

        int incidentId = syncTools.getIncidentId();
        std::cout << "Analyste traite l incident " << incidentId << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        syncTools.signalIncidentDone();
        std::cout << "Incident " << incidentId << " traite." << std::endl;
    }
}
