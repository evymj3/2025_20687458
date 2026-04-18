#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

// VTK Includes
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Existing connections for buttons and status bar
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    // 2. Create and link the ModelPartList (Worksheet 6 logic)
    this->partList = new ModelPartList("PartsList");
    ui->treeView->setModel(this->partList);

    // 3. Populate the tree with items
    ModelPart *rootItem = this->partList->getRootItem();

    for (int i = 0; i < 3; i++) {
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");
        ModelPart *childItem = new ModelPart({ name, visible });
        rootItem->appendChild(childItem);

        for (int j = 0; j < 5; j++) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            QString subVisible("true");
            ModelPart *childChildItem = new ModelPart({ subName, subVisible });
            childItem->appendChild(childChildItem);
        }
    }
    // <--- The Tree Loops end here.

    // =========================================================
    // VTK INITIALIZATION (Exercise 3)
    // =========================================================

    /* Link a render window with the Qt widget */
    // IMPORTANT: Check that your widget in Qt Creator is named 'vtkWidget'
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    /* Add a renderer */
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    /* Create the Cylinder object */
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);

    /* Create the mapper */
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    /* Create the actor */
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0, 0.0, 0.35); // Pinkish-Red
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);

    /* Add the actor to the renderer */
    renderer->AddActor(cylinderActor);

    /* Setup Camera */
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    /* MANDATORY: Tell the window to actually draw the cylinder */
    renderWindow->Render();

} // <--- End of Constructor

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    emit statusUpdateMessage(QString("Add button was clicked"), 0);
}

void MainWindow::handleTreeClicked() {
    QModelIndex index = ui->treeView->currentIndex();

    if (index.isValid()) {
        ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());
        QString text = selectedPart->data(0).toString();
        emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    // Placeholder for Exercise 4
}
