# lidar & laser_filters & rplidar_ros 사용법

1. laser_filters, rplidar_ros 폴더 src폴더에 넣구 catkin_make
2. 라이다 연결 후 'sudo chmod 666 /dev/ttyUSB0'
3. 'roslaunch laser_filters my_laser_filter.launch'
4-1. 'roslaunch rplidar_ros rplidar.launch' rviz 안켜짐 --대회용
4-2. 'roslaunch view_rplidar.launch' rviz 켜짐 --확인용
