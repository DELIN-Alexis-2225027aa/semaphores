#include "AnalystU.h"
#include <iostream>
#include <thread>
#include <chrono>

AnalystU::AnalystU(SyncToolsU &syncTools) : syncTools(syncTools) {}

void AnalystU::processIncident() {
    while (true) {
        syncTools.waitIncidentReady();  // L'analyste attend qu'un incident soit prêt

        int incidentId = syncTools.getIncidentId();
        std::cout << "Analyste traite l'incident " << incidentId << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simuler le traitement d'un incident

        syncTools.signalIncidentDone();
        std::cout << "Incident " << incidentId << " traite." << std::endl;
    }
}