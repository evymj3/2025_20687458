#include <QMessageBox> // Added from PDF
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Example of connecting signals and slots in mainwindow.cpp
    // =====================================================================
    // Add the following line at the end of the MainWindow constructor

    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    // =====================================================================
}



MainWindow::~MainWindow()
{
    delete ui;

}

//replaced with new
// Update your button handling slot so it activates status bar
// =====================================================================
void MainWindow::handleButton() {
    // This causes MainWindow to emit the signal that will then be
    // received by the status bar’s slot
    emit statusUpdateMessage(QString("Add button was clicked"), 0);
}
// =====================================================================
