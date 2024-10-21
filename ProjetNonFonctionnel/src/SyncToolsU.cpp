#include "SyncToolsU.h"
#include <iostream>

SyncToolsU::SyncToolsU() : currentIncidentId(0) {
    sem_init(&incidentQueue, 0, 0);
    sem_init(&incidentDone, 0, 0);
}

void SyncToolsU::signalIncidentReady(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    if (id == 1) {
        currentIncidentId = id;
        std::cout << "Incident " << id << " prioritaire pret." << std::endl;
        sem_post(&incidentQueue);
    } else {
        std::cout << "Incident " << id << " est en attente, non traité." << std::endl;
    }
}

void SyncToolsU::waitIncidentReady() {
    sem_wait(&incidentQueue);
}

int SyncToolsU::getIncidentId() {
    std::lock_guard<std::mutex> lock(mtx);
    return currentIncidentId;
}

void SyncToolsU::signalIncidentDone() {
    sem_post(&incidentDone);
}

void SyncToolsU::waitIncidentDone() {
    sem_wait(&incidentDone);
}
