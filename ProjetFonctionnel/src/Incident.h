#ifndef INCIDENT_H
#define INCIDENT_H

#include "SyncTools.h"

class Incident {
public:
    Incident(SyncTools& syncTools, int id);
    void handleIncident();

private:
    SyncTools& syncTools;
    int incidentID;
};

#endif // INCIDENT_H
