#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define NON_MATLAB_PARSING
#define MAX_EXT_API_CONNECTIONS 255

extern "C" {
#include "../../programming/remoteApi/extApi.h"
#ifdef _Included_extApiJava
    #include "extApiJava.h"
#endif
}

class Sim_client{
	private:

		ros::NodeHandle nh;
		int _clientID = -1;			// ID格納用変数
		int ID ;			// ID格納用変数
		int _portNb = 19999;		// 使用するポートの番号．V-REP側と合わせる
	public:
		Sim_client();
		~Sim_client();
		void conect_server();

};

Sim_client::Sim_client(){
}
Sim_client::~Sim_client(){
	simxFinish(_clientID);
}
void Sim_client::conect_server(){
	// サーバーと接続されるまで繰り返す
	while (_clientID == -1) {
		ROS_INFO_STREAM(_clientID<<"notconecting");
		//_clientID = simxStart((simxChar*)"127.0.0.1", _portNb, true, true, 2000, 5);
		_clientID = simxStart((simxChar*)"192.168.11.38", _portNb, true, true, 2000, 5);
	}
	this->ID = _clientID;
	ROS_INFO_STREAM("conecting clientID:"<<_clientID);

}

int main(int argc, char** argv) {
	ros::init (argc, argv, "img_detect");
	Sim_client client ;
	ros::Rate loop(10);

	int time_ms = 0;			// シミュレーション時間
	int Joint_handle;			// 関節のハンドル格納用変数

	while(ros::ok()){
		client.conect_server();
	}
return 0;
}
/*
   simxGetObjectHandle(_clientID, "Joint1", &Joint_handle, simx_opmode_blocking);		// ジョイントのハンドルを取得
   while (simxGetConnectionId(_clientID) != -1) {
   simxSetJointTargetPosition(_clientID, Joint_handle, 45.0*M_PI / 180.0 * sin(2.0*M_PI*time_ms/1000.0), simx_opmode_oneshot);		// ジョイントの角度の目標値を設定

   time_ms += 10;
   extApi_sleepMs(10);

   }
   */
