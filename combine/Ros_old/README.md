# RobomasterAIChallenge




<1.3>global, local motion planner를 추가하였습니다. 이외에도 gazebo상의 모델의 footprint 좌표가 잘못 설정되어 회전시 localizing이 흐트러지던 오류를 수정하였으며 경기장 모델을 실제 규격에 맞춰 조정하였습니다.
![alt text](https://github.com/woong164/RobomasterAIChallenge/blob/master/Images/ezgif-5-595d31b957e2.gif)



<1.2>amcl기능을 추가했습니다. roboin_simulation 패키지의 roboin_amcl.launch로 확인할 수 있습니다.

![alt text](https://github.com/woong164/RobomasterAIChallenge/blob/master/Images/ezgif-5-6cb57719c867.gif)




<1.1> mapping기능 추가했습니다. roslaunch roboin_simulation robomaster_mapping.launch 로 확인하실 수 있습니다.
ROS naviagation stack이 필요합니다. gmapping알고리즘 사용하였습니다.
![alt text](https://github.com/woong164/RobomasterAIChallenge/blob/master/Images/Screenshot%20from%202019-01-15%2016-37-37.png)















<1.0>
roboin_description 패키지는 로봇의 상태 정보와 및 simulation world의 정보가 담겨있습니다.
로봇의 상태는 urdf format, gazebo에 사용될 world는 sdf format으로 작성되어있으며 모델의 mesh와 texture를 별도의 폴더에 저장해두었습니다.

roboin_simulation에는 simulation관련 launch file과 rviz등 시각화 툴의 preset을 저장해 두었습니다. 또한 gazebo를 종료시 gzserver가 정상종료되지 않아 다시 gazebo를 실행하면 gzclient와 연동되지 않는 버그가 있으므로 launch파일을 통해 시작시 자동으로 gzserver 프로세스를 죽이는 bash script를 추가하였습니다.

실질적으로 사용할 launch file은 spawn.launch가 되겠습니다. 현재는 robomaster 규격의 경기장과 roboin 로봇 한대에 뎁스캠(키넥트,리얼센스)와 360도 lidar를 구현하였습니다. 일단 구동 kinematics는 differential drive모델을 사용하였으며 추후 mecanum wheel로 변경할 예정입니다. 필요하시면 armor module도 추가하도록 하겠습니다.


사용방법으로 roslaunch roboin_simulation spawn.launch를 실행하시면 3개의 gui가 뜹니다. xterm 창에 뜨는 CLI상에 키보드 입력을 하면 로봇이 움직입니다. i키를 누르시면 전진합니다. 나머지 키는 설명을 참조하세요.

두 번째 창은 RVIZ로 현재는 camera image와 로봇의 odometry와 laser scan값을 화면에 표시하게 설정해두었습니다. 다만 일단 fixed frame을 로봇 기준으로 설정해둬서 odometry는 큰 의미가 없습니다. 조만간 수정하겠습니다.

마지막 창은 gazebo로 로봇의 3차원 물리엔진 시뮬레이션입니다. ode엔진을 적용하였습니다.

navigation과 slam을 올리려했으나 예상보다 늦어져 일단 시뮬레이션 환경만 먼저 올립니다.
