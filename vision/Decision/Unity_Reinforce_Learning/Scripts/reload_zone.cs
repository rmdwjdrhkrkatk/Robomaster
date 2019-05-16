using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class reload_zone : MonoBehaviour
{    
    public GameObject agent;
    public string type;
    private float startTime;
    private bool active;
   
    void Start()
    {
        initialize();
    }


    void Update()
    {
        if (Time.time > startTime + 60)
        {
            active = true;
            startTime = Time.time;
        }
    }

    public void initialize()
    {
        startTime = Time.time;
        active = false;
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.name == type)
        {
            if (active)
            {
                col.gameObject.GetComponent<rm_agent_6>().bullets += 50;
                col.gameObject.GetComponent<rm_agent_6>().AddReward(col.gameObject.GetComponent<rm_agent_6>().rewards[7]);
                active = false;
            }           
        }
    }    
}
