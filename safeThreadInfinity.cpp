#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <chrono>

#define NB_CONNEXIONS 5

std::binary_semaphore serveurPret(0);
std::counting_semaphore<NB_CONNEXIONS> connexionDispo(NB_CONNEXIONS);
std::binary_semaphore fichierPret(0);
std::mutex accessConnexions;

int connexionsEnCours = 0;

void employe(int id) {
    connexionDispo.acquire();

    std::unique_lock<std::mutex> lock(accessConnexions);

    if (connexionsEnCours == NB_CONNEXIONS) {
        std::cout << "Employé " << id << " attend qu'une connexion se libère.\n";
        connexionDispo.release();
        lock.unlock();
        return;
    }

    connexionsEnCours++;
    std::cout << "Employé " << id << " se connecte au serveur. Connexions actives : " << connexionsEnCours << "\n";

    lock.unlock();

    serveurPret.release();

    fichierPret.acquire();
    std::cout << "Employé " << id << " télécharge le fichier.\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));

    lock.lock();
    connexionsEnCours--;
    std::cout << "Employé " << id << " a terminé le téléchargement. Connexions actives : " << connexionsEnCours << "\n";
    lock.unlock();

    connexionDispo.release();
}

void gestionnaireServeur() {
    while (true) {
        serveurPret.acquire();

        std::cout << "Le gestionnaire prépare un fichier.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        fichierPret.release();
        std::cout << "Le gestionnaire a préparé un fichier.\n";
    }
}

int main() {
    std::thread threadGestionnaire(gestionnaireServeur);

    std::thread employes[1000];
    int i =0;
    while (true) {
        employes[i] = std::thread(employe, i);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        i++;
    }

    while (true) {
        employes[i].join();
        i++;
    }

    threadGestionnaire.join();

    return 0;
}