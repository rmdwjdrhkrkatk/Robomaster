using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using MLAgents;
using UnityEngine.UI;

public class rm_agent_full : Agent
{
    public GameObject oppenent1;
    public GameObject oppenent2;
    public GameObject ally;
    public GameObject area;

    Rigidbody agentRb;
    Rigidbody oppetRb1;
    Rigidbody oppetRb2;
    Rigidbody allyRb;

    bool shoot;
    bool dead;
       
    public float turnSpeed = 100;
    public float moveSpeed = 1;
    public float fireRate = 5;
    float shotTime; 
    float hittedEffectTime;
    bool hitted;

    public Material normalMaterial;
    public Material hittedMaterial;
    public Material DeadMaterial;
    public GameObject myLaser;    
    private RayPerception rayPer;
    public bool useVectorObs;
    public int health;
    public Vector3 firstplace;    

    // 명중, 피격, 벽 충돌, 로봇 충돌, 승리, 죽은 거 때림, 팀킬
    int[] rewards = { 20, -1, -1, -1, -1, 200, -1, -5};


    // firing
    private Vector3 origin;
    private Vector3 direction;
    private float currentHitDistance;
           

    public override void InitializeAgent()
    {
        base.InitializeAgent();

        dead = false;
        shotTime = 0;
        agentRb = GetComponent<Rigidbody>();
        oppetRb1 = oppenent1.GetComponent<Rigidbody>();
        oppetRb2 = oppenent2.GetComponent<Rigidbody>();
        allyRb = ally.GetComponent<Rigidbody>();

        Monitor.verticalOffset = 1f;        
        rayPer = GetComponent<RayPerception>();        
        AgentReset();
    }

    public override void CollectObservations()
    {
        if (useVectorObs)
        {
            float rayDistance = 50f;
            float[] rayAngles = { 0f, 22.5f, 45f, 67.5f, 90f, 112.5f, 135f, 157.5f, 180f, 202.5f, 225f, 247.5f, 270f, 292.5f, 315f, 337.5f, 360f, 382.5f };
            string[] detectableObjects = { "agent_red", "agent_blue", "wall" };

            AddVectorObs(rayPer.Perceive(rayDistance, rayAngles, detectableObjects, 0f, 0f));

            Vector3 localVelocity = transform.InverseTransformDirection(agentRb.velocity);
            
            AddVectorObs(localVelocity.x);
            AddVectorObs(localVelocity.z);

            // 추가
            AddVectorObs(transform.rotation);

            AddVectorObs(this.transform.position.x);
            AddVectorObs(this.transform.position.z);

            AddVectorObs(oppenent1.transform.position.x);
            AddVectorObs(oppenent1.transform.position.z);
            AddVectorObs(oppenent2.transform.position.x);
            AddVectorObs(oppenent2.transform.position.z);
            AddVectorObs(ally.transform.position.x);
            AddVectorObs(ally.transform.position.z);

            AddVectorObs(System.Convert.ToInt32(shoot));
            AddVectorObs(System.Convert.ToInt32(oppenent1.GetComponent<rm_agent_full>().dead));
            AddVectorObs(System.Convert.ToInt32(oppenent2.GetComponent<rm_agent_full>().dead));
        }
    }    

    public void MoveAgent(float[] act)
    {
        shoot = false;       

        Vector3 dirToGo = Vector3.zero;
        Vector3 rotateDir = Vector3.zero;

        if (health < 1)
        {
            dead = true;
            Dead_agent();
            if (ally.GetComponent < rm_agent_full>().health < 1)
            {
                Done();
                ally.GetComponent<rm_agent_full>().Done();
                oppenent1.GetComponent<rm_agent_full>().Done();
                oppenent2.GetComponent<rm_agent_full>().Done();

                oppenent1.GetComponent<rm_agent_full>().AddReward(rewards[5]);
                oppenent2.GetComponent<rm_agent_full>().AddReward(rewards[5]);
            }
        }       

        if (!dead)
        {           

            if (Mathf.Abs(transform.position.x) > 4 || Mathf.Abs(transform.position.z) > 2.5)
            {
                Done();
                oppenent1.GetComponent<rm_agent_full>().Done();
                oppenent2.GetComponent<rm_agent_full>().Done();
                ally.GetComponent<rm_agent_full>().Done();
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
                    //case 0:
                      //  dirToGo = new Vector3(0, 0, 0);
                      //  break;
                    case 1:
                        dirToGo = transform.forward;
                        break;
                    case 2:
                        dirToGo = -transform.forward;
                        break;
                    
                }

                switch (rightAxis)
                {
                   // case 0:
                        //dirToGo = new Vector3(0, 0, 0);
                        //break;
                    case 1:
                        dirToGo = transform.right;
                        break;
                    case 2:
                        dirToGo = -transform.right;
                        break;
                }

                switch (rotateAxis)
                {
                    //case 0:
                      //  rotateDir = new Vector3(0, 0, 0);
                      //  break;
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
                    if (hit.collider.gameObject.CompareTag("agent_red") || hit.collider.gameObject.CompareTag("agent_blue"))
                    {
                        currentHitDistance = hit.distance;
                        hit.collider.gameObject.GetComponent<rm_agent_full>().health -= 50;
                        hit.collider.gameObject.GetComponent<rm_agent_full>().hitted_agent();
                        hit.collider.gameObject.GetComponent<rm_agent_full>().AddReward(rewards[2]); //피격 리워드

                        if (hit.collider.gameObject != ally)
                        {
                            if (hit.collider.gameObject.GetComponent<rm_agent_full>().dead)
                                AddReward(rewards[6]); // 죽은 놈 때림
                            else
                                AddReward(rewards[0]); //명중 리워드                            
                        }
                            
                        else
                            AddReward(rewards[7]); // 팀킬 리워드
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
        else
        {
            agentRb.AddForce(new Vector3(0,0,0), ForceMode.VelocityChange);            
            transform.Rotate(new Vector3(0, 0, 0), Time.fixedDeltaTime * turnSpeed);
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

    void Dead_agent()
    {
        gameObject.GetComponent<Renderer>().material =DeadMaterial;
    }
    
    public override void AgentAction(float[] vectorAction, string textAction)
    {
        MoveAgent(vectorAction);
    }

    public override void AgentReset()
    {       
        shoot = false;
        dead = false;
        normal_agent();
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
        if (collision.gameObject.CompareTag("agent_red") || collision.gameObject.CompareTag("agent_blue"))
        {
            health -= 10;
            AddReward(rewards[4]);     // 다른 agent에 부딪침 리워드 
        }
    }    
}
