#ifndef ANALYST_H_
#define ANALYST_H_

#include "SyncTools.h"

class Analyst {
public:
    Analyst(SyncTools& syncTools);
    void processIncident();

private:
    SyncTools& syncTools;
};

#endif // ANALYST_H_
