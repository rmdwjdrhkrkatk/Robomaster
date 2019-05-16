using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class bonus_zone : MonoBehaviour
{
    private bool activate;
    private bool activating;
    private int count;
    private float resetTime;
    private float activateTime;
    private float activatingTime;
    public string type;
    public GameObject agent;
        
    void Start()
    {
        initialize();
    }

   
    void Update()
    {
        if (Time.time > resetTime + 60)
        {
            initialize();
        }        

        if (Time.time > activateTime + 30)
        {
            activate = false;
        }

        if (activate)
        {
            agent.GetComponent<rm_agent_6>().bonus = true;
        }
        else
        {
            agent.GetComponent<rm_agent_6>().bonus = false;
        }
    }

    public void initialize()
    {
        resetTime = Time.time;
        activateTime = Time.time;
        activate = false;
        count = 2;
    }

    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.name == type)
        {
            activatingTime = Time.time;
        }        
    }

    void OnTriggerStay(Collider col)
    {        
        if (col.gameObject.name == type)
        {
            if(!activate)
                col.gameObject.GetComponent<rm_agent_6>().AddReward(1); // 비활성 시에는 밟는것 만으로도 리워드 적용
            if (Time.time > activatingTime + 5 && count > 0)
            {
                activate = true;
                activateTime = Time.time;
                count--;
                col.gameObject.GetComponent<rm_agent_6>().AddReward(col.gameObject.GetComponent<rm_agent_6>().rewards[6]);
            }
        }               
    }
}
