package com.DefaultCompany.ScriptsBuildOnlyTest;

import android.os.Bundle;
import android.util.Log;

import com.unity3d.player.UnityPlayerActivity;

public class MyActivity extends UnityPlayerActivity
{

    // Used to load the 'myapplication' library on application startup.
    static {
//        System.loadLibrary("monobdwgc-2.0");
//        System.loadLibrary("unity");
//        System.loadLibrary("myapplication");
//        HotUpdate.getInstance().StartHookWrap();
        System.loadLibrary("mathnativelib");

        //load xhook
        com.qiyi.xhook.XHook.getInstance().init();
        if(!com.qiyi.xhook.XHook.getInstance().isInited()) {
               Log.e("Unity", "com.qiyi.xhook.XHook not found ");
        }
        com.qiyi.xhook.XHook.getInstance().enableDebug(true); //default is false
        com.qiyi.xhook.XHook.getInstance().enableSigSegvProtection(false); //default is true

        Log.e("Unity", "com.qiyi.xhook.XHook init ");
        //load and run your biz lib (for register hook points)
        com.qiyi.biz.Biz.getInstance().init();
          Log.e("Unity", "com.qiyi.xhook.XHook start ");
        com.qiyi.biz.Biz.getInstance().start();

          Log.e("Unity", "com.qiyi.xhook.XHook loadlib ");
        //xhook do refresh
        com.qiyi.xhook.XHook.getInstance().refresh(false);
        System.loadLibrary("mathnativelib");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       // HotUpdate.getInstance().SetHotUpdatePath(this);
        Log.e("Unity", "MyActivity onCreate: ");
       
        //load and run the target lib
//        com.qiyi.test.Test.getInstance().init();
//        com.qiyi.test.Test.getInstance().start();
//        try {
//            Thread.sleep(200);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }

        //xhook do refresh again
        com.qiyi.xhook.XHook.getInstance().refresh(false);

       // Log.e("Unity", "myAddFloat java "+myAddFloat(3,21));
        //xhook do refresh again for some reason,
        //maybe called after some System.loadLibrary() and System.load()
        //*
        new Thread(new Runnable() {
            @Override
            public void run() {
                while(true)
                {
                    com.qiyi.xhook.XHook.getInstance().refresh(true);

                    try {
                        Thread.sleep(5000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();
        //*/
    }
    
     // public native float myAddFloat(float x,float y);
}
