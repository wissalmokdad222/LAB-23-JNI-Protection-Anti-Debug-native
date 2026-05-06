#include <jni.h>
#include <string>
#include <algorithm>
#include <climits>
#include <android/log.h>

#define LOG_TAG "JNI_DEMO"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

/**
 * Note pour l'Étape 11 :
 * Toujours utiliser extern "C" pour éviter le "name mangling" C++.
 * La signature doit suivre strictement : Java_package_classe_methode
 */

void throwException(JNIEnv* env, const char* message) {
    jclass exClass = env->FindClass("java/lang/IllegalArgumentException");
    if (exClass != nullptr) {
        env->ThrowNew(exClass, message);
    }
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_helloFromJNI(JNIEnv* env, jobject /* this */) {
    return env->NewStringUTF("Hello from C++ via JNI !");
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_factorial(JNIEnv* env, jobject /* this */, jint n) {
    if (n < 0) {
        throwException(env, "Le nombre doit être positif.");
        return 0;
    }
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        if (fact > INT_MAX) {
            throwException(env, "Dépassement de capacité (Overflow).");
            return 0;
        }
    }
    return static_cast<jint>(fact);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_jnidemo_MainActivity_reverseString(JNIEnv* env, jobject /* this */, jstring javaString) {
    if (javaString == nullptr) return env->NewStringUTF("");
    const char* chars = env->GetStringUTFChars(javaString, nullptr);
    std::string s(chars);
    env->ReleaseStringUTFChars(javaString, chars);
    std::reverse(s.begin(), s.end());
    return env->NewStringUTF(s.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_example_jnidemo_MainActivity_sumArray(JNIEnv* env, jobject /* this */, jintArray array) {
    if (array == nullptr) {
        throwException(env, "Le tableau ne peut pas être nul.");
        return 0;
    }
    jsize len = env->GetArrayLength(array);
    jint* elements = env->GetIntArrayElements(array, nullptr);
    long long sum = 0;
    for (jsize i = 0; i < len; i++) {
        sum += elements[i];
    }
    env->ReleaseIntArrayElements(array, elements, 0);
    return static_cast<jint>(sum);
}

// Correction pour UnsatisfiedLinkError : Vérification stricte du nom
extern "C" JNIEXPORT jlong JNICALL
Java_com_example_jnidemo_MainActivity_heavyTaskNative(JNIEnv* env, jobject /* this */, jint iterations) {
    long long sum = 0;
    for (int i = 0; i < iterations; i++) {
        sum += (i % 100);
    }
    return static_cast<jlong>(sum);
}
