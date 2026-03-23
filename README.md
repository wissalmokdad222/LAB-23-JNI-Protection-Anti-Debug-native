# JNIDemo - Guide d'Intégration JNI & NDK Android

Ce projet est un laboratoire complet démontrant l'utilisation de **Java Native Interface (JNI)** pour exécuter du code C++ au sein d'une application Android.

##  Étapes de Réalisation

### 1. Configuration du Projet
- Création d'un projet Android avec **C++ support**.
- Configuration du `build.gradle.kts` :
    - Activation du `externalNativeBuild` (CMake).
    - Ajout du support `viewBinding`.
    - Mise à jour du `compileSdk` (version 36) pour la compatibilité.

### 2. Couche Native (C++)
- **Fichier `CMakeLists.txt`** : Déclare la bibliothèque `native-lib` et la lie à la bibliothèque système `log`.
- **Fichier `native-lib.cpp`** :
    - Implémentation des signatures JNI (`Java_com_example_jnidemo_MainActivity_...`).
    - Gestion des types : `jstring`, `jint`, `jintArray`.
    - **Gestion d'exceptions** : Le C++ lève des `IllegalArgumentException` Java en cas d'erreur (négatif, overflow).
    - **Journalisation** : Utilisation de `__android_log_print` avec le tag `JNI_DEMO`.

### 3. Interface Utilisateur (XML)
- Mise en place d'une `ScrollView` contenant un `LinearLayout` vertical.
- Affichage des résultats via plusieurs `TextView` identifiés pour chaque test JNI.

### 4. Code Java (MainActivity)
- Déclaration des méthodes `native`.
- Chargement de la bibliothèque : `System.loadLibrary("native-lib")`.
- **Tests Robustes** : Utilisation de blocs `try-catch` pour intercepter les exceptions levées par le code natif.
- **Benchmark** : Comparaison du temps d'exécution entre une boucle Java et sa version native C++.

## Résultats des Tests
- **Hello JNI** : Message retourné depuis le C++.
- **Calculs** : Factorielle de 10 (normal), -5 (erreur catchée) et 20 (overflow catché).
- **Manipulation** : Inversion de chaîne et somme de tableau d'entiers.
- **Performance** : Calcul intensif montrant le gain de vitesse du code natif.

##  Outils Requis
- **NDK** (Side by side)
- **CMake**
- **LLDB** (pour le débogage natif)

---
*Projet réalisé dans le cadre d'un apprentissage progressif et professionnel du NDK Android.*