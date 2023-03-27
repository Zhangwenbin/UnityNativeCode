package com.test.xhook;

public class NativeLib {

    // Used to load the 'xhook' library on application startup.
    static {
        System.loadLibrary("xhook");
    }

    /**
     * A native method that is implemented by the 'xhook' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}