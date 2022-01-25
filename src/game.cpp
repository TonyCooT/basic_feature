#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "basic_feature/check_step.h"
#include <cstdlib>  // rand(), srand()
#include <ctime>    // time()
#include <string>   // to_string()

const int STEP_COUNT = 18;

static ros::Publisher g_pub;
static bool g_is_dead = false;

bool isChecked(basic_feature::check_step::Request& req, basic_feature::check_step::Response& res);
void chatterCallback(const std_msgs::Int8& msg);
int rightStep();

int main(int argc, char **argv)
{
    ros::init(argc, argv, "check_step_server");
    ros::NodeHandle n;
	
    std::string topic_name, service_name;
    n.param<std::string>("topic_name", topic_name, "chatter");
    n.param<std::string>("service_name", service_name, "check_step");
    
    ros::ServiceServer service = n.advertiseService(service_name, isChecked);
    g_pub = n.advertise<std_msgs::Int8>(topic_name, 10);
    ros::Subscriber sub = n.subscribe(topic_name, 10, chatterCallback);     
    
    std::srand(std::time(0));
    ROS_INFO("Ready to play the game, please enter 0 or 1 \n");
    
    while(ros::ok())
    {
        if(g_is_dead)
            ros::shutdown();
        ros::spinOnce();
    }
    
    return 0;
}

bool isChecked(basic_feature::check_step::Request& req, basic_feature::check_step::Response& res)
{
    if (req.step != 0 && req.step != 1)
    {
        res.result = "false";
        return true;
    }
    
    if (req.step == rightStep())
    {
        res.result = "move next";
        std_msgs::Int8 info;
        info.data = req.step;
        g_pub.publish(info);
    }
    else
    {
        res.result = "dead";
        g_is_dead = true;
    }
    
    return true;
}

void chatterCallback(const std_msgs::Int8& msg)
{
    static std::string output;
    
    if (output.size() < (STEP_COUNT - 1))
    {
        output += std::to_string(msg.data);
        ROS_INFO("%s \n", output.c_str());
    }
    else
    {
        ROS_INFO("congratulations, you won \n");
        output.clear();
    }
}

int rightStep()
{
    return (std::rand() % 2);
}
