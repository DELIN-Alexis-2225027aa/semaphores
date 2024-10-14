#ifndef SYNCTOOLS_H
#define SYNCTOOLS_H

#include <semaphore.h>
#include <mutex>

class SyncTools {
public:
    SyncTools();
    void signalIncidentReady(int id);   // Signaler qu'un incident est prêt avec son identifiant
    void waitIncidentReady();           // L'analyste attend qu'un incident soit prêt
    void signalIncidentDone();          // Signaler que l'incident est terminé
    void waitIncidentDone();            // L'analyste attend la fin du traitement de l'incident
    int getIncidentId();                // Récupérer l'identifiant de l'incident

private:
    std::mutex mtx;               // Mutex pour protéger l'accès aux données partagées
    sem_t incidentQueue;          // Sémaphore pour gérer la file d'incidents prêts
    sem_t incidentDone;           // Sémaphore pour signaler la fin du traitement de l'incident
    int incidentCount;            // Compteur d'incidents
    int currentIncidentId;        // Identifiant de l'incident actuellement prêt à être traité
};

#endif // SYNCTOOLS_H
