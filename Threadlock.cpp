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
    connexionDispo.acquire();  // Un employé prend une connexion disponible

    std::unique_lock<std::mutex> lock(accessConnexions);

    if (connexionsEnCours == NB_CONNEXIONS) {
        std::cout << "Employé " << id << " attend qu'une connexion se libère.\n";
        connexionDispo.release();
        lock.unlock();
        return;
    }

    connexionsEnCours++;
    std::cout << "Employé " << id << " se connecte au serveur. Connexions actives : " << connexionsEnCours << "\n";

    // Uniquement si c'est le seul employé connecté, il peut télécharger un fichier
    if (connexionsEnCours == 1) {
        lock.unlock();  // Libérer le mutex pendant l'attente du serveur

        serveurPret.release();  // Notifier le gestionnaire que l'employé attend un fichier
        fichierPret.acquire();  // Attendre que le fichier soit prêt

        std::cout << "Employé " << id << " télécharge le fichier.\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));

        lock.lock();  // Reprendre le verrou après le téléchargement
        std::cout << "Employé " << id << " a terminé le téléchargement.\n";
    } else {
        std::cout << "Employé " << id << " est connecté mais ne peut pas télécharger, car il n'est pas seul.\n";
    }

    connexionsEnCours--;
    std::cout << "Employé " << id << " se déconnecte. Connexions actives : " << connexionsEnCours << "\n";

    lock.unlock();
    connexionDispo.release();  // Libérer une connexion
}

void gestionnaireServeur() {
    while (true) {
        serveurPret.acquire();  // Attendre qu'un employé demande un fichier

        std::cout << "Le gestionnaire prépare un fichier.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        fichierPret.release();  // Fichier prêt pour l'employé
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
