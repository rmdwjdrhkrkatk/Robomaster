# 개요
RoboRts의 패키지들을 사용하기 위한 인터페이스
- RoboRTS decision 패키지의 behavior들을 사용할 수 있게 함

# 설치
- 우분투 버전에 맞는 ros 설치 
- (우분투18.04: http://wiki.ros.org/melodic/Installation/Ubuntu 우분투16.04: http://wiki.ros.org/kinetic/Installation)
- sudo apt install ros-<distro>-navigation  (distro는 자신의 ros version 예)kinetic, melodic...)
- sudo apt install xterm
- 자신의 catkin workspace (catkin_ws 등)로 이동    예) cd ~/catkin_ws
- catkin_ws/src에 모든 폴더랑 cmakelist 복사
- cd ~/catkin_ws && catkin_make
- 자신의 ros version이 kinetic kame인 경우 roborts_planning package의 local_planner/time_elastic_band 폴더를 기존 roborts의 해당 폴더로 덮어쓰기해야 빌드 됨(사실 그냥해도 빌드될 수도 있음)
  
# Quickstart
- 커맨드라인에 roslaunch icra_roboin_bringup stage_behavior.launch 입력
- 쉘에 세개의 창이 뜸 (stage, rviz, xterm)
- stage는 로봇 시뮬레이션(파란색:로봇, 빨간색:장애물)
- rviz에서는 현재 로봇의 costmap, odometry, path plan등을 시각화해서 확인할 수 있음
- xterm에 적혀있는 숫자를 입력하면 해당 behavior를 테스트할 수 있음. 7번은 모든 작업 취소
- 현재 backboot, patrol, goal, 테스트가능
- goal behavior는 rviz에 2d nav goal 버튼으로 목표를 지정해주면 그쪽으로 이동하는 방식으로 테스트가능



# <Feb 27, 2019>
변경사항
- ros melodic에서 빌드할 수 있게 일부 코드(teb local planner 의 g2o알고리즘 코드 등) 수정

추가 사항
- roborts_decision 패키지에 behavior interface를 추가
- icra_roboin_bringup 패키지 추가 (런치파일, 파라미터, rviz 설정, map file등)
- icra_roboin_control 패키지 추가 (fake enemy pose publisher, behavior selector 등 추가)
- icra_roboin_msg 패키지 추가 (behavior interface 와 통신하기 위한 메시지)
- 그 외에 ros navigation stack의 move_base를 통해 dwa planner 테스트 가능, 관련 파라미터 최적화해둠


