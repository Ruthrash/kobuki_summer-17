# Mobile robot platform using kobuki to test algorithms for Pursuit-evasion games
===
Description of the setup used to test the pursuit-evasion games algorithms.

Hardware  requirements
===
+ Yujin kobuki robot

+ Raspberry pi3 (along with a wifi dongle and a memory card)

+ A computer that will act as ROS a master(with matlab installed)

Raspberry pi 
===
+ Use the image file in the repository to run Ubuntu Mate 16.04.02 in the Pi.

+ Install ROS kinetic kame referring [here](http://www.instructables.com/id/How-to-Install-ROS-Kinetic-on-Raspberry-Pi-3/)

+ Once ROS is setup, store the kobuki package from the repository in /home/"catkin workspace name"/src

+ Install the kobuki package for ROS kinetic from [here](http://wiki.ros.org/kobuki/Tutorials/Installation)

SSH with the raspberry pi 
===
+ First find the ip address of the raspberry pi referring [here](https://www.raspberrypi.org/documentation/remote-access/ip-address.md)

+ Now in a terminal in the computer run,
`$ ssh pi_username@'ip_address_found_before'`

Description of the package and it's usage
===
+ To use the package, run
`$ roslaunch kobuki kobuki_node.launch`

+ Run the matlab code in the repository and refer [here](https://in.mathworks.com/hardware-support/robot-operating-system.html) for assisstance.
          1. If you don't have Matlab on your linux system you can have matlab running in your windows PC (as a node) and run the linux PC as the ROS master

+The kobuki node subscribes the goal from the matlab code, and the odometry from the odometry published by the inbuilt kokbuki node. With these information it calculates the velocity commands (v,w) and publishes it to the motors.
          
 
