LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := uninstallguard
LOCAL_SRC_FILES := guard.c
LOCAL_LDLIBS:=-L$(SYSROOT)/usr/lib -llog

LOCAL_CFLAGS += -std=c99
LOCAL_LDFLAGS += -shared

include $(BUILD_SHARED_LIBRARY)