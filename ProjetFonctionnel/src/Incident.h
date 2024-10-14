#ifndef INCIDENT_H
#define INCIDENT_H

#include "SyncTools.h"

class Incident {
public:
    Incident(SyncTools& syncTools, int id);  // Ajouter un identifiant unique
    void handleIncident();

private:
    SyncTools& syncTools;
    int incidentID;  // Identifiant de l'incident
};

#endif // INCIDENT_H
