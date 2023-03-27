package com.test.mathnativelib;

public class NativeLib {

    // Used to load the 'mathnativelib' library on application startup.
    static {
        System.loadLibrary("mathnativelib");
    }

    /**
     * A native method that is implemented by the 'mathnativelib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}