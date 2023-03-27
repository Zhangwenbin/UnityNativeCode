package com.DefaultCompany.ScriptsBuildOnlyTest;

import android.app.Activity;
import android.util.Log;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;

public class HotUpdate {
    private static HotUpdate hotUpdate = null;
    private static final String DllPath = "CqPersist/bin/Data/Managed";
    private static final String ExternalFile = "CqPersist/files.ini";
    private static final String InsideFile = "files.ini";

    static
    {
        try
        {
            System.loadLibrary("myapplication");
        } catch (UnsatisfiedLinkError var1) {
            System.err.println("load library hotupdate failed!!!");
            System.exit(1);
        }
    }

    public static HotUpdate getInstance()
    {
        if (hotUpdate == null) {
            hotUpdate = new HotUpdate();
        }

        return hotUpdate;
    }

    public void SetHotUpdatePath(Activity activity) {
        String appPath = activity.getExternalFilesDir(null).getAbsolutePath();
        String dllPath = appPath + File.separator + "CqPersist/bin/Data/Managed";
        String persistFile = ReadExternalFile(activity);

                    Log.e("HotUpdate From Java ", dllPath);
                    SetHotUpdatePath(dllPath);

    }

    public String ReadExternalFile(Activity activity)
    {
        String result = "";
        String appPath = activity.getExternalFilesDir(null).getAbsolutePath();
        File persistFile = new File(appPath, "CqPersist/files.ini");
        try
        {
            if (persistFile.exists()) {
                BufferedReader br = new BufferedReader(new FileReader(persistFile));
                result = br.readLine();
            }
        }
        catch (Exception localException) {
        }
        Log.e("HotUpdate external", result);
        return result;
    }

    public String ReadInsideFile(Activity activity) {
        String result = "";
        try
        {
            InputStream is = activity.getAssets().open("files.ini");
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            result = br.readLine();
        }
        catch (Exception localException) {
        }
        Log.e("HotUpdate inside", result);
        return result;
    }



    public void StartHookWrap()
    {
        StartHook();
    }

    public native void SetHotUpdatePath(String paramString);

    public native void StartHook();
}
