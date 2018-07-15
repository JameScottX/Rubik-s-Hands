#ifndef COLORHANDLE_H
#define COLORHANDLE_H

#include <QObject>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QPixmap>
#include <QThread>
#include <QTimer>
#include "serial.h"


#define IMAGEWID   400
#define IMAGEHEIGHT  400

//#define IMAGEAREA_RL_WIDTH  140
//#define IMAGEAREA_HEIGHT   160

#define TRUE_IMAGEWID   352
#define TRUE_IMAGEHEIGHT  288

#define gen3  1.732050808
#define gen1_3  0.5773503

#define PARAMS_H     80
#define PARAMS_S     100
#define PARAMS_V     120

#define RED      0
#define GREEN    1
#define BLUE     2
#define YELLOW   3
#define CHE      4
#define WHITE    5
#define NOTHING  8



class colorhandle:public QObject
{
    Q_OBJECT

public:

    explicit colorhandle(QObject *parent =NULL);

    cv::VideoCapture capture_f;
    cv::VideoCapture capture_b;

    void cameraInit();
    cv::Mat getFrame_f();
    cv::Mat getFrame_b();
    void imageHandle_f();
    void imageHandle_b();
    QImage mat2QImage(cv::Mat& mat);

    cv::Mat frame_f,frame_b;
    cv::Mat imageModel_F;
    cv::Mat imageModel_B;

    //int element_[6][9][6];

    char tmp_element[6][9];

    bool temp_show = false;

    cv::Mat splitColor(cv::Mat tempIge);
    cv::Mat lines_inside_area(cv::Mat tempIge);
    std::pair<cv::Mat,char* > getPart(const cv::Mat tempIge);
    cv::Mat getPart2(const cv::Mat tempIge);
    cv::Mat getPart3(const cv::Mat tempIge);
    short length_part2 = 200/3;
    short length_part3 = 200/6;

    void mWrapHandle(cv::Mat imgGet,std::vector<cv::Point2f> vecPoint,cv::Mat partImgeOut);
    cv::Mat  mwrap_area_handle_last(cv::Mat imgGet);
    char judeg_matrix(cv::Point pit);

    char judge_pix(cv::Vec3b pix_get);
    char judge_pix2(cv::Vec3b pix_get);

    char part_info[9];

//注释为原来方案
//    cv::Point center ;
//    cv::Point pleft ;
//    cv::Point pright;
//    cv::Point pdown;
//    cv::Point lr_uPoint;
//    cv::Point ld_lPoint;
//    cv::Point rd_rPoint;

//    std::vector<cv::Point2f>U_l_area_corner;
//    std::vector<cv::Point2f>U_u_area_corner;
//    std::vector<cv::Point2f>U_r_area_corner;
//    std::vector<cv::Point2f>D_u_area_corner;
//    std::vector<cv::Point2f>D_l_area_corner;
//    std::vector<cv::Point2f>D_r_area_corner;

    short IMAGEAREA_RL_WIDTH = 91;
    short IMAGEAREA_HEIGHT  = 151;

    cv::Point _L_U[2];
    cv::Point _L_D[2];
    cv::Point _C_U[2];
    cv::Point _C_D[2];
    cv::Point _R_U[2];
    cv::Point _R_D[2];

    std::vector<cv::Point2f>U_L_area_corner;
    std::vector<cv::Point2f>U_R_area_corner;
    void point_Config(short x_ =0,short y_ =0,double size_ =0 );

    std::vector<cv::Point2f>D_L_area_corner;
    std::vector<cv::Point2f>D_R_area_corner;
    void point_Config2(short x_=0 ,short y_=0 ,double size_ =0);

    void point_Config3();

    CvFont fontcompare;
    cv::Vec3b getPartAeraPix(cv::Mat tempIge,cv::Point target);
    cv::Vec3b getPartAeraHSV(const cv::Mat tempIge,cv::Point target);

private:

    QTimer *rfsh =new QTimer();

    char suf[6][9];

    bool camera_f_stop=false;
    bool camera_b_stop  =false;

    char pix_val_gal = 50;
    short area_gap =620;
    short threshold_gap = 15;


    short EXPOSURE_ = -8;
    short SATURATION_ = 72;
    short CONTRAST_ = 12;
    short BRIGHTNESS_ = 15;
    short HUE_param_   = -562;


    short wrap_length = 200;
    short element_length  = 66;
    short element_length_double =  132;

    char sf[16];

    short l_line_b;
    short r_line_b;


    bool flag_get_point=false;


private slots:

    void ImageOut();

private:

//    bool c_l_line(short x,short y);
//    bool c_r_line(short x,short y);
//    bool c_u_line(short x,short y);



public:
    void get_Camera_params();
    void set_Camera_params();
//    void get_Camera_HSV(cv::Mat Img);
    void Camera_params_Adaptive();

    short Camera_ImgH;
    short Camera_ImgS;
    short Camera_ImgV;

    short Camera_EXPOSURE_param;  //曝光
    short Camera_SATURATION_param;   //饱和度
    short Camera_CONTRAST_param;     // 对比度
    short Camera_BRIGHTNESS_param;   //亮度
    short Camera_HUE_param;          //色调

};

#endif // COLORHANDLE_H
