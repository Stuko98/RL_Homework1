#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

void joint_state_Callback(const sensor_msgs::JointState& state)
{
    for (int i=0;i<4;i++) ROS_INFO("joint %d position: %f \n",i,state.position[i]); 
}

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    //Subscriber
    ros::Subscriber subscriber = nh.subscribe("/arm/joint_states",10,joint_state_Callback);

    //Publisher
    ros::Publisher j0_publisher = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J0_controller/command", 1);
    ros::Publisher j1_publisher = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J1_controller/command", 1);
    ros::Publisher j2_publisher = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J2_controller/command", 1);
    ros::Publisher j3_publisher = nh.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J3_controller/command", 1);


    ros::Rate loopRate(10);

    while (ros::ok()) {
        std_msgs::Float64 command0, command1, command2, command3;

        command0.data = 1;
        command1.data = 1;
        command2.data = 1;
        command3.data = 1;

        ROS_INFO_STREAM(command0.data);
        ROS_INFO_STREAM(command1.data);
        ROS_INFO_STREAM(command2.data);
        ROS_INFO_STREAM(command3.data);

        j0_publisher.publish(command0);
        j1_publisher.publish(command1);
        j2_publisher.publish(command2);
        j3_publisher.publish(command3);
                
        ros::spinOnce();
        loopRate.sleep();
    }

    ros::spin();


    return 0;
}