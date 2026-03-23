#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define LOG_TAG "JNI_DEMO"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Fonction utilitaire pour lancer une exception Java
void throwJavaException(JNIEnv* env, const char* message) {
    jclass exClass = env->FindClass("java/lang/IllegalArgumentException");
    if (exClass != nullptr) {
        env->ThrowNew(exClass, message);
    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_helloFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    LOGI("Appel de helloFromJNI depuis le natif");
    return env->NewStringUTF("Hello from C++ via JNI !");
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_factorial(
        JNIEnv* env,
        jobject /* this */,
        jint n) {

    if (n < 0) {
        LOGE("Erreur : n negatif");
        throwJavaException(env, "La factorielle n'est pas definie pour les nombres negatifs.");
        return 0; // La JVM detectera l'exception apres le retour
    }

    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        if (fact > INT_MAX) {
            LOGE("Overflow detecte pour n=%d", n);
            throwJavaException(env, "Depassement de capacite (Overflow) detecte.");
            return 0;
        }
    }

    LOGI("Factoriel de %d calcule en natif = %lld", n, fact);
    return static_cast<jint>(fact);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_reverseString(
        JNIEnv* env,
        jobject /* this */,
        jstring javaString) {

    if (javaString == nullptr) {
        throwJavaException(env, "La chaine ne peut pas etre nulle.");
        return nullptr;
    }

    const char* chars = env->GetStringUTFChars(javaString, nullptr);
    if (chars == nullptr) return nullptr;

    std::string s(chars);
    env->ReleaseStringUTFChars(javaString, chars);

    std::reverse(s.begin(), s.end());
    return env->NewStringUTF(s.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_sumArray(
        JNIEnv* env,
        jobject /* this */,
        jintArray array) {

    if (array == nullptr) {
        throwJavaException(env, "Le tableau ne peut pas etre nul.");
        return 0;
    }

    jsize len = env->GetArrayLength(array);
    jint* elements = env->GetIntArrayElements(array, nullptr);
    if (elements == nullptr) return 0;

    long long sum = 0;
    for (jsize i = 0; i < len; i++) {
        sum += elements[i];
    }

    env->ReleaseIntArrayElements(array, elements, 0);

    if (sum > INT_MAX) {
        throwJavaException(env, "Overflow sur la somme du tableau.");
        return 0;
    }

    return static_cast<jint>(sum);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_jnidemo_MainActivity_heavyTaskNative(
        JNIEnv* env,
        jobject /* this */,
        jint iterations) {

    long long sum = 0;
    for (int i = 0; i < iterations; i++) {
        sum += (i % 100);
    }
    return static_cast<jlong>(sum);
}
