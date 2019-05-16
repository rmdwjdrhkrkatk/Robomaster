using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using MLAgents;

public class rm_agent : Agent
{
    public GameObject oppenent;
    public GameObject area;

    Rigidbody agentRb;
    Rigidbody oppetRb;

    bool shoot;
       
    public float turnSpeed = 300;
    public float moveSpeed = 2;
    public float fireRate = 5;
    float shotTime; 
    float hittedEffectTime;
    bool hitted;

    
    public Material normalMaterial;
    public Material hittedMaterial;    
    public GameObject myLaser;    
    private RayPerception rayPer;
    public bool useVectorObs;
    public int health;
    public Vector3 firstplace;

    [Header("Reward setting")]
    [Header("Mark, Miss, Hit, wall, agent")]
    public int[] rewards = { 5, -1, -1, -1, -1 };


    // firing
    private Vector3 origin;
    private Vector3 direction;
    private float currentHitDistance;
           

    public override void InitializeAgent()
    {
        base.InitializeAgent();
        
        
        shotTime = 0;
        agentRb = GetComponent<Rigidbody>();
        oppetRb = oppenent.GetComponent<Rigidbody>();

        Monitor.verticalOffset = 1f;        
        rayPer = GetComponent<RayPerception>();        
        AgentReset();
    }

    public override void CollectObservations()
    {
        if (useVectorObs)
        {
            float rayDistance = 50f;
            float[] rayAngles = { 20f, 90f, 160f, 45f, 135f, 70f, 110f, 270f, 315f, 225f, 180f };
            string[] detectableObjects = { "agent", "wall" };

            AddVectorObs(rayPer.Perceive(rayDistance, rayAngles, detectableObjects, 0f, 0f));

            Vector3 localVelocity = transform.InverseTransformDirection(agentRb.velocity);
            
            AddVectorObs(localVelocity.x);
            AddVectorObs(localVelocity.z);

            // 추가
            AddVectorObs(transform.rotation);

            AddVectorObs(this.transform.position.x);
            AddVectorObs(this.transform.position.z);

            AddVectorObs(oppenent.transform.position.x);
            AddVectorObs(oppenent.transform.position.z);

            
            AddVectorObs(System.Convert.ToInt32(shoot));
        }
    }    

    public void MoveAgent(float[] act)
    {
        shoot = false;       

        Vector3 dirToGo = Vector3.zero;
        Vector3 rotateDir = Vector3.zero;

        if (health < 1)
        {
            Done();
            oppenent.GetComponent<rm_agent>().Done();
        }


        if (Mathf.Abs(transform.position.x) > 4 || Mathf.Abs(transform.position.z) > 2.5)
        {
            Done();
            oppenent.GetComponent<rm_agent>().Done();
        }

        

        if (Time.time > hittedEffectTime + 0.1f && hitted)
        {
            normal_agent();
        }

        bool shootCommand = false;

        if (brain.brainParameters.vectorActionSpaceType == SpaceType.continuous)
        {
            dirToGo = transform.forward * Mathf.Clamp(act[0], -1f, 1f);
            rotateDir = transform.up * Mathf.Clamp(act[1], -1f, 1f);
            //shootCommand = Mathf.Clamp(act[2], -1f, 1f) > 0.5f;            
        }
        else
        {
            var forwardAxis = (int)act[0];
            var rightAxis = (int)act[1];
            var rotateAxis = (int)act[2];
            var shootAxis = (int)act[3];

            switch (forwardAxis)
            {
                case 1:
                    dirToGo = transform.forward;
                    break;
                case 2:
                    dirToGo = -transform.forward;
                    break;
            }

            switch (rightAxis)
            {
                case 1:
                    dirToGo = transform.right;
                    break;
                case 2:
                    dirToGo = -transform.right;
                    break;
            }

            switch (rotateAxis)
            {
                case 1:
                    rotateDir = -transform.up;
                    break;
                case 2:
                    rotateDir = transform.up;
                    break;
            }
            switch (shootAxis)
            {
                case 1:
                    shootCommand = true;
                    break;
            }
        }

        if (shootCommand)
        {
            if (Time.time > shotTime + 1.0f / fireRate)
                shoot = true;
            
            //dirToGo *= 0.5f;
            //agentRb.velocity *= 0.75f;
        }

        agentRb.AddForce(dirToGo * moveSpeed, ForceMode.VelocityChange);
        transform.Rotate(rotateDir, Time.fixedDeltaTime * turnSpeed);
        

        if (agentRb.velocity.sqrMagnitude > 25f) // slow it down
        {
            agentRb.velocity *= 0.95f;
        }

        if (shoot)
        {
            shotTime = Time.time;
            myLaser.transform.localScale = new Vector3(1f, 1f, 2f);
            Vector3 position = transform.TransformDirection(RayPerception.PolarToCartesian(25f, 90f));
            origin = transform.position;
            direction = position;
            Debug.DrawRay(transform.position, position, Color.red, 0f, true);
            RaycastHit hit;

            if (Physics.SphereCast(transform.position, 0.1f, position, out hit, 25f))
            {                
                if (hit.collider.gameObject.CompareTag("agent"))
                {
                    currentHitDistance = hit.distance;                    
                    hit.collider.gameObject.GetComponent<rm_agent>().health -= 50;
                    hit.collider.gameObject.GetComponent<rm_agent>().AddReward(rewards[2]);
                    hit.collider.gameObject.GetComponent<rm_agent>().hitted_agent();
                    AddReward(rewards[0]); //명중 리워드
                }
                else
                {
                    AddReward(rewards[1]); //불발 리워드
                }
                    
            }

        }
        else
        {
            myLaser.transform.localScale = new Vector3(0f, 0f, 0f);
        }
    }    

    void normal_agent()
    {
        hitted = false;        
        gameObject.GetComponent<Renderer>().material = normalMaterial;
    }

    void hitted_agent()
    {
        hitted = true;
        hittedEffectTime = Time.time;
        gameObject.GetComponent<Renderer>().material = hittedMaterial;
    }
    
    public override void AgentAction(float[] vectorAction, string textAction)
    {
        MoveAgent(vectorAction);
    }

    public override void AgentReset()
    {       
        shoot = false;
        agentRb.velocity = Vector3.zero;        
        myLaser.transform.localScale = new Vector3(0f, 0f, 0f);       
        transform.position = firstplace + area.transform.position;
        health = 2000;
    }

    void OnCollisionEnter(Collision collision)
    {        
        if (collision.gameObject.CompareTag("wall"))
        {
            health -= 10;
            AddReward(rewards[3]);       // 벽에 부딪침 리워드
        }
        if (collision.gameObject.CompareTag("agent"))
        {
            health -= 10;
            AddReward(rewards[4]);     // 다른 agent에 부딪침 리워드 
        }
    }    
}
