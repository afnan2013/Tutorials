#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_nativeappexample_NativeLibrary_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Yup.... I have linked it";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativeappexample_NativeLibrary_passingDataToJni(JNIEnv *env, jobject thiz,
                                                                 jdoubleArray tmp_array,
                                                                 jint tmp_int, jfloat tmp_float) {
    jdouble *tmpArray = env->GetDoubleArrayElements(tmp_array,NULL);

    int ret =1;
    ret = (tmpArray[0]==1 && tmpArray[1] == 2 && tmpArray[2]== 3)? 0: -1;

    env->ReleaseDoubleArrayElements(tmp_array, tmpArray, 0);
    return ret;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_nativeappexample_NativeLibrary_passObjectToJNI(JNIEnv *env, jobject thiz,
                                                                jobject sample_data_obj) {

    // Get jclass of the object
    jclass sampleDataOBJClass = env->GetObjectClass(sample_data_obj);

    // Get data field IDs of the object
    jfieldID sampIntField = env->GetFieldID(sampleDataOBJClass, "sampleInt", "I");
    jfieldID sampBoolField = env->GetFieldID(sampleDataOBJClass, "sampleBoolean", "Z");
    jfieldID sampStringField = env->GetFieldID(sampleDataOBJClass, "sampleString",
                                               "Ljava/lang/String;");

    // Get individual Data
    jint sampleInt = env->GetIntField(sample_data_obj, sampIntField);
    jboolean sampleBoolean = env->GetBooleanField(sample_data_obj, sampBoolField);

    // Update data
    const char *successString = "SUCCESS";
    env->SetObjectField(sample_data_obj, sampStringField, env->NewStringUTF(successString));

    // return error code (in this case, return the int value form the object)
    return sampleInt;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_nativeappexample_NativeLibrary_getObjectFromJNI(JNIEnv *env, jobject instance){
    // Create a jclass from actual Java object class path
    jclass sampleObjClass = env->FindClass(
            "com/example/nativeappexample/SampleDataObj");
    jmethodID methodId = env->GetMethodID(sampleObjClass, "<init>", "()V");
    jobject sampleObj = env->NewObject(sampleObjClass, methodId);

    //Update fields of object
    const char *successString = "Hi...I am an object";
    jfieldID sampStringField = env->GetFieldID(sampleObjClass, "sampleString",
                                               "Ljava/lang/String;");
    env->SetObjectField(sampleObj, sampStringField, env->NewStringUTF(successString));

    //Update int data field
    int data = 10;
    jfieldID sampIntField = env->GetFieldID(sampleObjClass, "sampleInt", "I");
    env->SetIntField(sampleObj, sampIntField, data);

    return sampleObj;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_nativeappexample_NativeLibrary_callTheCallBackMethod(JNIEnv *env, jobject instance) {
    // Get jclass of the instance
    jclass jClassInstance = env->GetObjectClass(instance);

    // Get java callback method
    jmethodID callBackJava = env->GetMethodID(jClassInstance, "callBack", "(ILjava/lang/String;)V");

    // If method not found
    if (NULL == callBackJava) return;

    // create string data to pass
    const char *successString = "SUCCESS     ";

    // integer value to pass
    int data = 10;

    // Call back Java method with parameters
    env->CallVoidMethod(instance, callBackJava, data, env->NewStringUTF(successString));
}