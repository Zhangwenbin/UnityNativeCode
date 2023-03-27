package com.test.biz;

public class NativeLib {

    // Used to load the 'biz' library on application startup.
    static {
        System.loadLibrary("biz");
    }

    /**
     * A native method that is implemented by the 'biz' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}