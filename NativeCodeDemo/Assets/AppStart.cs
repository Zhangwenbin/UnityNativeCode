using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

public class AppStart : MonoBehaviour
{
   // [DllImport("__Internal")]
  //  private static extern float myNativeAdd(float x, float y);
    
    [DllImport("mathnativelib")]
    private static extern float myAddFloat(float x, float y);
    // Start is called before the first frame update
    void Start()
    {
        Debug.LogError("start----3333");
     //   Debug.LogError("start----"+myNativeAdd(2, 7));
        InvokeRepeating("Log",3,1);
        
    }

    // Update is called once per frame
    void Log()
    {
        Debug.LogError("start----"+myAddFloat(2, 7));
    }
}
