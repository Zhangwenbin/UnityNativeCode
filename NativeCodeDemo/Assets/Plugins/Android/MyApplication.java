package com.DefaultCompany.ScriptsBuildOnlyTest;

import android.os.Bundle;
import android.util.Log;

import android.app.Application;

public class MyApplication extends Application
{
  public void onCreate()
  {
    super.onCreate();
     Log.e("Unity", "MyApplication onCreate: ");
  }
}
