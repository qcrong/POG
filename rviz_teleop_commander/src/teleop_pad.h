#ifndef TELEOP_PAD_H
#define TELEOP_PAD_H

//所需要包含的头文件
#include <ros/ros.h>
#include <ros/console.h>
#include <rviz/panel.h>   //plugin基类的头文件
//qcrong add 
#include <QPushButton>
#include <QTextBrowser>
#include <std_msgs/Int8.h>
#include <vector>
#include "rviz_teleop_commander/targets_tag.h"		//自定义消息类型，传递要抓取的目标标签
#include "rviz_teleop_commander/grab_result.h"		//自定义消息类型，传递当前抓取的目标标签和抓取次数

class QLineEdit;

namespace rviz_teleop_commander
{
// 所有的plugin都必须是rviz::Panel的子类
class TeleopPanel: public rviz::Panel
{
// 后边需要用到Qt的信号和槽，都是QObject的子类，所以需要声明Q_OBJECT宏
Q_OBJECT
public:
  // 构造函数，在类中会用到QWidget的实例来实现GUI界面，这里先初始化为0即可
  TeleopPanel( QWidget* parent = 0 );

  // 重载rviz::Panel积累中的函数，用于保存、加载配置文件中的数据，在我们这个plugin
  // 中，数据就是topic的名称
  virtual void load( const rviz::Config& config );
  virtual void save( rviz::Config config ) const;

  // 公共槽.
public Q_SLOTS:
  // 当用户输入topic的命名并按下回车后，回调用此槽来创建一个相应名称的topic publisher
  void pubTagsTopic();

  // 内部槽.
protected Q_SLOTS:
  //void sendVel();                 // 发布当前的速度值
  //void update_Linear_Velocity();  // 根据用户的输入更新线速度值
  //void update_Angular_Velocity(); // 根据用户的输入更新角速度值
  void updateTopic();             // 根据用户的输入更新topic name
  void grabResultCB(const rviz_teleop_commander::grab_result::ConstPtr &msg);

  // 内部变量.
protected:
  // 目标标签输入框
  QLineEdit* output_tags_editor_;
  QString output_topic_;
  
  // 线速度值输入框
  //QLineEdit* output_topic_editor_1;
  //QString output_topic_1;
  
  // 角速度值输入框
  //QLineEdit* output_topic_editor_2;
  //QString output_topic_2;
  
  //退出按钮
  QPushButton* start_push_button;

  //输出显示框
  QTextBrowser* grabTagShow;	//当前抓取的目标标签
  QTextBrowser* grabTimesShow;	//当前目标标签的抓取次数

  // ROS的publisher，用来发布要抓取的目标物的标签
  ros::Publisher tags_publisher_;

  //ROS的subscriber,用来接收当前抓取的目标物的标签和抓取次数
  ros::Subscriber grab_result_sub;	

  // The ROS node handle.
  ros::NodeHandle nh_;

  // 当前保存的线速度和角速度值
  float linear_velocity_;
  float angular_velocity_;

  //要发布的消息
  rviz_teleop_commander::targets_tag tagsMsg;	//抓取目标
 
  //接收的消息
  //rviz_teleop_commander::grab_result grabResultMsg;	//抓取状态
};

} // end namespace rviz_teleop_commander

#endif // TELEOP_PANEL_H
