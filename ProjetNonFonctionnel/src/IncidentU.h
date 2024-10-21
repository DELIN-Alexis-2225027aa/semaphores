#ifndef INCIDENT_H
#define INCIDENT_H

#include "SyncToolsU.h"

class IncidentU {
public:
    IncidentU(SyncToolsU& syncTools, int id);
    void handleIncident();

private:
    SyncToolsU& syncTools;
    int incidentID;
};

#endif // INCIDENT_H
