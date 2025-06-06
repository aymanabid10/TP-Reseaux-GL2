# TP-Reseaux-GL2
- Aymen Abid
# TP Socket en C – Version Windows (Winsock)

## 🎯 Objectif du TP

Ce TP a pour objectif d'explorer les communications réseaux via les **sockets** en langage **C**, sous **Windows**, en utilisant l’API **Winsock2**. Le travail est divisé en trois parties :

1. HTTP en mode connecté
2. Communication TCP (client/serveur)
3. Communication UDP (client/serveur)

---

## ⚙️ Prérequis

- Windows 10/11
- `telnet` activé (voir plus bas)

---

## 🗂 Arborescence du projet

```
.
├── HTTP en mode connecté
│   ├── client_http_windows.c
│   └── client_http_windows.exe
├── TCP
│   ├── client_tcp_windows.c
│   ├── client_tcp_windows.exe
│   ├── serveur_tcp_windows.c
│   └── serveur_tcp_windows.exe
├── UDP
│   ├── client_udp_windows.c
│   ├── client_udp_windows.exe
│   ├── serveur_udp_windows.c
│   └── serveur_udp_windows.exe
└── README.md
```

---

## 🔧 Compilation

### Avec MinGW :

```bash
gcc client_tcp_windows.c -o client_tcp_windows.exe -lws2_32
gcc serveur_tcp_windows.c -o serveur_tcp_windows.exe -lws2_32
gcc client_udp_windows.c -o client_udp_windows.exe -lws2_32
gcc serveur_udp_windows.c -o serveur_udp_windows.exe -lws2_32
gcc client_http_windows.c -o client_http_windows.exe -lws2_32
```

> `-lws2_32` permet de lier la bibliothèque Winsock2.(pour Windows)

---

## ✅ Exécution

### 1. Serveur TCP

```bash
./TCP/serveur_tcp_windows.exe
```

### 2. Client TCP

```bash
./TCP/client_tcp_windows.exe
```

### 3. Serveur UDP

```bash
./UDP/serveur_udp_windows.exe
```

### 4. Client UDP

```bash
./UDP/client_udp_windows.exe
```

### 5. Client HTTP

```bash
./HTTP\ en\ mode\ connecté/client_http_windows.exe
```

---

## 🧠 Explication des programmes

### 🔸 Partie HTTP

- Le client envoie une requête HTTP `GET /` à un serveur (par exemple 10.250.101.1:80).
- Il reçoit la réponse HTML du serveur.

### 🔸 Partie TCP

- Le serveur envoie l’heure au client toutes les secondes pendant 60 secondes.
- Le client affiche ce qu’il reçoit sur la sortie standard.

### 🔸 Partie UDP

- Le client envoie un message d’initialisation.
- Le serveur répond avec l’heure pendant 60 secondes.
- Le client affiche les données reçues.

---

## 🧩 Détails sur l'implémentation Windows

### ⚠️ Différences avec Linux

| Linux / Unix        | Windows (Winsock)         |
|---------------------|---------------------------|
| `<sys/socket.h>`    | `<winsock2.h>`            |
| `close()`           | `closesocket()`           |
| Pas d’init requise  | `WSAStartup()` obligatoire |
| `read()/write()`    | `recv()/send()`           |

### ✅ Initialisation Winsock

Chaque programme commence par :

```c
WSADATA wsa;
WSAStartup(MAKEWORD(2, 2), &wsa);
```

Et se termine par :

```c
WSACleanup();
```

---

## 🛰️ Telnet sous Windows

Telnet permet de simuler un client TCP.

### ▶️ Activer Telnet

```txt
Panneau de configuration > Programmes > Activer ou désactiver des fonctionnalités Windows > Telnet Client
```

### ▶️ Exemple d’utilisation

Lance le serveur TCP :

```bash
./TCP/serveur_tcp_windows.exe
```

Puis dans le terminal :

```bash
telnet 127.0.0.1 12345
```

Tu devrais voir s'afficher l'heure toutes les secondes.

---

## ❓ Questions / Réponses

### **Q1. Qu'est-ce qu'une socket ?**
Une socket est une interface permettant la communication réseau entre deux processus (souvent client-serveur), localement ou à distance.

### **Q2. Quelle est la différence entre TCP et UDP ?**

| TCP                         | UDP                            |
|----------------------------|--------------------------------|
| Orienté connexion          | Sans connexion                 |
| Fiable (accusé de réception) | Moins fiable mais plus rapide |
| Ex : HTTP, FTP             | Ex : DNS, VoIP                 |

### **Q3. Pourquoi utiliser `WSAStartup()` sur Windows ?**
Winsock doit être initialisé avant toute utilisation des sockets sous Windows. C’est obligatoire.

### **Q4. Pourquoi `closesocket()` au lieu de `close()` ?**
Parce que Windows utilise une API propre aux sockets, distincte des fichiers (contrairement à Linux).

---

## 🧪 Conseils de test

1. Toujours lancer les serveurs avant les clients.
2. Tester localement avec `127.0.0.1`.
3. Tester avec plusieurs terminaux (ou un client telnet + ton client C).
4. Vérifier le pare-feu si tu ne reçois pas de données.

---

## ✍️ Auteur

TP réalisé dans le cadre du cours de Réseaux, adapté pour Windows par Aymen Abid.
