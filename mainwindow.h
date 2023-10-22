#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller/mwcontroller.h"

#include "view/settings_widget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
using namespace s21;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MWController* mw_cont_; ///< Создание экземпляра контроллера
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SettingsWidget* sw_ = nullptr;
    void SaveJPEG();
    void SaveBMP();

public slots:
    void LoadButtonClicked();
    void SlotSettngsBtnClicked();
    void SlotRecordButtonClicked();
    void SlotTransformButtonClicked();
};
#endif // MAINWINDOW_H
