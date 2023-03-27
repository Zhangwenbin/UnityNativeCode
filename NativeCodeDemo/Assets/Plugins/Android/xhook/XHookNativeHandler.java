package com.qiyi.xhook;

/**
 * Created by caikelun on 18/01/2018.
 */

public class XHookNativeHandler {
    private static final XHookNativeHandler ourInstance = new XHookNativeHandler();

    public static XHookNativeHandler getInstance() {
        return ourInstance;
    }

    private XHookNativeHandler() {
    }

    public native int refresh(boolean async);

    public native void clear();

    public native void enableDebug(boolean flag);

    public native void enableSigSegvProtection(boolean flag);

}
