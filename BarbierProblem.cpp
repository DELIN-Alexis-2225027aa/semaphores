#include <iostream>
#include <thread>
#include <semaphore>
#include <mutex>
#include <chrono>

#define NB_CHAISES 5

std::counting_semaphore<NB_CHAISES> chaisesDispo(NB_CHAISES);
std::binary_semaphore barbierPret(0);
std::binary_semaphore clientFini(0);
std::binary_semaphore barbierFini(0);
std::mutex mutexChaises;

int clientsEnAttente = 0;

void client(int id) {
    if (chaisesDispo.try_acquire()) {
        std::unique_lock<std::mutex> lock(mutexChaises);
        clientsEnAttente++;
        std::cout << "Client " << id << " attend. Clients en attente : " << clientsEnAttente << "\n";
        lock.unlock();

        barbierPret.release();
        barbierFini.acquire();

        std::cout << "Client " << id << " a fini la coupe.\n";
        
        clientFini.release();

        lock.lock();
        clientsEnAttente--;
        std::cout << "Client " << id << " quitte. Clients en attente : " << clientsEnAttente << "\n";
        lock.unlock();

        chaisesDispo.release();
    } else {
        std::cout << "Client " << id << " part car il n'y a pas de chaise disponible.\n";
    }
}

void barbier() {
    while (true) {
        std::cout << "Le barbier attend des clients...\n";
        barbierPret.acquire();

        std::cout << "Le barbier coupe les cheveux.\n";
        std::this_thread::sleep_for(std::chrono::seconds(6));

        barbierFini.release();
        clientFini.acquire();
    }
}

int main() {
    std::thread threadBarbier(barbier);

    std::thread clients[10];
    for (int i = 0; i < 10; i++) {
        clients[i] = std::thread(client, i);
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }

    for (int i = 0; i < 10; i++) {
        clients[i].join();
    }

    threadBarbier.join();

    return 0;
}

