#ifndef SYNCTOOLS_H
#define SYNCTOOLS_H

#include <semaphore.h>
#include <mutex>

class SyncTools {
public:
    SyncTools();
    void signalIncidentReady(int id);
    void waitIncidentReady();
    void signalIncidentDone();
    void waitIncidentDone();
    int getIncidentId();

private:
    std::mutex mtx;
    sem_t incidentQueue;
    sem_t incidentDone;
    int currentIncidentId;
};

#endif // SYNCTOOLS_H
