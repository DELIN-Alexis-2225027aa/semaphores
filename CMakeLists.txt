# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(Semaphores)

# Compiler uniquement ProjetFonctionnel
add_executable(semaphores
        ProjetFonctionnel/src/Analysts.cpp
        ProjetFonctionnel/src/Incident.cpp
        ProjetFonctionnel/src/SyncTools.cpp
        ProjetFonctionnel/main.cpp
)

 add_executable(semaphores_non_fonctionnel
     ProjetNonFonctionnel/src/AnalystU.cpp
     ProjetNonFonctionnel/src/IncidentU.cpp
     ProjetNonFonctionnel/src/SyncToolsU.cpp
     ProjetNonFonctionnel/main.cpp
         ProjetNonFonctionnel/src/IncidentU.h
 )
