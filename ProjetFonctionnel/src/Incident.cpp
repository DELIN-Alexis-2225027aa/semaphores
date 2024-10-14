#include "Incident.h"
#include <iostream>
#include <thread>
#include <chrono>

Incident::Incident(SyncTools &syncTools, int id) : syncTools(syncTools), incidentID(id) {}

// Fonction pour gérer l'incident
void Incident::handleIncident() {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Simuler l'arrivée d'un incident

    std::cout << "Incident " << incidentID << " pret a etre traite." << std::endl;
    syncTools.signalIncidentReady(incidentID);  // Passer l'identifiant de l'incident

    // Attendre que l'incident soit entièrement traité
    syncTools.waitIncidentDone();
    std::cout << "Incident " << incidentID << " totalement traite." << std::endl;
}
