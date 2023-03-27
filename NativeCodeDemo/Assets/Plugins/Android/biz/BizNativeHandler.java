package com.qiyi.biz;

/**
 * Created by caikelun on 18/01/2018.
 */

public class BizNativeHandler {
    private static final BizNativeHandler ourInstance = new BizNativeHandler();

    public static BizNativeHandler getInstance() {
        return ourInstance;
    }

    private BizNativeHandler() {
    }

    public native void start();
}
