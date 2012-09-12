#ifndef CCNY_RGBD_FEATURE_DETECTOR_H
#define CCNY_RGBD_FEATURE_DETECTOR_H

#include <vector>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <sensor_msgs/image_encodings.h>
#include <pcl/ros/conversions.h>
#include <pcl_ros/point_cloud.h>
#include <visualization_msgs/Marker.h>

#include "ccny_rgbd/structures/rgbd_frame.h"
#include "ccny_rgbd/rgbd_util.h"

namespace ccny_rgbd
{

class RGBDFrame;

class FeatureDetector
{
  public:

    FeatureDetector(ros::NodeHandle nh, ros::NodeHandle nh_private);
    virtual ~FeatureDetector();

    void findFeatures(RGBDFrame& frame);
    inline double findFeaturesTimed(RGBDFrame& frame);

    virtual void findFeatures(RGBDFrame& frame, const cv::Mat * input_img) = 0;

    inline int getSmooth() const;
    inline double getMaxRange() const;

    inline void setSmooth(int smooth);
    inline void setMaxRange(double max_range);

  protected:

    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    bool compute_descriptors_;

  private:

    ros::Publisher features_publisher_;
    ros::Publisher covariances_publisher_;

    int smooth_;
    double max_range_;
    bool show_keypoints_;
    bool publish_features_;
    bool publish_covariances_;

    //bool mask_created_;
    //cv::Mat mask_img_;
    //int mask_w_;

    void publishCovariances(RGBDFrame& frame);
};

} //namespace ccny_rgbd

#endif // CCNY_RGBD_FEATURE_DETECTOR_H