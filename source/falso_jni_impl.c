#include <falso_jni/FalsoJNI_Impl.h>
#include <falso_jni/FalsoJNI_Logger.h>
#include <string.h>
#include <vitasdk.h>
#include <AFakeNative/keycodes.h>

// System-wide constant that's often used to determine Android version
// https://developer.android.com/reference/android/os/Build.VERSION.html#SDK_INT
// Possible values: https://developer.android.com/reference/android/os/Build.VERSION_CODES
const int SDK_INT = 19; // Android 4.4 / KitKat

/*
 * JNI Methods
*/

NameToMethodID nameToMethodId[] = {
	{ 1,  "isExpansionFileExist", METHOD_TYPE_BOOLEAN },
	{ 2,  "loadExpansionFile", METHOD_TYPE_OBJECT },
	{ 3,  "availableProcessors", METHOD_TYPE_INT },
	{ 4,  "isMusicActive", METHOD_TYPE_BOOLEAN },
};

jboolean isExpansionFileExist(jmethodID id, va_list args) {
    return 0;
}

jboolean isMusicActive(jmethodID id, va_list args) {
    return 0;
}

jobject loadExpansionFile(jmethodID id, va_list args) {
	jstring arg = va_arg(args, jstring);
	sceClibPrintf("loadExpansionFile %s\n", arg);
    return NULL;
}

jint availableProcessors(jmethodID id, va_list args) {
	return 3;
}

MethodsBoolean methodsBoolean[] = {
	{ 1,  isExpansionFileExist },
	{ 4,  isMusicActive },
};
MethodsByte methodsByte[] = {};
MethodsChar methodsChar[] = {};
MethodsDouble methodsDouble[] = {};
MethodsFloat methodsFloat[] = {};
MethodsShort methodsShort[] = {};
MethodsInt methodsInt[] = {
	{ 3,  availableProcessors },
};
MethodsLong methodsLong[] = {};
MethodsObject methodsObject[] = {
	{ 2,  loadExpansionFile },
};
MethodsVoid methodsVoid[] = {};

/*
 * JNI Fields
*/

// System-wide constant that applications sometimes request
// https://developer.android.com/reference/android/content/Context.html#WINDOW_SERVICE
char WINDOW_SERVICE[] = "window";

NameToFieldID nameToFieldId[] = {
	{ 0, "WINDOW_SERVICE", FIELD_TYPE_OBJECT }, 
	{ 1, "SDK_INT", FIELD_TYPE_INT },
};

FieldsBoolean fieldsBoolean[] = {};
FieldsByte fieldsByte[] = {};
FieldsChar fieldsChar[] = {};
FieldsDouble fieldsDouble[] = {};
FieldsFloat fieldsFloat[] = {};
FieldsInt fieldsInt[] = {
	{ 1, SDK_INT },
};
FieldsObject fieldsObject[] = {
	{ 0, WINDOW_SERVICE },
};
FieldsLong fieldsLong[] = {};
FieldsShort fieldsShort[] = {};

__FALSOJNI_IMPL_CONTAINER_SIZES
