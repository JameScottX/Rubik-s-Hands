#include "colorhandle.h"
#include <QMessageBox>
#include <QDebug>

#define IMAGE_TOUSHI_LCOSE    31
#define IMAGE_TOUSHI_FAR      25



colorhandle::colorhandle(QObject *parent)
    :QObject(parent)
{

    cvInitFont(&fontcompare, CV_FONT_HERSHEY_DUPLEX, 0.25, 0.25, 0, 1);

    point_Config3();
}


void colorhandle::cameraInit(){

         rfsh->stop();
         capture_f.set(CV_CAP_PROP_FRAME_WIDTH,IMAGEWID);
         capture_f.set(CV_CAP_PROP_FRAME_HEIGHT,IMAGEHEIGHT);
         capture_b.set(CV_CAP_PROP_FRAME_WIDTH,IMAGEWID);
         capture_b.set(CV_CAP_PROP_FRAME_HEIGHT,IMAGEHEIGHT);

         if(!capture_f.isOpened()){

             return;/****************/
         }
         if(!capture_b.isOpened()){

             return;/****************/
         }
         connect(rfsh,SIGNAL(timeout()),this,SLOT(ImageOut()));

         rfsh->start(80);
}

    //以下为魔方视觉第二套方案
void colorhandle::point_Config(short x_ ,short y_ ,double size_ ){

    static double temp_size =1;
    temp_size+=size_;

    double temp_width = IMAGEAREA_RL_WIDTH*temp_size;
    double temp_height = IMAGEAREA_HEIGHT*temp_size;
    static short Xpos =60,Ypos = 120;

    _L_U[0].x =Xpos+ x_;    //这里下x,y需要交换
    _L_U[0].y =Ypos+ y_+IMAGE_TOUSHI_LCOSE;
    _L_D[0].x = _L_U[0].x;
    _L_D[0].y = temp_height + _L_U[0].y-IMAGE_TOUSHI_LCOSE;

    _C_U[0].x = temp_width + _L_U[0].x ;
    _C_U[0].y = _L_U[0].y-IMAGE_TOUSHI_LCOSE;
    _C_D[0].x = _C_U[0].x;
    _C_D[0].y = _L_D[0].y+IMAGE_TOUSHI_LCOSE;

    _R_U[0].x = 2 * temp_width + _L_U[0].x;
    _R_U[0].y = _L_U[0].y;
    _R_D[0].x = _R_U[0].x;
    _R_D[0].y = _L_D[0].y;

    Xpos += x_;
    Ypos += y_;
    U_L_area_corner.clear();


    U_L_area_corner.push_back(_L_U[0]);
    U_L_area_corner.push_back(_C_U[0]);
    U_L_area_corner.push_back(_C_D[0]);
    U_L_area_corner.push_back(_L_D[0]);


    U_R_area_corner.clear();

    U_R_area_corner.push_back(_C_D[0]);
    U_R_area_corner.push_back(_C_U[0]);
    U_R_area_corner.push_back(_R_U[0]);
    U_R_area_corner.push_back(_R_D[0]);

    qDebug()<<" F " + QString::number(_L_U[0].x)+" "+QString::number(_L_U[0].y);
     qDebug()<<" F size" + QString::number(temp_size);
}

void colorhandle::point_Config2(short x_ ,short y_ ,double size_ ){

    //以下为魔方视觉第二套方案

    static double temp_size =1;
    temp_size+=size_;

    double temp_width = IMAGEAREA_RL_WIDTH*temp_size;
    double temp_height = IMAGEAREA_HEIGHT*temp_size;
    static short Xpos2 =60;
    static short Ypos2 = 120;

    _L_U[1].x =Xpos2+ x_;    //这里下x,y需要交换
    _L_U[1].y =Ypos2+ y_+IMAGE_TOUSHI_FAR;
    _L_D[1].x = _L_U[1].x;
    _L_D[1].y = temp_height + _L_U[1].y-IMAGE_TOUSHI_FAR;

    _C_U[1].x = temp_width + _L_U[1].x ;
    _C_U[1].y = _L_U[1].y-IMAGE_TOUSHI_FAR;
    _C_D[1].x = _C_U[1].x;
    _C_D[1].y = _L_D[1].y+IMAGE_TOUSHI_FAR;

    _R_U[1].x = 2 * temp_width + _L_U[1].x;
    _R_U[1].y = _L_U[1].y;
    _R_D[1].x = _R_U[1].x;
    _R_D[1].y = _L_D[1].y;

    Xpos2 += x_;
    Ypos2 += y_;

    D_L_area_corner.clear();

    D_L_area_corner.push_back(_L_U[1]);
    D_L_area_corner.push_back(_L_D[1]);
    D_L_area_corner.push_back(_C_D[1]);
    D_L_area_corner.push_back(_C_U[1]);

    D_R_area_corner.clear();

    D_R_area_corner.push_back(_R_U[1]);
    D_R_area_corner.push_back(_C_U[1]);
    D_R_area_corner.push_back(_C_D[1]);
    D_R_area_corner.push_back(_R_D[1]);

    qDebug()<<" B " + QString::number(_L_U[1].x)+" "+QString::number(_L_U[1].y);
    qDebug()<<" B size" + QString::number(temp_size);
}

void colorhandle::point_Config3(){//初始调节位置

    short Xpos = 27;
    short Ypos = 50-IMAGE_TOUSHI_LCOSE;

    double temp_width = IMAGEAREA_RL_WIDTH*1.4;
    double temp_height = IMAGEAREA_HEIGHT*1.4;

    short Xpos2 =82;
    short Ypos2 = 101 -IMAGE_TOUSHI_FAR;
    double temp_width2 = IMAGEAREA_RL_WIDTH*1.05;
    double temp_height2 = IMAGEAREA_HEIGHT*1.05;


    _L_U[0].x =Xpos;    //这里下x,y需要交换
    _L_U[0].y =Ypos+IMAGE_TOUSHI_LCOSE;
    _L_D[0].x = _L_U[0].x;
    _L_D[0].y = temp_height + _L_U[0].y-IMAGE_TOUSHI_LCOSE;

    _C_U[0].x = temp_width + _L_U[0].x ;
    _C_U[0].y = _L_U[0].y-IMAGE_TOUSHI_LCOSE;
    _C_D[0].x = _C_U[0].x;
    _C_D[0].y = _L_D[0].y+IMAGE_TOUSHI_LCOSE;

    _R_U[0].x = 2 * temp_width + _L_U[0].x;
    _R_U[0].y = _L_U[0].y;
    _R_D[0].x = _R_U[0].x;
    _R_D[0].y = _L_D[0].y;


    _L_U[1].x =Xpos2;    //这里下x,y需要交换
    _L_U[1].y =Ypos2+IMAGE_TOUSHI_FAR;
    _L_D[1].x = _L_U[1].x;
    _L_D[1].y = temp_height2 + _L_U[1].y-IMAGE_TOUSHI_FAR;

    _C_U[1].x = temp_width2 + _L_U[1].x ;
    _C_U[1].y = _L_U[1].y-IMAGE_TOUSHI_FAR;
    _C_D[1].x = _C_U[1].x;
    _C_D[1].y = _L_D[1].y+IMAGE_TOUSHI_FAR;

    _R_U[1].x = 2 * temp_width2 + _L_U[1].x;
    _R_U[1].y = _L_U[1].y;
    _R_D[1].x = _R_U[1].x;
    _R_D[1].y = _L_D[1].y;

    U_L_area_corner.clear();


    U_L_area_corner.push_back(_L_U[0]);
    U_L_area_corner.push_back(_C_U[0]);
    U_L_area_corner.push_back(_C_D[0]);
    U_L_area_corner.push_back(_L_D[0]);


    U_R_area_corner.clear();

    U_R_area_corner.push_back(_C_D[0]);
    U_R_area_corner.push_back(_C_U[0]);
    U_R_area_corner.push_back(_R_U[0]);
    U_R_area_corner.push_back(_R_D[0]);

    D_L_area_corner.clear();

    D_L_area_corner.push_back(_L_U[1]);
    D_L_area_corner.push_back(_L_D[1]);
    D_L_area_corner.push_back(_C_D[1]);
    D_L_area_corner.push_back(_C_U[1]);

    D_R_area_corner.clear();

    D_R_area_corner.push_back(_R_U[1]);
    D_R_area_corner.push_back(_C_U[1]);
    D_R_area_corner.push_back(_C_D[1]);
    D_R_area_corner.push_back(_R_D[1]);
}
char temp_judge(float a, float b, float c){

    if(a>=b && a>=c){
        if(b>=c){
        return 0x02;
        }else{
        return 0x01;
        }

    }else if(b>=a && b>=c){
        if(a>=c){
        return 0x12;
        }else{
        return 0x10;
        }
    }else if(c>=a && c>=b){
        if(a>=b){
         return 0x21;
        }else{
         return 0x20;
        }
    }
}


cv::Mat image_first_handle(cv::Mat image_in){//未使用

    float max_,min_;
    char tmp8_;
    cv::Mat image32_tmp(image_in.size(),CV_8UC3);
    cv::Mat image8_out(image_in.size(),CV_8UC3);

    image_in.convertTo(image32_tmp,CV_8UC3);

    for(int r=0;r<image32_tmp.rows;r++){

        cv::Vec3b *pixVal = image32_tmp.ptr<cv::Vec3b>(r);
       // cv::Vec3b *pix_Out = image8_out<cv::Vec3b>(r);

        for(int c=0;c<image32_tmp.cols;c++){

            pixVal[c][2] = pixVal[c][2];
            pixVal[c][1] = pixVal[c][1];
            pixVal[c][0] = pixVal[c][0];

            tmp8_ = temp_judge(pixVal[c][0],pixVal[c][1],pixVal[c][2]);

            pixVal[c][tmp8_ >> 4] = pixVal[c][tmp8_>>4]*1.15;
            pixVal[c][tmp8_ & 0x0F] = pixVal[c][tmp8_>>4]*0.85;

        }
    }

    image8_out = image32_tmp;
    return image8_out;

}

cv::Mat image_first_handle2(cv::Mat Img){//未使用

       cv::Mat image8_out(Img.size(),CV_8UC3);
       cv::Mat Img_out(Img.size(), CV_32FC3);
       Img.convertTo(Img_out, CV_32FC3);
       cv::Mat Img_in(Img.size(), CV_32FC3);
       Img.convertTo(Img_in, CV_32FC3);
       // define the iterator of the input image
       cv::MatIterator_<cv::Vec3f> inp_begin, inp_end;
       inp_begin=Img_in.begin<cv::Vec3f>();
       inp_end =Img_in.end<cv::Vec3f>();

       // define the iterator of the output image
       cv::MatIterator_<cv::Vec3f> out_begin, out_end;
       out_begin=Img_out.begin<cv::Vec3f>();
       out_end =Img_out.end<cv::Vec3f>();

       // increment (-100.0, 100.0)
       float Increment=90.0/100.0;

       float delta=0;
       float minVal, maxVal;
       float t1, t2, t3;
       float L,S;
       float alpha;

       for(; inp_begin!=inp_end; inp_begin++, out_begin++)
       {

           (*inp_begin)[0] = (*inp_begin)[0]*2.6;
           (*inp_begin)[1] = (*inp_begin)[1]*2.6;
           (*inp_begin)[2] = (*inp_begin)[2]*2.6;

           t1=(*inp_begin)[0];
           t2=(*inp_begin)[1];
           t3=(*inp_begin)[2];

           minVal=std::min(std::min(t1,t2),t3);
           maxVal=std::max(std::max(t1,t2),t3);
           delta=(maxVal-minVal)/255.0;
           L=0.5*(maxVal+minVal)/255.0;
           S=std::max(0.5*delta/L, 0.5*delta/(1-L));

           if (Increment>0)
           {
               alpha=std::max(S, 1-Increment);
               alpha=1.0/alpha-1;
               (*out_begin)[0]=(*inp_begin)[0]+((*inp_begin)[0]-L*255.0)*alpha;
               (*out_begin)[1]=(*inp_begin)[1]+((*inp_begin)[1]-L*255.0)*alpha;
               (*out_begin)[2]=(*inp_begin)[2]+((*inp_begin)[2]-L*255.0)*alpha;
           }
           else
           {
               alpha=Increment;
               (*out_begin)[0]=L*255.0+((*inp_begin)[0]-L*255.0)*(1+alpha);
               (*out_begin)[1]=L*255.0+((*inp_begin)[1]-L*255.0)*(1+alpha);
               (*out_begin)[2]=L*255.0+((*inp_begin)[2]-L*255.0)*(1+alpha);

           }
       }
       Img_out=Img_out/*/255.0*/;
       Img_out.convertTo(image8_out,CV_8UC3);
       return image8_out;

}



cv::Mat colorhandle::getFrame_f(){

    cv::Mat imageout;

    if(!camera_f_stop){

        capture_f>>frame_f;

        imageout = frame_f;
        return imageout;
    }
}

cv::Mat colorhandle::getFrame_b(){

    cv::Mat imageout;

   if(!camera_b_stop){

        capture_b>>frame_b;
        cv::flip(frame_b,frame_b,1);  //这里需要进行翻转

       imageout = frame_b;
        return imageout;
    }

}

void colorhandle::ImageOut(){

        imageModel_F = getFrame_f();
        imageModel_B = getFrame_b();

}

cv::Mat colorhandle::splitColor(cv::Mat tempIge){

    char vr,vg,vb;
    cv::Mat temp,imageout;

    temp= cv::Mat(frame_f.size(),frame_f.type(),cv::Scalar::all(0));

    for(int r=0;r<tempIge.rows;r++){

        cv::Vec3b *pixVal = tempIge.ptr<cv::Vec3b>(r);

        for(int c=0;c<tempIge.cols;c++){

            vr = pixVal[c][2];
            vb = pixVal[c][1];
            vg = pixVal[c][0];

            if(abs(vr-vb)>pix_val_gal || abs(vg-vb)>pix_val_gal || abs(vr-vg)>pix_val_gal){

                temp.at<cv::Vec3b>(r,c)[2] =vr;
                temp.at<cv::Vec3b>(r,c)[1] =vb;
                temp.at<cv::Vec3b>(r,c)[0] =vg;
            }
        }
    }

    return temp;

}

cv::Vec3b colorhandle:: getPartAeraPix(cv::Mat tempIge,cv::Point target){        //获取方块颜色


    cv::Vec3b area_pix;
    double vr =0,vb =0,vg =0;

    for(int i=0;i<3;i++){

        for(int j=0;j<3;j++){

          vg+= tempIge.at<cv::Vec3b>(target.y+j,target.x+i)[0];
          vb+= tempIge.at<cv::Vec3b>(target.y+j,target.x+i)[1];
          vr+= tempIge.at<cv::Vec3b>(target.y+j,target.x+i)[2];
        }
    }

   area_pix[0]=(char)(vg/9);
   area_pix[1]=(char)(vb/9);
   area_pix[2]=(char)(vr/9);

   return area_pix;

}

cv::Vec3b colorhandle::getPartAeraHSV(const cv::Mat tempIge,cv::Point target){        //获取方块颜色

    cv::Mat tempHSV;

    cv::Vec3b area_pix;
    double vr =0,vb =0,vg =0;

    cv::cvtColor(tempIge,tempHSV,CV_BGR2HSV);

    for(int i=0;i<2;i++){

        for(int j=0;j<2;j++){

          vg+= tempHSV.at<cv::Vec3b>(target.y+j,target.x+i)[0];
          vb+= tempHSV.at<cv::Vec3b>(target.y+j,target.x+i)[1];
          vr+= tempHSV.at<cv::Vec3b>(target.y+j,target.x+i)[2];
        }
    }

   area_pix[0]=(char)(vg/4);
   area_pix[1]=(char)(vb/4);
   area_pix[2]=(char)(vr/4);

   return area_pix;

}



char colorhandle::judeg_matrix(cv::Point pit){       //这里规定wrap图片大小为 200*200

    if(pit.y < element_length){

        if(pit.x < element_length){
            return 0;
        }else if (element_length <pit.x && pit.x <element_length_double){

            return 1;
        }else if(pit.x> element_length_double){
            return 2;
        }

     }else if (element_length < pit.y && pit.y< element_length_double){

        if(pit.x < element_length){
            return 3;
        }else if (element_length <pit.x && pit.x<element_length_double){
            return 4;
        }else if(pit.x>element_length_double){
            return 5;
        }
    }else if (pit.y>element_length_double){

        if(pit.x < element_length){
            return 6;
        }else if (element_length <pit.x && pit.x<element_length_double){
            return 7;
        }else if(pit.x>element_length_double){
            return 8;
        }
    }
    return 9;
}
//*******************************
short max_(short a,short b,short c){

    short max;

    if(a>=b){
        if(a>=c){
        max = a;
        }else{
           max = c;
        }
    }else{
        if(b>=c){
           max = b;
        }else{
           max = c;
        }
    }
    return max;

}
short min_(short a,short b,short c){
    short min;

    if(a>=b){
        if(b>=c){
        min = c;
        }else{
           min = b;
        }
    }else{
        if(a>=c){
           min = c;
        }else{
           min = a;
        }
    }
    return min;

}
char colorhandle::judge_pix(cv::Vec3b pix_get){   //这里需要实验

    short R_ = pix_get(2)+1;
    short G_ = pix_get(1)+1;
    short B_ = pix_get(0)+1;


    float r_g = (float)R_/(float)G_;
    float r_b = (float)R_/(float)B_;
    float b_r = (float)B_/(float)R_;
    float b_g = (float)B_/(float)G_;
    float g_r = (float)G_/(float)R_;
    float g_b = (float)G_/(float)B_;

    short tmax ,tmin;
    tmax = max_(R_,G_,B_);
    tmin = min_(R_,G_,B_);

    if(g_r >5.00 && G_ == tmax){qDebug()<<"GREEN";return  GREEN;}      //g/r
    if(b_r > 5.003 && g_b<1.20){qDebug()<<"BLUE";return BLUE;}      //b/r && b/g
    if(r_g>3.62 && r_b>5.001){qDebug()<<"RED";return RED;}

    if((float)tmax/tmin<2 ){qDebug()<<"WHITE";return WHITE;}

    if(r_g>1.001 ){qDebug()<<"CHE";return CHE;}   //这里依据摄像头的问题
    if(r_g <1.002  ){qDebug()<<"YELLOW";return YELLOW;}


    qDebug()<<"NOTHING";
    return NOTHING;

}

std::pair<cv::Mat,char*> colorhandle::getPart(const cv::Mat tempIge){

    memset(part_info,NOTHING,9);

    cv::Mat gray_tmp;
    cv::Mat threshold_output;
    //cv::Mat img_out = cv::Mat::zero(threshold_output.size(),CV_8UC3);

    cv::cvtColor(tempIge,gray_tmp,CV_BGR2GRAY);
    cv::threshold(gray_tmp,threshold_output,threshold_gap,255,cv::THRESH_BINARY);//***********

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(threshold_output,contours,hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
    std::vector<cv::RotatedRect> minEllipse(contours.size());

    if(minEllipse.size()>=4){                       // 这里的判断需要改进

        for(int i=0;i<contours.size();i++){

          if(cv::contourArea(contours[i])>area_gap){

           minEllipse[i] =cv::fitEllipse(cv::Mat(contours[i]));

           cv::Point center_;
           center_.x =minEllipse[i].center.x;                                    //这里需要转换
           center_.y =minEllipse[i].center.y;

           char tmp_get =judeg_matrix(center_);

           if(tmp_get>8)continue;

           cv::Vec3b get_point_pix =  getPartAeraPix(tempIge,center_);           //注意这里用原来的坐标


           part_info[tmp_get] = judge_pix(get_point_pix);

           sprintf_s(sf,"(%d,%d,%d)",getPartAeraPix(tempIge,center_)[2],getPartAeraPix(tempIge,center_)[1],getPartAeraPix(tempIge,center_)[0]);
           cv::ellipse(tempIge, minEllipse[i], cv::Scalar(0,255,0), 2, 8);
           cvPutText(&(CvMat)tempIge, sf,cv::Point(center_.x,center_.y), &fontcompare, CV_RGB(255, 0, 0));
           }
        }
    }

    return {tempIge,part_info};
}



char colorhandle::judge_pix2(cv::Vec3b pix_get){

    if(pix_get[0]<6)return RED;
    if(pix_get[0]<30)return CHE;
    if(pix_get[0]>=30 && pix_get[0]<60)return YELLOW;
    if(pix_get[1]<130)return WHITE;
    if(pix_get[0]>=60 && pix_get[0]<80)return GREEN;
    if(pix_get[0]>80) return BLUE;
    return NOTHING;

}

cv::Mat colorhandle::getPart2(const cv::Mat tempIge){

    cv::Point point;
    char tmp_get;
    cv::Mat temp;

    for(short x=0;x<3;x++){
        point.x = length_part3+x*length_part2;
        for(short y=0;y<3;y++){
            point.y= length_part3+y*length_part2;

             tmp_get = judeg_matrix(point);
            cv::Vec3b get_point_pix = getPartAeraHSV(tempIge,point);
            part_info[tmp_get] = judge_pix2(get_point_pix);
        }
    }

    return tempIge;

}


void colorhandle::mWrapHandle(cv::Mat imgGet,std::vector<cv::Point2f> vecPoint, cv::Mat partImgeOut){      //这里矫正图片区域

    std::vector<cv::Point2f>quad_pts;

    quad_pts.push_back(cv::Point2f(0,0));
    quad_pts.push_back(cv::Point2f(partImgeOut.cols,0));
    quad_pts.push_back(cv::Point2f(partImgeOut.cols,partImgeOut.rows));
    quad_pts.push_back(cv::Point2f(0,partImgeOut.rows));

    cv::Mat transmtx =cv::getPerspectiveTransform(vecPoint,quad_pts);;
    cv::warpPerspective(imgGet,partImgeOut,transmtx,partImgeOut.size());

}


cv::Mat colorhandle ::mwrap_area_handle_last(cv::Mat imgGet){          //这里将白色增添上去

    cv::Mat tmp = getPart2(imgGet);
    return tmp;
}


void colorhandle::get_Camera_params(){

//    Camera_EXPOSURE_param = capture_f.get(CV_CAP_PROP_EXPOSURE );
//    Camera_SATURATION_param = capture_f.get(CV_CAP_PROP_SATURATION );
//    Camera_CONTRAST_param = capture_f.get(CV_CAP_PROP_CONTRAST );
//    Camera_BRIGHTNESS_param = capture_f.get(CV_CAP_PROP_BRIGHTNESS);
//    Camera_HUE_param = capture_f.get(CV_CAP_PROP_HUE);

    Camera_EXPOSURE_param = EXPOSURE_;
    Camera_SATURATION_param = SATURATION_;
    Camera_CONTRAST_param = CONTRAST_;
    Camera_BRIGHTNESS_param =BRIGHTNESS_;
    Camera_HUE_param =HUE_param_;
    set_Camera_params();

    qDebug()<<Camera_EXPOSURE_param;
    qDebug()<<Camera_SATURATION_param;
    qDebug()<<Camera_CONTRAST_param;
    qDebug()<<Camera_BRIGHTNESS_param;
    qDebug()<<Camera_HUE_param;

}

void colorhandle::set_Camera_params(){

    capture_f.set(CV_CAP_PROP_EXPOSURE,Camera_EXPOSURE_param);
    capture_f.set(CV_CAP_PROP_SATURATION,Camera_SATURATION_param);
    capture_f.set(CV_CAP_PROP_CONTRAST ,Camera_CONTRAST_param);
    capture_f.set(CV_CAP_PROP_BRIGHTNESS,Camera_BRIGHTNESS_param);
    capture_f.set(CV_CAP_PROP_HUE,Camera_HUE_param);

    capture_b.set(CV_CAP_PROP_EXPOSURE,Camera_EXPOSURE_param);
    capture_b.set(CV_CAP_PROP_SATURATION,Camera_SATURATION_param+20);
    capture_b.set(CV_CAP_PROP_CONTRAST ,Camera_CONTRAST_param);
    capture_b.set(CV_CAP_PROP_BRIGHTNESS,Camera_BRIGHTNESS_param-5);
    capture_b.set(CV_CAP_PROP_HUE,Camera_HUE_param);



}


void colorhandle::Camera_params_Adaptive(){

     // get_Camera_HSV(imageModel_B);

     if( PARAMS_S - Camera_ImgS < -2){

         Camera_SATURATION_param-=2;

     }else if ( PARAMS_S - Camera_ImgS > 2){

         Camera_SATURATION_param+=2;

     }

     if(PARAMS_V - Camera_ImgV <-2){

         Camera_BRIGHTNESS_param-=2;

     }else if(PARAMS_V - Camera_ImgV >2){

         Camera_BRIGHTNESS_param+=2;

         }

     set_Camera_params();
}



QImage colorhandle::mat2QImage(cv::Mat& mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1

    if(mat.type() == CV_8UC1)

    {

#if 0

        qDebug() << "CV_8UC1";

#endif

        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);

        // Set the color table (used to translate colour indexes to qRgb values)

        image.setColorCount(256);

        for(int i = 0; i < 256; i++)

        {

            image.setColor(i, qRgb(i, i, i));

        }

        // Copy input Mat

        uchar *pSrc = mat.data;

        for(int row = 0; row < mat.rows; row ++)

        {

            uchar *pDest = image.scanLine(row);

            memcpy(pDest, pSrc, mat.cols);

            pSrc += mat.step;

        }

        return image;

    }

    // 8-bits unsigned, NO. OF CHANNELS = 3

    else if(mat.type() == CV_8UC3)

    {

        // Copy input Mat

        const uchar *pSrc = (const uchar*)mat.data;

        // Create QImage with same dimensions as input Mat

        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);

        return image.rgbSwapped();

    }

    else if(mat.type() == CV_8UC4)

    {

#if 0

        qDebug() << "CV_8UC4";

#endif

        // Copy input Mat

        const uchar *pSrc = (const uchar*)mat.data;

        // Create QImage with same dimensions as input Mat

        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);

        return image.copy();

    }

    else

    {

#if 0

        qDebug() << "ERROR: Mat could not be converted to QImage.";

#endif

        QMessageBox::information(

            NULL,

            "Error",

            "Image Format Unknown!",

            QMessageBox::Yes | QMessageBox::No,

            QMessageBox::Yes);

        return QImage();

    }

}









