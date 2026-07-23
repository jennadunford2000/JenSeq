#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString env;
    env = getenv("NCBI_API_KEY");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::about(this,"Title here", "kms");
}


void MainWindow::on_pushButton_2_clicked()
{
    QStringList fileNames;
    QString strng;

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Text files (*.txt)"));

        dialog.exec();

        fileNames = dialog.selectedFiles();
        QMessageBox::about(this,"Title here",fileNames.first());

        QFile inputFile(QString(fileNames.first()));
        inputFile.open(QIODevice::ReadOnly);
        if (!inputFile.isOpen())
            return;

        QTextStream stream(&inputFile);
        for (QString line = stream.readLine();
             !line.isNull();
             line = stream.readLine()) {
            ui->Output->insertPlainText(line + "\n");
        };

}

