#include "Analyst.h"
#include "Incident.h"
#include "SyncTools.h"
#include <thread>
#include <iostream>

int main() {
    SyncTools syncTools;

    // Lancer 1 analyste
    std::thread analyst(&Analyst::processIncident, Analyst(syncTools));

    // Lancer 10 incidents en boucle continue
    std::thread incidents[10];
    for (int i = 0; i < 10; ++i) {
        incidents[i] = std::thread(&Incident::handleIncident, Incident(syncTools, i + 1));  // Identifiant unique pour chaque incident
    }

    // Continuer à ajouter des incidents après traitement
    for (int i = 0; i < 10; ++i) {
        incidents[i].join();  // Joindre les incidents au fur et à mesure
    }

    // Les threads ne doivent pas s'arrêter
    analyst.join();

    return 0;
}
