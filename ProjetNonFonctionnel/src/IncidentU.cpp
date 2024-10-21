#include "IncidentU.h"
#include <iostream>
#include <thread>
#include <chrono>

IncidentU::IncidentU(SyncToolsU &syncTools, int id) : syncTools(syncTools), incidentID(id) {}

void IncidentU::handleIncident() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Incident " << incidentID << " pret a etre traite." << std::endl;
    syncTools.signalIncidentReady(incidentID);

    syncTools.waitIncidentDone();
    std::cout << "Incident " << incidentID << " totalement traite." << std::endl;
}
