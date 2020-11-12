package com.example.nativeappexample;

public class NativeLibrary {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    JNICallBackInterface callBackInterface;

    public NativeLibrary(JNICallBackInterface callBackInterface){
        this.callBackInterface = callBackInterface;
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int passingDataToJni(double[] tmpArray, int tmpInt, float tmpFloat);

    public native int passObjectToJNI(SampleDataObj sampleDataObj);

    public native SampleDataObj getObjectFromJNI();

    public native void callTheCallBackMethod();

    private void callBack(int data, String stringValue) {
        callBackInterface.callBackEvent(stringValue + String.valueOf(data));
    }
}
