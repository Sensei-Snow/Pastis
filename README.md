# Pastis

<p align="center">
  <strong>Un clipboard hijacker éducatif écrit en C pour Windows.</strong>
  <br />
  <em>Comprendre le fonctionnement du presse-papiers avec l'API Win32.</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white" alt="Windows" />
  <img src="https://img.shields.io/badge/API-Win32-555555?style=for-the-badge" alt="Win32 API" />
  <img src="https://img.shields.io/badge/Build-CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/Purpose-Educational-2E8B57?style=for-the-badge" alt="Educational project" />
</p>

---

## 📖 Présentation

**Pastis** est un projet développé en **C**, destiné à explorer le fonctionnement du presse-papiers de Windows et les mécanismes système permettant d'interagir avec celui-ci à travers l'API Win32.

Le projet s'inscrit dans une démarche d'apprentissage de la programmation système, de la gestion des données du presse-papiers et des implications de sécurité associées.

Un *clipboard hijacker* désigne un programme capable de surveiller ou de modifier le contenu du presse-papiers. Ce type de mécanisme peut notamment être détourné pour altérer des données copiées par l'utilisateur.

Pastis permet notamment de comprendre le fonctionnement de ces logiciels à travers un exemple concret, les adresses de portefeuilles de cryptomonnaies.

## 📁 Structure du projet

```text
Pastis/
├── config/
│   └── config.ini
├── bin/
│   └── Pastis.exe
├── CMakeLists.txt
├── src/
│   └── ...
├── include/
│   └── ...
├── lib/
│   └── ...
├── .gitignore
├── LICENSE
└── README.md
```

## 🚀 Installation et compilation

### Prérequis

Avant de commencer, assure-toi de disposer des éléments suivants :

- Windows avec les outils de développement compatibles avec le projet.
- Un compilateur C compatible avec la cible Windows.
- CMake.
- Git, si tu souhaites cloner le dépôt.

### 1. Récupérer le projet

Clone le dépôt puis place-toi dans son répertoire :

```bash
git clone https://github.com/Sensei-Snow/Pastis.git
cd Pastis
```

### 2. Configurer le programme

Ouvre le fichier :

```text
config/config.ini
```

Modifie les paramètres avec tes propres adresses de portefeuilles de cryptomonnaies.

### 3. Générer les fichiers de compilation

À la racine du projet, exécute :

```bash
cmake -S . -B build_config
```

Cette commande utilise `CMakeLists.txt` pour générer les fichiers nécessaires à la compilation dans le dossier `build_config/`.

### 4. Compiler

Lance ensuite :

```bash
cmake --build build_config --config Release
```

CMake invoquera le compilateur et construira les cibles définies dans le projet.

> 💡 Le générateur CMake utilisé détermine les outils nécessaires. Avec Visual Studio, les commandes ci-dessus peuvent être exécutées depuis un terminal disposant de l'environnement de développement approprié.

### 5. Exécution

Une fois la compilation terminée, retrouve l'exécutable dans le répertoire de sortie défini par le projet et par le générateur CMake.

Respecte les paramètres configurés et utilise uniquement un environnement de test autorisé.

N'hésite pas à désactiver temporairement ton antivirus.

Pour arrêter le logiciel, passe par le gestionnaire de tâche de ton système et tue le processus. Pastis est discret et s'exécute en arrière-plan.

## 👨‍💻 Auteur

**$now_**

## 📜 Licence

Ce projet est distribué sous licence MIT.

---

<p align="center">
  <strong>Pastis</strong>
  <br />
  <em>Fait avec 💖</em>
</p>
