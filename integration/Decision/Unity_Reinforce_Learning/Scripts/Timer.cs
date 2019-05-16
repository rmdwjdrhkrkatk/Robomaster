using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    private float startTime;
    public Text text;
    
    // Start is called before the first frame update
    void Start()
    {
        initialize();
    }

    // Update is called once per frame
    void Update()
    {
        text.text = Mathf.Round(Time.time - startTime).ToString();
    }

    public void initialize()
    {
        startTime = Time.time;
    }
}
