#include "Analyst.h"
#include <iostream>
#include <thread>
#include <chrono>

Analyst::Analyst(SyncTools &syncTools) : syncTools(syncTools) {}

void Analyst::processIncident() {
    while (true) {
        syncTools.waitIncidentReady();  // L'analyste attend qu'un incident soit prêt

        // Récupérer l'identifiant de l'incident prêt
        int incidentId = syncTools.getIncidentId();

        std::cout << "Analyste traite l'incident " << incidentId << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simuler le traitement d'un incident

        // Signaler que l'incident a été traité
        syncTools.signalIncidentDone();
        std::cout << "Incident " << incidentId << " traite." << std::endl;
    }
}
