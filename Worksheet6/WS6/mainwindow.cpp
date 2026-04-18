#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Existing connections for button and status bar
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);

    //added below- Link the TreeView click to our new function
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);

    /* 1. Create/allocate the ModelList */
    this->partList = new ModelPartList("PartsList");

    /* 2. Link it to the treeview in the GUI */
    ui->treeView->setModel(this->partList);

    /* 3. Manually create a model tree (Exercise 4) */
    ModelPart *rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Create strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart *childItem = new ModelPart({ name, visible });

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString subName = QString("Item %1,%2").arg(i).arg(j);
            QString subVisible("true");

            ModelPart *childChildItem = new ModelPart({ subName, subVisible });

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }
} // <--- End of Constructor

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    emit statusUpdateMessage(QString("Add button was clicked"), 0);

}
void MainWindow::handleTreeClicked() {
    /* Get the index of the selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Get a pointer to the item from the index */
    ModelPart *selectedPart = static_cast<ModelPart*>(index.internalPointer());

    /* Retrieve the name string from the internal data */
    QString text = selectedPart->data(0).toString();

    /* Show the message in the status bar */
    emit statusUpdateMessage(QString("The selected item is: ") + text, 0);
}

void MainWindow::on_actionOpen_File_triggered()
{

}

