#define BUFFER_LEN 255
#define INOTIFY_BUFFER_LENGTH (sizeof(struct inotify_event) + NAME_MAX + 1)
#define TAG "UNINSTALL_GUARD"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

JNIEXPORT void JNICALL StartGuard(JNIEnv* env, jobject obj, jstring package_name);