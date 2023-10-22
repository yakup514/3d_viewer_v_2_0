#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "view/viewer.h"
#include <QValidator>
#include <QFileDialog>
#include "controller/command.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mw_cont_ = new MWController;
    connect(ui->load_btn, SIGNAL(clicked()), this, SLOT(LoadButtonClicked()));
    connect(ui->set_btn, SIGNAL(clicked()), this, SLOT(SlotSettngsBtnClicked()));
    connect(ui->record_btn, SIGNAL(clicked()), this, SLOT(SlotRecordButtonClicked()));
    connect(ui->transform_btn, SIGNAL(clicked()), this, SLOT(SlotTransformButtonClicked()));
    QDoubleValidator* doub_vall = new QDoubleValidator(-360.0, 360.0, 2, this);
    doub_vall->setLocale(QLocale::C);
    ui->rot_x_le->setValidator(doub_vall);
    ui->rot_y_le->setValidator(doub_vall);
    ui->rot_z_le->setValidator(doub_vall);
    ui->move_x_le->setValidator(doub_vall);
    ui->move_y_le->setValidator(doub_vall);
    ui->move_z_le->setValidator(doub_vall);
    QDoubleValidator* sc_vall = new QDoubleValidator(0.01, 10.0, 2, this);
    sc_vall->setLocale(QLocale::C);
    ui->scale_le->setValidator(sc_vall);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SaveJPEG() {
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                 "~/untitled.jpg",
                                                 tr("Images (*.jpg)"));
    QImage img = ui->viewer->grabFramebuffer();
    img.save(path);

}

void MainWindow::SaveBMP() {
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                 "~/untitled.bmp",
                                                 tr("Images (*.bmp)"));
    QImage img = ui->viewer->grabFramebuffer();
    img.save(path);

}

void MainWindow::LoadButtonClicked(){
   QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                               "~/", tr("Models (*.obj)"));

    if (!path.isEmpty()) {
    ParseCommand pc(mw_cont_->model_, path.toStdString());
    pc.Execute();

    ui->viewer->InitModel(mw_cont_->GetVertexCount(), mw_cont_->GetVertexes(), mw_cont_->GetFasets());

    ui->viewer->update();
    }

}

void MainWindow::SlotSettngsBtnClicked() {
    if (sw_)
        delete sw_;
  sw_ = new SettingsWidget(this);  //
  sw_->setModal(true);

  if (sw_->exec() == QDialog::Accepted) {
    ui->viewer->LoadSettings();
    ui->viewer->update();
  }
}

void MainWindow::SlotRecordButtonClicked() {
    if (ui->comboBox->currentIndex() == 0)
        SaveJPEG();
    else if (ui->comboBox->currentIndex() == 1)
        SaveBMP();
}

void MainWindow::SlotTransformButtonClicked() {
    if (mw_cont_->model_) {
    if (!ui->move_x_le->text().isEmpty()) {
        double move = ui->move_x_le->text().toDouble();
        MoveCommand mc(mw_cont_->model_, 'x', move);
        mc.Execute();
    }
    if (!ui->move_y_le->text().isEmpty()) {
        double move = ui->move_y_le->text().toDouble();
        MoveCommand mc(mw_cont_->model_, 'y', move);
        mc.Execute();
    }
    if (!ui->move_z_le->text().isEmpty()) {
        double move = ui->move_z_le->text().toDouble();
        MoveCommand mc(mw_cont_->model_, 'z', move);
        mc.Execute();
    }
    if (!ui->rot_x_le->text().isEmpty()) {
        double rot = ui->rot_x_le->text().toDouble();
        RotateCommand rc (mw_cont_->model_, 'x', rot);
        rc.Execute();
    }
    if (!ui->rot_y_le->text().isEmpty()) {
        double rot = ui->rot_y_le->text().toDouble();
        RotateCommand rc (mw_cont_->model_, 'y', rot);
        rc.Execute();
    }
    if (!ui->rot_z_le->text().isEmpty()) {
        double rot = ui->rot_z_le->text().toDouble();
        RotateCommand rc (mw_cont_->model_, 'z', rot);
        rc.Execute();
    }
    if (!ui->scale_le->text().isEmpty()) {
        double scale = ui->scale_le->text().toDouble();
        if (scale == 0)
            scale = 1e-7;
        ScaleCommand sc (mw_cont_->model_, scale);
        sc.Execute();
    }
    ui->viewer->InitVertexBuffer(mw_cont_->GetVertexCount(), mw_cont_->GetVertexes());
     ui->viewer->update();
    }
}
