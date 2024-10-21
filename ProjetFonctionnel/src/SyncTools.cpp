#include "SyncTools.h"
#include <iostream>

SyncTools::SyncTools() : currentIncidentId(0) {
    sem_init(&incidentQueue, 0, 0);
    sem_init(&incidentDone, 0, 0);
}

void SyncTools::signalIncidentReady(int id) {
    std::lock_guard<std::mutex> lock(mtx);
    currentIncidentId = id;
    std::cout << "Incident " << id << " prêt." << std::endl;
    sem_post(&incidentQueue);
}

void SyncTools::waitIncidentReady() {
    sem_wait(&incidentQueue);
}

int SyncTools::getIncidentId() {
    std::lock_guard<std::mutex> lock(mtx);
    return currentIncidentId;
}

void SyncTools::signalIncidentDone() {
    sem_post(&incidentDone);
}

void SyncTools::waitIncidentDone() {
    sem_wait(&incidentDone);
}
