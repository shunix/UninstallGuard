#include <limits.h>
#include <jni.h>
#include <string.h>
#include <unistd.h>
#include <android/log.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include "guard.h"

static const char* class_path_name = "";
static const char* data_path = "/data/data";
static JNINativeMethod methods[] = {
    {"startGuard", "(Ljava/lang/String)V", &StartGuard}
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGD("JNI_OnLoad");
    JNIEnv* env;
    int ret = (*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_6);
    if (ret == JNI_EDETACHED) {
        LOGD("JNI_EDETACHED");
        if ((*vm)->AttachCurrentThread(vm, &env, NULL) != 0) {
            LOGD("AttachCurrentThread Error");
            return JNI_ERR;
        }
    } else if (ret == JNI_OK) {
        jclass clazz = (*env)->FindClass(env, class_path_name);
        (*env)->RegisterNatives(env, clazz, methods, sizeof(methods) / sizeof(methods[0]));
        return JNI_VERSION_1_6;
    } else {
        LOGD("JNI_OnLoad Error");
        return JNI_ERR;
    }
}

JNIEXPORT void JNICALL StartGuard(JNIEnv* env, jobject obj, jstring package_name) {
    LOGD("StartGuard");
    const char* native_package_name = (*env)->GetStringUTFChars(env, package_name, NULL);
    LOGD("Package Name: %s", native_package_name);
    char* dest_path = (char*) calloc(BUFFER_LEN, sizeof(char));
    strcpy(dest_path, data_path);
    strcat(dest_path, native_package_name);
    LOGD("Dest Path: %s", dest_path);
    pid_t pid = fork();
    if (pid < 0) {
        LOGD("Unable to fork");
    } else {
        if (pid == 0) {
            int inotify_fd = inotify_init();
            int watch_des = inotify_add_watch(inotify_fd, dest_path, IN_DELETE_SELF);
            if (watch_des == -1) {
                return;
            } else {
                LOGD("Watch Descriptor: %d", watch_des);
            }
            uint8_t buffer[INOTIFY_BUFFER_LENGTH];
            for(;;) {
                int read_length = read(inotify_fd, buffer, INOTIFY_BUFFER_LENGTH);
                uint8_t* p = buffer;
                if (read_length > 0) {
                  for (int i  = 0; i < read_length;) {
                      LOGD("App was uninstalled");
                      int name_length = ((struct inotify_event*) p)->len;
                      p += (sizeof(struct inotify_event) + name_length);
                      i += (sizeof(struct inotify_event) + name_length);
                  }
                }
            }
        } else {
            LOGD("Forked pid: %d", pid);
            int status;
            waitpid(pid, &status, 0);
        }
    }
    (*env)->ReleaseStringUTFChars(env, package_name, native_package_name);
}