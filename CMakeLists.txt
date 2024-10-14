cmake_minimum_required(VERSION 3.29)
project(semaphores)

set(CMAKE_CXX_STANDARD 14)

include_directories(ProjetFonctionnel/src)
include_directories(ProjetNonFonctionnel/src)

add_executable(semaphores
    ProjetFonctionnel/src/Analyst.cpp
    ProjetFonctionnel/src/Analyst.h
    ProjetFonctionnel/src/Incident.cpp
    ProjetFonctionnel/src/Incident.h
    ProjetFonctionnel/src/SyncTools.cpp
    ProjetFonctionnel/src/SyncTools.h
    ProjetFonctionnel/main.cpp
    ProjetNonFonctionnel/src/Analyst.cpp
    ProjetNonFonctionnel/src/Analyst.h
    ProjetNonFonctionnel/src/Incident.cpp
    ProjetNonFonctionnel/src/Incident.h
    ProjetNonFonctionnel/src/SyncTools.cpp
    ProjetNonFonctionnel/src/SyncTools.h
    ProjetNonFonctionnel/main.cpp)
