# JNIDemo - Guide d'Intégration JNI & NDK Android

Ce projet est un laboratoire complet démontrant l'utilisation de **Java Native Interface (JNI)** pour exécuter du code C++ au sein d'une application Android, alliant performance et sécurité.

## 🛠 Étapes de Réalisation

### 1. Fondamentaux du JNI
- **Configuration** : Activation de `externalNativeBuild` avec CMake dans `build.gradle.kts`.
- **Implémentation C++** : Création de `native-lib.cpp` gérant les types `jstring`, `jint`, et `jintArray`.
- **Passerelle Java** : Chargement de la bibliothèque via `System.loadLibrary("native-lib")`.
- **Performance** : Mise en place d'un benchmark montrant un gain significatif (~40x) pour les calculs intensifs.

### 2. Sécurité & Anti-Débogage (Avancé)
Ce volet explore l'utilisation du NDK pour protéger l'application contre l'instrumentation :
- **Contrôle via ptrace** : Détection de la présence d'un debugger au niveau système.
- **Inspection de `/proc/self/maps`** : Recherche de signatures textuelles d'outils comme **Frida**, **Xposed**, **Magisk** ou **GDB**.
- **Réaction graduée** : Remontée d'un état suspect vers l'interface Java sans provoquer de crash brutal.

### 3. Gestion d'Exceptions Natives
Implémentation d'une variante avancée où le code C++ lève directement des exceptions Java (`IllegalArgumentException`) via JNI. Cela permet une API propre et sécurisée côté Java utilisant des blocs `try-catch`.

---

## 🔍 Analyse & Validation

### Scénarios de Test
1. **Exécution normale** : Statut "OK", fonctions natives autorisées.
2. **Session de Debug** : Signalement d'un état suspect par le contrôle natif.
3. **Cas Limites** : Validation des erreurs pour valeurs négatives ou dépassements de capacité (overflow).

### Limites de l'Approche
- La détection n'est jamais exhaustive et peut présenter des faux positifs.
- Un attaquant expérimenté peut tenter de neutraliser les contrôles natifs.
- L'objectif est d'enseigner une stratégie de **durcissement progressive** plutôt qu'une protection absolue.

---

## 💡 Bonnes Pratiques JNI
- **Minimiser les transitions** : Réduire les allers-retours Java ↔ Natif pour limiter le surcoût.
- **Libération des ressources** : Utilisation rigoureuse de `ReleaseStringUTFChars` et `ReleaseIntArrayElements`.
- **Séparation des responsabilités** : Isoler la logique métier du code défensif.
- **Observabilité** : Utilisation de Logcat native avec des tags spécifiques (`ANTI_DEBUG`, `JNI_DEMO`).

---

## 🎓 Résumé pédagogique
Dans ce laboratoire, l’application Android :
- Charge une bibliothèque native avec `System.loadLibrary`.
- Appelle une méthode JNI `isDebugDetected()`.
- Exécute deux contrôles natifs simples (ptrace et maps).
- Remonte un booléen à Java.
- Adapte l’interface selon l’état détecté.

Ce TP consolide à la fois les connaissances JNI, la structure d’un module natif Android, l’usage de CMake, la journalisation native et l’idée de défense en profondeur côté mobile.

## 🏁 Conclusion
JNI est une passerelle puissante entre Java et C++, mais il faut l’utiliser avec méthode. Le bon usage consiste donc à réserver JNI aux traitements réellement utiles : **calcul intensif**, **bibliothèques natives existantes**, **logique sensible**, ou **services bas niveau**.

Avec ce laboratoire, l’application **JNIDemo** devient un excellent point de départ pour des projets plus avancés comme le chiffrement natif, la détection anti-debug avancée, le traitement d’image ou la sécurité applicative Android.

---
*Projet réalisé avec succès - Expertise NDK Android.*
