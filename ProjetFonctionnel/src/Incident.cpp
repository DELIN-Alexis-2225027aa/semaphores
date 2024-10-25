#include "Incident.h"
#include <iostream>
#include <thread>
#include <chrono>

Incident::Incident(SyncTools &syncTools, int id) : syncTools(syncTools), incidentID(id) {}

void Incident::handleIncident() {
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Incident " << incidentID << " pret a etre traite." << std::endl;
    syncTools.signalIncidentReady(incidentID);

    syncTools.waitIncidentDone();
    std::cout << "Incident " << incidentID << " totalement traite." << std::endl;
}
