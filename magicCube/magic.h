#ifndef MAGIC_H
#define MAGIC_H

#include <QMainWindow>
#include <QTimer>
#include "colorhandle.h"
#include "core.h"
#include <QMessageBox>
#include "cameraset.h"

namespace Ui {
class Magic;

}

class Magic : public QMainWindow
{
    Q_OBJECT

public:
    explicit Magic(QWidget *parent = 0);
    ~Magic();

private:

    Ui::Magic *ui;
    QThread *imageTh;
    QTimer *refreshIge =new QTimer();

    serial *Mserial;


    QPixmap mp;


    colorhandle *mImage;
    core *magic_core;

    cv::Mat tempimg;
    cv::Mat tempimg2;

     void UI_Config(void);

     QTimer *serial_refresh = new QTimer();

     void area2_Show(char cho);

     QByteArray array;

     void turn2_code();
     char judge_(char get);
     std::string codeSetIn[20];
     char element_central[6];

     bool turn4_otherelement = false;

     void turn4_other();

     QTimer time2_count;

     unsigned short s_ =0;
     unsigned short ms_ =0;

     unsigned char Camera_Params_Adjust = 0;

     bool Key_GFlag = false;
     bool Key_SpaceFlag = false;
     bool Key_RFlag = false;

     void ALLReady();
     void num_show(QString loc,char *get);
private:

     CameraSet myCamera;
     void CameraSetInit();

     bool showParams_Flag = true;

     char cameraFNum = 1;
     char cameraBNum = 2;
     char listCamera[3] = {0,1,2};
private slots:

    void imageRefresh();
    void start_fun();
    void start_func_key();

    void info_clear();

    void serial_dector();
    void serial_connect();

    void Moto_L_S();
    void Moto_L_N();
    void Moto_R_S();
    void Moto_R_N();
    void ready_go();
    void paprection();

    void time_refresh();

    void myCamera_setParams();

    void serial_getBits();

    void actionStatus();
    void showParams();
    void OpenCamera();

    bool eventFilter(QObject *obj,QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

};

#endif // MAGIC_H
