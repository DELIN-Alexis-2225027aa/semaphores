#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <mutex>

#define NB_CONNEXIONS 5

sem_t serveurPret;
sem_t connexionDispo;
sem_t fichierPret;
std::mutex accessConnexions;

int connexionsEnCours = 0;

void employe(int id) {
    sem_wait(&connexionDispo);

    std::unique_lock<std::mutex> lock(accessConnexions);

    if (connexionsEnCours == NB_CONNEXIONS) {
        std::cout << "Employe" << id << " attend qu'une connexion se libere.\n";
        sem_post(&connexionDispo);
        lock.unlock();
        return;
    }

    connexionsEnCours++;
    std::cout << "Employe " << id << " se connecte au serveur. Connexions actives : " << connexionsEnCours << "\n";

    lock.unlock();

    sem_post(&serveurPret);

    sem_wait(&fichierPret);
    std::cout << "Employe " << id << " telecharge le fichier.\n";

    sleep(5);

    lock.lock();
    connexionsEnCours--;
    std::cout << "Employe " << id << " a termine le téléchargement. Connexions actives : " << connexionsEnCours << "\n";
    lock.unlock();

    sem_post(&connexionDispo);
}

void gestionnaireServeur() {
    while (true) {
        sem_wait(&serveurPret);

        std::cout << "Le gestionnaire prepare un fichier.\n";
        sleep(5);

        sem_post(&fichierPret);
        std::cout << "Le gestionnaire a prepare un fichier.\n";
    }
}

int main() {
    sem_init(&serveurPret, 0, 0);
    sem_init(&connexionDispo, 0, NB_CONNEXIONS);
    sem_init(&fichierPret, 0, 0);

    std::thread threadGestionnaire(gestionnaireServeur);

    std::thread employes[10];
    for (int i = 0; i < 10; i++) {
        employes[i] = std::thread(employe, i);
        sleep(1);
    }

    for (int i = 0; i < 10; i++) {
        employes[i].join();
    }

    sem_destroy(&serveurPret);
    sem_destroy(&connexionDispo);
    sem_destroy(&fichierPret);

    return 0;
}
