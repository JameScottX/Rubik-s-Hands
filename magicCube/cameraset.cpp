#include "cameraset.h"
#include "ui_cameraset.h"

CameraSet::CameraSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraSet)
{

    ui->setupUi(this);

    connect(ui->hS_hue,SIGNAL(valueChanged(int)),ui->sB_hue,SLOT(setValue(int)));
    connect(ui->hS_saturation,SIGNAL(valueChanged(int)),ui->sB_saturation,SLOT(setValue(int)));
    connect(ui->hS_exposure,SIGNAL(valueChanged(int)),ui->sB_exposure,SLOT(setValue(int)));
    connect(ui->hS_contrast,SIGNAL(valueChanged(int)),ui->sB_contrast,SLOT(setValue(int)));
    connect(ui->hS_brightness,SIGNAL(valueChanged(int)),ui->sB_brightness,SLOT(setValue(int)));

    connect(ui->sB_hue,SIGNAL(valueChanged(int)),ui->hS_hue,SLOT(setValue(int)));
    connect(ui->sB_saturation,SIGNAL(valueChanged(int)),ui->hS_saturation,SLOT(setValue(int)));
    connect(ui->sB_exposure,SIGNAL(valueChanged(int)),ui->hS_exposure,SLOT(setValue(int)));
    connect(ui->sB_contrast,SIGNAL(valueChanged(int)),ui->hS_contrast,SLOT(setValue(int)));
    connect(ui->sB_brightness,SIGNAL(valueChanged(int)),ui->hS_brightness,SLOT(setValue(int)));

    connect(ui->hS_hue,SIGNAL(valueChanged(int)),this,SLOT(Forparams_change()));
    connect(ui->hS_saturation,SIGNAL(valueChanged(int)),this,SLOT(Forparams_change()));
    connect(ui->hS_exposure,SIGNAL(valueChanged(int)),this,SLOT(Forparams_change()));
    connect(ui->hS_contrast,SIGNAL(valueChanged(int)),this,SLOT(Forparams_change()));
    connect(ui->hS_brightness,SIGNAL(valueChanged(int)),this,SLOT(Forparams_change()));

}

CameraSet::~CameraSet()
{
    delete ui;
}

void CameraSet::Forparams_change(){


    get_Camera_EXPOSURE_param= ui->hS_exposure->value();
    get_Camera_BRIGHTNESS_param  = ui->hS_brightness->value();
    get_Camera_CONTRAST_param = ui->hS_contrast->value();
    get_Camera_SATURATION_param = ui->hS_saturation->value();
    get_Camera_HUE_param = ui->hS_hue->value();


    emit params_change();

}

void CameraSet::Slider_SpinInit(short EXPOSURE,short SATURATION,short CONTRAST,short BRIGHTNESS,short HUE){

    ui->hS_exposure->setMinimum(EXPOSURE-20);
    ui->hS_exposure->setMaximum(EXPOSURE+20);

    ui->hS_brightness->setMinimum(BRIGHTNESS-100);
    ui->hS_brightness->setMaximum(BRIGHTNESS+100);

    ui->hS_contrast->setMinimum(CONTRAST-100);
    ui->hS_contrast->setMaximum(CONTRAST+100);

    ui->hS_hue->setMinimum(HUE-100);
    ui->hS_hue->setMaximum(HUE+100);

    ui->hS_saturation->setMinimum(SATURATION-160);
    ui->hS_saturation->setMaximum(SATURATION+160);

    ui->hS_exposure->setValue(EXPOSURE);
    ui->hS_brightness->setValue(BRIGHTNESS);
    ui->hS_contrast->setValue(CONTRAST);
    ui->hS_hue->setValue(HUE);
    ui->hS_saturation->setValue(SATURATION);

}


