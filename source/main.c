/*
 * main.c
 *
 * ARMv7 Shared Libraries loader. EnbornX Edition
 *
 * Copyright (C) 2021 Andy Nguyen
 * Copyright (C) 2021-2023 Rinnegatamante
 * Copyright (C) 2022-2023 Volodymyr Atamanenko
 *
 * This software may be modified and distributed under the terms
 * of the MIT license. See the LICENSE file for details.
 */

#include "utils/init.h"
#include "utils/glutil.h"
#include "utils/settings.h"
#include "utils/logger.h"

#include <psp2/kernel/threadmgr.h>

#include <falso_jni/FalsoJNI.h>
#include <so_util/so_util.h>

#include <AFakeNative/AFakeNative.h>
#include <vitasdk.h>
#include <kubridge.h>
#include <stdio.h>

int _newlib_heap_size_user = 256 * 1024 * 1024;

#ifdef USE_SCELIBC_IO
int sceLibcHeapSize = 24 * 1024 * 1024;
#endif

so_module so_mod;

int crasher(unsigned int argc, void *argv) {
	uint32_t *nullptr = NULL;
	for (;;) {
		SceCtrlData pad;
		sceCtrlPeekBufferPositive(0, &pad, 1);
		if (pad.buttons & SCE_CTRL_SELECT) *nullptr = 0;
		sceKernelDelayThread(100);
	}
}

int main() {
	//sceSysmoduleLoadModule(SCE_SYSMODULE_RAZOR_CAPTURE);
	//SceUID crasher_thread = sceKernelCreateThread("crasher", crasher, 0x40, 0x1000, 0, 0, NULL);
	//sceKernelStartThread(crasher_thread, 0, NULL);

	SceAppUtilInitParam appUtilParam;
	SceAppUtilBootParam appUtilBootParam;
	memset(&appUtilParam, 0, sizeof(SceAppUtilInitParam));
	memset(&appUtilBootParam, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&appUtilParam, &appUtilBootParam);

	soloader_init_all();
	
	int (*JNI_OnLoad)(JavaVM *jvm) = (void*)so_symbol(&so_mod,"JNI_OnLoad");
    JNI_OnLoad(&jvm);
	log_info("JNI_OnLoad() passed");
	
	void (*initNativeGlobal)(JNIEnv * env, jclass clazz, char *external_dir, char *internal_dir, uint8_t is_xperia, uint8_t key_swapped) = (void *) so_symbol(&so_mod, "_Z59Java_com_lantansia_enbornx_EnbornXActivity_initNativeGlobalP7_JNIEnvP7_jclassP8_jstringS4_hh");
	initNativeGlobal(&jni, 0x0, "ux0:data/enbornx", "ux0:data/enbornx", 1, 0);
	
	void (*setHardKeyboardHidden)(JNIEnv * env, jclass clazz, uint8_t hidden) = (void *) so_symbol(&so_mod, "_Z64Java_com_lantansia_enbornx_EnbornXActivity_setHardKeyboardHiddenP7_JNIEnvP7_jclassh");
	setHardKeyboardHidden(&jni, 0x0, 1);
	
	int (*ANativeActivity_onCreate)(ANativeActivity *activity, void *savedState, size_t savedStateSize) = (void *) so_symbol(&so_mod, "ANativeActivity_onCreate");
	ANativeActivity *activity = ANativeActivity_create();
	log_info("Created NativeActivity object");

	ANativeActivity_onCreate(activity, NULL, 0);
	log_info("ANativeActivity_onCreate() passed");

	activity->callbacks->onStart(activity);
	log_info("onStart() passed");

	AInputQueue *aInputQueue = AInputQueue_create();
	activity->callbacks->onInputQueueCreated(activity, aInputQueue);
	log_info("onInputQueueCreated() passed");

	ANativeWindow *aNativeWindow = ANativeWindow_create();
	activity->callbacks->onNativeWindowCreated(activity, aNativeWindow);
	log_info("onNativeWindowCreated() passed");

	activity->callbacks->onWindowFocusChanged(activity, 1);
	log_info("onWindowFocusChanged() passed");

	activity->callbacks->onResume(activity);
	log_info("Main thread shutting down");

	sceKernelExitDeleteThread(0);
}
