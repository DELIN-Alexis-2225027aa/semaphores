#ifndef ANALYSTS_H
#define ANALYST_H

#include "SyncTools.h"

class Analysts {
public:
    Analysts(SyncTools& syncTools);
    void processIncident();

private:
    SyncTools& syncTools;
};

#endif
