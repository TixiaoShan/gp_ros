// Related headers:
#include "gpregressor.h"
#include "covMaterniso3.h"
#include <ros/ros.h>

//C library headers:
#include <iostream>
#include <fstream>


//C++ library headers:  NONE


//other library headers:  NONE


using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "gp_ros");
    ros::NodeHandle nh;

    int num_train = 10, train_dim = 2;
    int num_test = 10;

    GPRegressor g(100, 3, 0.01);  // g(training mean, elf,  noise level), note that noise level can be set to zero.


 	MatrixXf gp_train_x(num_train, train_dim), gp_train_label(num_train, 1), gp_test_x(num_test, train_dim);
 	MatrixXf gp_mean, gp_var;

 	for (int i=0;i<num_train;i++) {
 		gp_train_x(i,0) = i;
 		gp_train_x(i,1) = i+1;
 		gp_train_label(i) = i+3;
 	}

 	for (int i=0;i<num_test;i++) {
 		gp_test_x(i,0) = i-1;
 		gp_test_x(i,1) = i+1.2;
 	}

 	cout << "turning in gp trainning data.." << endl;
 	g.train(gp_train_x, gp_train_label);

 	cout << "performing gp testing.."  << endl;
 	g.test(gp_test_x, gp_mean, gp_var);


 	for (int i=0;i<num_test;i++) {
 		cout << "mean: " << gp_mean(i) << " ,  covr: " << gp_var(i) << endl;
 	}
 	
 	cout << "GP done." << endl;

 	while(ros::ok()) {
 		ros::spin();
 	}
}