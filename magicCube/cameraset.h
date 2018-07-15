#ifndef CAMERASET_H
#define CAMERASET_H

#include <QWidget>

namespace Ui {
class CameraSet;

}

class CameraSet : public QWidget
{
    Q_OBJECT

public:
    explicit CameraSet(QWidget *parent = 0);
    ~CameraSet();

    short get_Camera_EXPOSURE_param;
    short get_Camera_SATURATION_param;
    short get_Camera_CONTRAST_param;
    short get_Camera_BRIGHTNESS_param;
    short get_Camera_HUE_param;

    void Slider_SpinInit(short EXPOSURE,short SATURATION,short CONTRAST,short BRIGHTNESS,short HUE);
signals:

    void params_change();

private slots:

    void Forparams_change();

private:

    Ui::CameraSet *ui;


};

#endif // CAMERASET_H
