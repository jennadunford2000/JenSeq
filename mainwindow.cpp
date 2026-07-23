#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <cstdlib>


QList<QString> outputList;
int GValue = 0;
int TValue = 0;
int CValue = 0;
int AValue = 0;
int total;
int notBaseValue = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    ui->Output->clear();

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Text files (*.txt)"));

        dialog.exec();

        fileNames = dialog.selectedFiles();
        QMessageBox::about(this,"Title here",fileNames.first());

        QFile inputFile(QString(fileNames.first()));
        inputFile.open(QIODevice::ReadOnly);
        if (!inputFile.isOpen())
            return;
        int i = 0;
        QTextStream stream(&inputFile);
        for (QString line = stream.readLine();
             !line.isNull();
             line = stream.readLine()) {
            if(i>0)
            {
                ui->Output->insertPlainText(line + "\n");
                outputList.append(line);
            }
            i++;
        };

}


void MainWindow::on_pushButton_3_clicked()
{
    if(outputList.empty())
    {
        QMessageBox::about(this,"No items to analyse", "Your data is empty. Please load a file");
    }
    else
    {
        AValue = 0;
        GValue = 0;
        CValue = 0;
        TValue = 0;
        total = 0;
        notBaseValue = 0;
        for(int a = 0; a < outputList.length(); a++)
        {
            QString test = outputList.value(a);
            for(int b = 0; b< test.length(); b++)
            {
                if (test.at(b) != " ")
                {
                    switch (test.at(b).toLatin1()) {
                    case 'A':
                        AValue++;
                        break;
                    case 'G':
                        GValue++;
                        break;
                    case 'T':
                        TValue++;
                        break;
                    case 'C':
                        CValue++;
                        break;
                    default:
                        notBaseValue++;
                        break;
                    }
                }

            }
        }
        ui->ALabel->setText(QString::number(AValue));
        ui->GLabel->setText(QString::number(GValue));
        ui->TLabel->setText(QString::number(TValue));
        ui->CLabel->setText(QString::number(CValue));
        ui->InvalidLabel->setText(QString::number(notBaseValue));

        total = AValue + GValue + TValue + CValue;
        ui->totalLabel->setText(QString::number(total));
        if(total != 0)
        {
            double GPercent = ((double)GValue/(double)total) * 100.00;
            ui->GPercent->setText("G Percentage: " + QString::number(GPercent) + "%");
            double CPercent = ((double)CValue / (double)total) * 100.00;
            ui->CPercent->setText("C Percentage: " + QString::number(CPercent) + "%");
            double APercent = ((double)AValue / (double)total) * 100.00;
            ui->APercent->setText("A Percentage: " + QString::number(APercent) + "%");
            double TPercent = ((double)TValue / (double)total) * 100.00;
            ui->TPercent->setText("T Percentage: " + QString::number(TPercent) + "%");
        }

    }
}

