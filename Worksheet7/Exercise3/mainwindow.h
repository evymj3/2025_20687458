#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vtkSmartPointer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include "ModelPartList.h"

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

public slots:
    void handleButton();
    void handleTreeClicked();

signals:
    void statusUpdateMessage(const QString &message, int timeout);

private slots:
    void on_actionOpen_File_triggered();

private:
    Ui::MainWindow *ui;
    ModelPartList* partList;

    // VTK specific pointers for Exercise 3
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
};

#endif // MAINWINDOW_H
