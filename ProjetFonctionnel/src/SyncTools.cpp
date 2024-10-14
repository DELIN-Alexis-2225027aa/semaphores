#include "SyncTools.h"
#include <iostream>

SyncTools::SyncTools() : incidentCount(0), currentIncidentId(0) {
    sem_init(&incidentQueue, 0, 0);  // Initialiser le sémaphore pour les incidents en attente
    sem_init(&incidentDone, 0, 0);   // Initialiser le sémaphore pour la fin des incidents
}

// Signaler qu'un incident est prêt à être traité, avec son identifiant
void SyncTools::signalIncidentReady(int id) {
    std::lock_guard<std::mutex> lock(mtx);  // Protéger le compteur avec un mutex
    incidentCount++;
    currentIncidentId = id;  // Stocker l'identifiant de l'incident en cours
    std::cout << "Incident " << id << " pret. Nombre d'incidents en attente : " << incidentCount << std::endl;
    sem_post(&incidentQueue);  // Libérer un analyste pour traiter l'incident
}

// Attendre qu'un incident soit prêt pour traitement
void SyncTools::waitIncidentReady() {
    sem_wait(&incidentQueue);  // L'analyste attend qu'un incident soit prêt
}

// Récupérer l'identifiant de l'incident en cours de traitement
int SyncTools::getIncidentId() {
    std::lock_guard<std::mutex> lock(mtx);  // Protéger l'accès avec un mutex
    return currentIncidentId;
}

// Signaler que l'incident est terminé
void SyncTools::signalIncidentDone() {
    sem_post(&incidentDone);  // Signaler que l'incident a été traité
}

// Attendre que l'incident ait été traité
void SyncTools::waitIncidentDone() {
    sem_wait(&incidentDone);  // L'analyste attend que l'incident soit traité
}
