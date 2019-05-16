using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class health_report_6 : MonoBehaviour
{

    public GameObject agent;
    public Text text;
    public string name;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        text.text = name + agent.GetComponent<rm_agent_6>().health.ToString() + " / bullet : " + agent.GetComponent<rm_agent_6>().bullets.ToString();
    }
}