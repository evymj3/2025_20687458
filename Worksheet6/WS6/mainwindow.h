#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Example of slot definition in mainwindow.h
    // =====================================================================
    // Add this to the MainWindow class definition



public slots:
    void handleButton();
    // =====================================================================
    // Example of signal definition in mainwindow.h
    // =====================================================================
    // This needs adding to the MainWindow class definition
signals:
    void statusUpdateMessage(const QString &message, int timeout);
    // =====================================================================

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
