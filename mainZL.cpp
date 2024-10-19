#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h> //pour fct sleep()
#include <mutex>

#define NB_CHAISES 5

sem_t barbierPret;   //barbier pre^t
sem_t clientPret;    //Client prêt
sem_t clientFini;    //Client a fini
sem_t barbierFini;   //Barbier a fini coupe de cheveux
std::mutex accessChaises; //protection de l'accès aux chaises

int clientsEnAttente = 0;

void client(int id) {

    std::unique_lock<std::mutex> lock(accessChaises);

    if (clientsEnAttente == NB_CHAISES) {
        std::cout << "Client " << id << " part car il n'y a pas de chaise disponible.\n";
        return;
    }

    clientsEnAttente++;
    std::cout << "Client " << id << " attend. Clients en attente : " << clientsEnAttente << "\n";

    sem_post(&clientPret);
    lock.unlock();

    sem_wait(&barbierPret);
    std::cout << "Client " << id << " se fait couper les cheveux.\n";

    sem_post(&clientFini);
    sem_wait(&barbierFini);
    std::cout << "Client " << id << " a terminé sa coupe de cheveux.\n";
}

void barbier() {
    while (true) {
        std::cout << "Le barbier attend des clients...\n";
        sem_wait(&clientPret);  // Attend qu'un client arrive

        std::unique_lock<std::mutex> lock(accessChaises);
        clientsEnAttente--;
        std::cout << "Le barbier coupe les cheveux. Clients en attente : " << clientsEnAttente << "\n";
        lock.unlock();

        sem_post(&barbierPret);

        sleep(6);  //délai coupe cheveux

        sem_wait(&clientFini);
        std::cout << "Le barbier a terminé la coupe.\n";
        sem_post(&barbierFini);
    }
}

int main() {
    // init
    sem_init(&barbierPret, 0, 0);
    sem_init(&clientPret, 0, 0);
    sem_init(&clientFini, 0, 0);
    sem_init(&barbierFini, 0, 0);

    std::thread threadBarbier(barbier);

    std::thread clients[10];
    for (int i = 0; i < 10; i++) {
        clients[i] = std::thread(client, i);
        sleep(4); //délai arrivage client
    }

    for (int i = 0; i < 10; i++) {
        clients[i].join();
    }

    threadBarbier.join();

    // destruction semaphore mais pas obligé
    sem_destroy(&barbierPret);
    sem_destroy(&clientPret);
    sem_destroy(&clientFini);
    sem_destroy(&barbierFini);

    return 0;
}
