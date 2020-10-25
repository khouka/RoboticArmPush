#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <math.h>
#include <vector>

// Defining the joint publishers
ros::Publisher joint1_pub;
ros::Publisher joint2_pub;
ros::Publisher joint4_pub;
ros::Publisher joint6_pub;
ros::Publisher joint7_pub;

const double PI = 3.14159265359;
void base_shoulder(double cur1, double cur2, double vel1, double vel2, bool ispositioning);
void elbow_wrist(double cur4, double cur6, double vel1, double vel2, bool ispositioning);
void push_object(double vel, bool ispositioning);
double degrees2radians(double angle_in_degrees);

int main(int argc, char **argv)
{
  // Initiate new ROS node named "joint_command_node"
  ros::init(argc, argv, "joint_command_node");
  ros::NodeHandle n;
  double cur1, cur2, cur4, cur6;
  double vel, vel1, vel2;
  bool ispositioning;

  // The joint Publishers
  joint1_pub = n.advertise<std_msgs::Float64>("/ram/joint1_position_controller/command", 10); 
  joint2_pub = n.advertise<std_msgs::Float64>("/ram/joint2_position_controller/command", 10);
  joint4_pub = n.advertise<std_msgs::Float64>("/ram/joint4_position_controller/command", 10);
  joint6_pub = n.advertise<std_msgs::Float64>("/ram/joint6_position_controller/command", 10);
  joint7_pub = n.advertise<std_msgs::Float64>("/ram/joint7_position_controller/command", 10);
  // Pushing Object
  base_shoulder(0.0,0.0, degrees2radians(92)/25, degrees2radians(-11.5)/25, true);
  elbow_wrist(0.0,0.0, degrees2radians(92)/25, degrees2radians(11.5)/25, true);
  ros::Duration(1).sleep();
  push_object(0.05, true);
  ros::Duration(2).sleep();
  // Rolling Back
  push_object(0.1, false);
  ros::Duration(0.5).sleep();
  elbow_wrist(degrees2radians(92),degrees2radians(11.5), degrees2radians(92)/10, degrees2radians(11.5)/10, false);
  ros::Duration(0.5).sleep();
  base_shoulder(degrees2radians(92), degrees2radians(-11.5), degrees2radians(92)/10, degrees2radians(-11.5)/10, false);  
}
double degrees2radians(double angle_in_degrees){
      return angle_in_degrees *PI /180.0;
}
void base_shoulder(double cur1, double cur2, double vel1, double vel2, bool ispositioning){
   std_msgs::Float64 j1;
   std_msgs::Float64 j2;
   ros::Rate loop_rate(60);	
   if (ispositioning){
    for (int i=0;i<25;i++){
     j1.data = cur1 + vel1 * i;
     joint1_pub.publish(j1); 
     j2.data = cur2 + vel2 * i;
     joint2_pub.publish(j2);
     ros::Duration(0.05).sleep();  
     ros::spinOnce(); 
     loop_rate.sleep();          
   }
  }
  else{
   for (int i=0;i<10;i++){
    j1.data = cur1 - vel1 * i;
    joint1_pub.publish(j1); 
    j2.data = cur2 - vel2 * i;
    joint2_pub.publish(j2);
    ros::Duration(0.05).sleep();  
   }
  }
}
void elbow_wrist(double cur4, double cur6, double vel1, double vel2, bool ispositioning){
   std_msgs::Float64 j4;
   std_msgs::Float64 j6;
   ros::Rate loop_rate(40);
   if (ispositioning){
    for (int i=0;i<25;i++){
     j4.data = cur4 - vel1 * i;
     joint4_pub.publish(j4); 
     j6.data = cur6 + vel2 * i;
     joint6_pub.publish(j6);
     ros::Duration(0.05).sleep();  
     ros::spinOnce(); 
     loop_rate.sleep();          
   }
  }
  else{
   for (int i=0;i<11;i++){
    j4.data = cur4 - vel1 * i;
    joint4_pub.publish(j4); 
    j6.data = cur6 - vel2 * i;
    joint6_pub.publish(j6);
    ros::Duration(0.05).sleep();          
   }
  }
}
void push_object(double vel, bool ispositioning){
  std_msgs::Float64 j7;
  double start = 0.0;
  ros::Rate loop_rate(60);
  if (ispositioning){
   for (int i=0;i<10;i++){
    j7.data = start + vel * i;
    joint7_pub.publish(j7); 
    ros::Duration(0.05).sleep();  
    ros::spinOnce(); 
    loop_rate.sleep();          
   }
  }
  else{
    for (int i=0;i<5;i++){
     j7.data = start - vel * i;
     joint7_pub.publish(j7); 
     ros::Duration(0.05).sleep();  
    }
  }
}
