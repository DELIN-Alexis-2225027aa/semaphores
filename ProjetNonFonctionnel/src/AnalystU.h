#ifndef ANALYST_H_
#define ANALYST_H_

#include "SyncToolsU.h"

class AnalystU {
public:
    explicit AnalystU(SyncToolsU& syncTools);
    void processIncident();

private:
    SyncToolsU& syncTools;
};

#endif // ANALYST_H_
