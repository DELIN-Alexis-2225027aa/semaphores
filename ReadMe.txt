# BarberShop Problem - Gestion des Incidents de Cybersécurité

## Introduction ##

Dans ce projet, nous appliquons le **problème du salon de coiffure (BarberShop Problem)** à un scénario concret de **gestion d'incidents de cybersécurité**. Le problème original du salon de coiffure modélise la gestion d'un nombre limité de clients dans un salon, avec un coiffeur et une salle d'attente. Nous adaptons cette problématique à un contexte de cybersécurité où un nombre limité d'**analystes de sécurité** gèrent les **tickets d'incidents** de sécurité.

## Concept

L'idée principale est de gérer la synchronisation entre :
- Les **incidents de sécurité** qui arrivent dans le système (équivalent aux **clients** dans le problème du salon de coiffure).
- Les **analystes de sécurité** (équivalent au **coiffeur**), qui traitent ces incidents de manière synchrone, un incident à la fois.

Chaque analyste peut traiter un seul ticket d'incident à la fois, et s'il y a plus de tickets que d'analystes disponibles, les nouveaux tickets doivent attendre jusqu'à ce qu'un analyste se libère.

## Structure du projet

Nous avons organisé le projet avec des fichiers séparés pour mieux structurer le code. Chaque fichier représente un composant spécifique de la solution.

### Fichiers utilisés :

1. **`main.cpp`** : Le fichier principal où nous lançons les threads pour simuler l'arrivée des incidents et la gestion de ces incidents par les analystes.
2. **`Incident.h` et `Incident.cpp`** : Contient la classe `Incident` qui simule l'arrivée des incidents dans le système.
3. **`Analyst.h` et `Analyst.cpp`** : Contient la classe `Analyst`, représentant l'analyste de sécurité qui traite les incidents.
4. **`SyncTools.h` et `SyncTools.cpp`** : Contient les outils de synchronisation comme les sémaphores et les mutex, nécessaires pour gérer la coordination entre l'arrivée des incidents et leur traitement par les analystes.

### Synchronisation

Nous utilisons des **sémaphores** pour gérer la synchronisation entre l'arrivée des incidents et leur traitement par les analystes :
- **incidentQueue** : Sémaphore qui représente la file d'attente des incidents.
- **incidentProcessed** : Sémaphore qui signale la fin du traitement d'un incident.

Un **mutex** est utilisé pour protéger l'accès aux variables partagées, comme le compteur des incidents en cours.

### Exemple de scénario :

1. **Arrivée d'incidents** : Plusieurs incidents de sécurité arrivent dans le système (modélisés par des threads). Si des analystes sont disponibles, ils prennent immédiatement un incident à traiter. Si tous les analystes sont occupés, les nouveaux incidents attendent dans une file d'attente (gérée par les sémaphores).
   
2. **Traitement par les analystes** : Les analystes de sécurité prennent les incidents un par un et les traitent. Une fois qu'un analyste termine le traitement d'un incident, il signale qu'il est prêt à traiter un nouvel incident.

3. **Synchronisation des incidents** : Les incidents doivent attendre qu'un analyste soit disponible. Lorsqu'un incident est pris en charge, il attend que le traitement soit terminé avant de signaler qu'il est résolu.

## Implémentation

1. **Gestion des incidents (Incident class)** :
   - Les incidents sont représentés par des threads qui simulent l'arrivée aléatoire des tickets d'incidents dans le système.
   - Chaque incident appelle la fonction `handleIncident()` pour attendre qu'un analyste soit disponible.

2. **Gestion des analystes (Analyst class)** :
   - Les analystes de sécurité sont également modélisés par des threads.
   - Chaque analyste appelle la fonction `processIncident()` pour attendre qu'un incident arrive, traiter l'incident, puis passer au suivant.

3. **Outils de synchronisation (SyncTools class)** :
   - Des sémaphores sont utilisés pour synchroniser les interactions entre incidents et analystes.
   - Le sémaphore `incidentQueue` permet aux analystes de savoir quand un incident est disponible pour être traité.
   - Le sémaphore `incidentProcessed` permet aux incidents de signaler que le traitement est terminé.

