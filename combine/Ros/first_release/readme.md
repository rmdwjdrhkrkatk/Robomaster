# 사용법
1. 로스 설치
2. sudo apt install ros-kinetic-navigation
3. sudo apt install libgoogle-glog-dev
4. python 2 버전 주피터노트북 설치 (pip install jupyter 하면 될듯?)
5. scipy 설치
6. 로스가 python 2에서 돌아가서 3랑 호환안됨. 호환되게 할 방법 알아보겠음 일단은 python2로 써야함. 그리고 virtualenv등은 로스땜에 쓰기 좀 어려움
7. catkin make해주고 (하는법은 로스 설치 참조)
8. roslaunch icra_roboin_simulation referee_1vs1.launch
9. 일단 수동테스트해보고싶으면 rosrun icra_roboin_decision manual_command.py
10. 강화학습용 api는 icra_roboin_decision/scripts에 HowToUse.ipynb (주피터노트북으로 키면됨) 참조
11. 질문사항은 유현우 010-9451-3579 로
