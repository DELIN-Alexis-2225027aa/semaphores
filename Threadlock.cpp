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

    {
        std::unique_lock<std::mutex> lock(accessConnexions);
        connexionsEnCours++;
        std::cout << "Employé " << id << " se connecte au serveur. Connexions actives : " << connexionsEnCours << "\n";
    }

    {
        std::unique_lock<std::mutex> lock(accessConnexions);
        while (connexionsEnCours != 1) {
            std::cout << "Employé " << id << " attend d'être le seul sur la connexion.\n";
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));  
            lock.lock();
        }
    }

    serveurPret.release();
    fichierPret.acquire();

    std::cout << "Employé " << id << " télécharge le fichier.\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));

    {
        std::unique_lock<std::mutex> lock(accessConnexions);
        connexionsEnCours--;
        std::cout << "Employé " << id << " a terminé le téléchargement. Connexions actives : " << connexionsEnCours << "\n";
    }

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

    std::thread employes[10];
    for (int i = 0; i < 10; i++) {
        employes[i] = std::thread(employe, i);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    for (int i = 0; i < 10; i++) {
        employes[i].join();
    }

    threadGestionnaire.join();

    return 0;
}
