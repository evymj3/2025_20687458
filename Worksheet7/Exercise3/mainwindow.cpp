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

    // Layout fix to ensure the 3D window isn't squashed
    ui->horizontalLayout->setStretch(0, 1);
    ui->horizontalLayout->setStretch(1, 4);

    // 1. Existing connections
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    // 2. Create and link the ModelPartList
    this->partList = new ModelPartList("PartsList");
    ui->treeView->setModel(this->partList);

    // 3. Populate the tree
    ModelPart *rootItem = this->partList->getRootItem();
    for (int i = 0; i < 3; i++) {
        ModelPart *childItem = new ModelPart({ QString("TopLevel %1").arg(i), "true" });
        rootItem->appendChild(childItem);
        for (int j = 0; j < 5; j++) {
            childItem->appendChild(new ModelPart({ QString("Item %1,%2").arg(i).arg(j), "true" }));
        }
    }

    // =========================================================
    // VTK INITIALIZATION
    // =========================================================
    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    ui->vtkWidget->setRenderWindow(renderWindow);

    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);
    renderer->SetBackground(0.15, 0.15, 0.2); // Dark blue-grey

    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(20);

    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(1.0, 0.2, 0.4); // Pinkish-Red
    cylinderActor->RotateX(30.0);

    renderer->AddActor(cylinderActor);

    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);

    renderWindow->Render();
}

// --- THESE ARE THE MISSING FUNCTIONS THAT CAUSED YOUR LINKER ERRORS ---

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
    // Placeholder
}
