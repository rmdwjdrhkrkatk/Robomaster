using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class initialize_field : MonoBehaviour
{
    public GameObject red_reload;
    public GameObject blue_reload;
    public GameObject red_rein;
    public GameObject blue_rein;
    public GameObject timer;    

    public void initialize_field_function()
    {
        red_reload.GetComponent<reload_zone>().initialize();
        blue_reload.GetComponent<reload_zone>().initialize();
        red_rein.GetComponent<bonus_zone>().initialize();
        blue_rein.GetComponent<bonus_zone>().initialize();
        timer.GetComponent<Timer>().initialize();
    }

}
