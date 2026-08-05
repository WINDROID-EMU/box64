#ifndef ANDROID_COMPAT_H
#define ANDROID_COMPAT_H

#ifdef ANDROID
#include <android/api-level.h>

/* Get Android API level at runtime */
static inline int get_android_version(void) {
#ifdef __ANDROID_API__
    return __ANDROID_API__;
#else
    return 0; // Unknown
#endif
}

/* Check if running on at least a specific Android version */
#define IS_ANDROID_AT_LEAST(version) (get_android_version() >= (version))

/* Android-specific paths */
#define ANDROID_TMP_DIR "/data/data/com.windroid.emu/files/usr/tmp"
#define ANDROID_DATA_DIR "/data/data/com.windroid.emu/files"
#define ANDROID_USR_DIR "/data/data/com.windroid.emu/files/usr"

/* Kernel version checking for Android 12 (kernel 4.19+) */
#define KERNEL_VERSION(major, minor, patch) (((major) << 16) | ((minor) << 8) | (patch))
#define KERNEL_AT_LEAST(major, minor, patch) \
    (LINUX_VERSION_CODE >= KERNEL_VERSION(major, minor, patch))

/* Android 12 corresponds to API level 31 */
#define IS_ANDROID_12_OR_LATER IS_ANDROID_AT_LEAST(31)

/* Check if kernel supports memfd_create (kernel 3.17+) */
#define KERNEL_SUPPORTS_MEMFD KERNEL_AT_LEAST(3, 17, 0)

/* Check if kernel supports getrandom (kernel 3.17+) */
#define KERNEL_SUPPORTS_GETRANDOM KERNEL_AT_LEAST(3, 17, 0)

#else
/* Non-Android builds */
#define get_android_version() 0
#define IS_ANDROID_AT_LEAST(version) 0
#define ANDROID_TMP_DIR "/tmp"
#define ANDROID_DATA_DIR "/data"
#define ANDROID_USR_DIR "/usr"
#define IS_ANDROID_12_OR_LATER 0
#define KERNEL_SUPPORTS_MEMFD 1
#define KERNEL_SUPPORTS_GETRANDOM 1
#endif

#endif /* ANDROID_COMPAT_H */
