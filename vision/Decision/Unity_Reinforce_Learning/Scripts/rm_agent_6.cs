using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using MLAgents;
using UnityEngine.UI;

public class rm_agent_6 : Agent
{
    public GameObject oppenent;
    public GameObject area;    

    Rigidbody agentRb;
    Rigidbody oppetRb;

    bool shoot;
    bool detect_agent_;
    private int type;

    public float turnSpeed = 300;
    public float moveSpeed = 2;
    public float fireRate = 5;
    float startTime;
    float shotTime; 
    float hittedEffectTime;
    float winnerTime;
    float confrontTime;
    bool hitted;
    bool winnerTextTrue;

    public Material normalMaterial;
    public Material hittedMaterial;    
    public GameObject myLaser;    
    private RayPerception rayPer;
    private RayPerception rayPer2; //
    public bool useVectorObs;
    public int health;
    public int bullets;
    public Vector3 firstplace;
    public Text winner;

    public bool bonus;
    

    // 명중, 불발, 피격, 벽 충돌, 로봇 충돌, 승리, 보너스 점령, 재장전 성공, 잔탄발사
    // 10th attempt { 20, -1, -1, -1, -1, 200, 0, 0, 0 }
    // 11st attempt  { 20, -1, -1, -1, -1, 200, 100, 100, -1  }
    public int[] rewards = {20, -1, -1, -1, -1, 200, 100, 100, -1};

    // firing
    private Vector3 origin;
    private Vector3 direction;
    private float currentHitDistance;
           
    // 유니티 rigidbody 세팅 및 초기화
    public override void InitializeAgent()
    {
        base.InitializeAgent();       
        
        
        agentRb = GetComponent<Rigidbody>();
        oppetRb = oppenent.GetComponent<Rigidbody>();

        Monitor.verticalOffset = 1f;        
        rayPer = GetComponent<RayPerception>(); 
        rayPer2 = GetComponent<RayPerception>(); //
        AgentReset();
    }

    // 관측하는 값
    public override void CollectObservations()
    {
        if (useVectorObs)
        {
            // 22.5도 간격으로 18방향 관측
            float rayDistance = 50f;
            float[] rayAngles = { 0f, 22.5f, 45f, 67.5f, 90f, 112.5f, 135f, 157.5f, 180f, 202.5f, 225f, 247.5f, 270f, 292.5f, 315f, 337.5f, 360f, 382.5f };
            string[] detectableObjects = {"wall"};
            Vector3 localVelocity = transform.InverseTransformDirection(agentRb.velocity);

            // red면 0, blue 면 1
            if (this.name == "red")
                type = 0;
            else
                type = 1;
            AddVectorObs(type);

            // 현재 잔탄 수, 정면에 적이 있는지 여부
            AddVectorObs(bullets);
            AddVectorObs(System.Convert.ToInt32(detect_agent_));
            
            // 관측 (레이저 형태로)
            AddVectorObs(rayPer.Perceive(rayDistance, rayAngles, detectableObjects, 0f, 0f));           
            
            // agent의 속도, 회전 방향, 위치, 적의 위치
            AddVectorObs(localVelocity.x);
            AddVectorObs(localVelocity.z);           
            AddVectorObs(transform.rotation.y);
            AddVectorObs(transform.position.x);
            AddVectorObs(transform.position.z);
            AddVectorObs(oppenent.transform.position.x);
            AddVectorObs(oppenent.transform.position.z);
            AddVectorObs(oppenent.transform.rotation.y);

            // 시간
            AddVectorObs(Time.time - startTime);
        }
    }

    // 계속 반복 실행되는 함수
    public void MoveAgent(float[] act)
    {
        shoot = false;
        Vector3 dirToGo = Vector3.zero;
        Vector3 rotateDir = Vector3.zero;

        // 서로 대치할 때 리워드를 주나, 0.2초에 한 번에 최대이며 총알이 없으면 주지 않음.
        detect_agent_ = detect_agent();
        if (detect_agent_ && Time.time > confrontTime + 0.2 && bullets > 0)
        {
            AddReward(1f);
        }

        // bonus 시 상부에 흰색 네모 띄우기
        if (!bonus)
        {
            transform.Find("bonus_cube").gameObject.SetActive(false);
        }
        else
            transform.Find("bonus_cube").gameObject.SetActive(true);

        // 체력이 0이 되었을 때 초기화
        if (health < 1)
        {
            Done();
            oppenent.GetComponent<rm_agent_6>().Done();
            oppenent.GetComponent<rm_agent_6>().AddReward(rewards[5]); // 승리 리워드
            //print(oppenent);
            winner.text = oppenent.ToString();
            winnerTime = Time.time;
            winnerTextTrue = true;
        }

        if (Time.time > winnerTime + 2.0f && winnerTextTrue)
        {
            winner.text = "";
            winnerTextTrue = false;
        }
        // 경기장에서 벗어나거나 5분 이상 경시 시 리셋
        if (Mathf.Abs(transform.position.x) > 4 || Mathf.Abs(transform.position.z) > 2.5 || Time.time > startTime + 300)
        {
            Done();
            oppenent.GetComponent<rm_agent_6>().Done();
        }

        // 피격 시 0.1초간 흰색으로 바뀌었다 복귀
        if (Time.time > hittedEffectTime + 0.1f && hitted)
        {
            normal_agent();
        }

        // 조종/발사 커맨드
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
                case 0:
                    rotateDir = new Vector3 (0,0,0);
                    break;
                case 1:
                    rotateDir = -transform.up;
                    break;
                case 2:
                    rotateDir = transform.up;
                    break;
            }
        }

        // 실제 이동하는 코드
        agentRb.AddForce(dirToGo * moveSpeed, ForceMode.VelocityChange);
        transform.Rotate(rotateDir, Time.fixedDeltaTime * turnSpeed);

        // 최고속도 제한
        if (agentRb.velocity.sqrMagnitude > 25f)
        {
            agentRb.velocity *= 0.95f;
        }

        // 발사 커맨드

        Vector3 position = transform.TransformDirection(RayPerception.PolarToCartesian(25f, 90f));
        origin = transform.position;
        direction = position;
        RaycastHit hit;

        // 히트스캔 방식 발사
        if (Time.time > shotTime + 0.1)
        { 
            if (Physics.SphereCast(transform.position, 0.1f, position, out hit, 25f))
            {
                if (hit.collider.gameObject.CompareTag("agent") && bullets > 0)
                {
                    bullets--;
                    myLaser.transform.localScale = new Vector3(1f, 1f, 2f);
                    Debug.DrawRay(transform.position, position, Color.red, 0f, true);
                    shotTime = Time.time;

                    currentHitDistance = hit.distance;

                    AddReward(rewards[0]); //명중 리워드

                    // 상대가 보너스를 가지고 있을 경우 방어력 보너스 부여
                    if (!hit.collider.gameObject.GetComponent<rm_agent_6>().bonus)
                        hit.collider.gameObject.GetComponent<rm_agent_6>().health -= 50;
                    else
                        hit.collider.gameObject.GetComponent<rm_agent_6>().health -= 25;

                    hit.collider.gameObject.GetComponent<rm_agent_6>().AddReward(rewards[2]); //  피격 리워드
                    if (hit.collider.gameObject.GetComponent<rm_agent_6>().bullets < 1)
                        hit.collider.gameObject.GetComponent<rm_agent_6>().AddReward(rewards[2] * 2); // 총알없을 때 피격 패널티 ×2 -> 회피 학습이 가능할 것인가?

                    hit.collider.gameObject.GetComponent<rm_agent_6>().hitted_agent();                    
                }
            }            
        }
        else
        {
            myLaser.transform.localScale = new Vector3(0f, 0f, 0f);
        }
    }    

    bool detect_agent()
    {
        // 전면 시야각 30도로 상대를 포착
        float[] angle_list = new float[] { 87.5f, 75f, 80f, 85f, 90f, 95f, 100f, 105f, 92.5f };
        RaycastHit hit;
        bool result = false;
        
        foreach (float item in angle_list)
        {
            Vector3 position = transform.TransformDirection(RayPerception.PolarToCartesian(25f, item));
            origin = transform.position;
            direction = position;
            Debug.DrawRay(transform.position, position, Color.blue, 0f, true);

            if(Physics.SphereCast(transform.position, 0.1f, position, out hit, 25f))
            {
                if (hit.collider.gameObject.CompareTag("agent"))
                {
                    result = true;                   
                }
            }                
        }

        return result;
    }

    // 평소 색
    void normal_agent()
    {
        hitted = false;        
        gameObject.GetComponent<Renderer>().material = normalMaterial;
    }

    // 맞았을 때 색
    void hitted_agent()
    {
        hitted = true;
        hittedEffectTime = Time.time;
        gameObject.GetComponent<Renderer>().material = hittedMaterial;
    }
    
    // 조종 커맨드 실행
    public override void AgentAction(float[] vectorAction, string textAction)
    {
        MoveAgent(vectorAction);
    }

    public override void AgentReset()
    {       
        shoot = false;
        shotTime = 0;        
        startTime = Time.time;
        agentRb.velocity = Vector3.zero;        
        myLaser.transform.localScale = new Vector3(0f, 0f, 0f);       
        transform.position = firstplace + area.transform.position;
        health = 2000;
        bullets = 50; // 일단 200발로 시작해보자.
        area.GetComponent<initialize_field>().initialize_field_function();
        confrontTime = Time.time;
    }

    // 충돌 시
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
