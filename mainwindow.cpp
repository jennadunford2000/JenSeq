#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <cstdlib>
#include <QRegularExpression>
#include <Eigen/Dense>

QList<QString> outputList;
int GValue = 0;
int TValue = 0;
int CValue = 0;
int AValue = 0;
int total;
int notBaseValue = 0;

using namespace std;
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

void MainWindow::on_temppushButton_clicked()
{
    QMessageBox::about(this,"Title here", "kms");
}


void MainWindow::on_temppushButton_2_clicked()
{
    QStringList fileNames;
    QString strng;
    ui->tempOutput->clear();

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
                ui->tempOutput->insertPlainText(line + "\n");
                outputList.append(line);
            }
            i++;
        };

}


void MainWindow::on_temppushButton_3_clicked()
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
        ui->tempALabel->setText(QString::number(AValue));
        ui->tempGLabel->setText(QString::number(GValue));
        ui->tempTLabel->setText(QString::number(TValue));
        ui->tempCLabel->setText(QString::number(CValue));
        ui->tempInvalidLabel->setText(QString::number(notBaseValue));

        total = AValue + GValue + TValue + CValue;
        ui->temptotalLabel->setText(QString::number(total));
        if(total != 0)
        {
            double GPercent = ((double)GValue/(double)total) * 100.00;
            ui->tempGPercent->setText("G Percentage: " + QString::number(GPercent) + "%");
            double CPercent = ((double)CValue / (double)total) * 100.00;
            ui->tempCPercent->setText("C Percentage: " + QString::number(CPercent) + "%");
            double APercent = ((double)AValue / (double)total) * 100.00;
            ui->tempAPercent->setText("A Percentage: " + QString::number(APercent) + "%");
            double TPercent = ((double)TValue / (double)total) * 100.00;
            ui->tempTPercent->setText("T Percentage: " + QString::number(TPercent) + "%");
        }

    }
}
void MainWindow::disableTempUI()
{
    QList<QLabel*> LabelList = this->findChildren<QLabel*>(QRegularExpression("temp.*"));
    QList<QPushButton*> ButtonList = this->findChildren<QPushButton*>(QRegularExpression("temp.*"));
    QList<QTextEdit*> TextList = this->findChildren<QTextEdit*>(QRegularExpression("temp.*"));

    foreach (QLabel *item, LabelList) {
        item->setVisible(false);
    }

    foreach (QPushButton *item, ButtonList) {
        item->setVisible(false);
    }


    foreach (QTextEdit *item, TextList) {
        item->setVisible(false);
    }

}

void MainWindow::on_AlignmentBut_clicked()
{
    disableTempUI();
}

void MainWindow::testAlign()
{
    //we need our two sequences
    QString seq1[] = {"T","T","G","A","C","G","T"};
    QString seq2[] = {"T","G","A","C","G"};

    char sSeq1[] = {'T','T','G','A','C','G','T'};
    char sSeq2[] = {'T','G','A','C','G'};


    //declaring the matrix
    Eigen::MatrixXd AlignMatrix(sizeof(seq1)+1,sizeof(seq2)+1);


    //scoring values
    int mismatch = -1;
    int match = 1;
    int indel = -2;

    //Initalize the matrix
    //traverse the matrix
    //left to right
    //from 1;1
    //at each point
    //check up sum
    //check left sum
    //check diagonal sum
    //find highest sum answer/s
    //store direction taken in new array
    //store sum value in matrix
    //once finished -> traceback
    //from bottom right follow "direction arrows" backwards
    //if move left, then gap, if move diagonal, then match - store possible alignment
    //if multiple possible directions, do it again - store possible alignment
    ui->matrix->clearContents();
    ui->matrix->clear();


    ui->matrix->setRowCount(sizeof(sSeq2)+1);
    ui->matrix->setColumnCount(sizeof(sSeq1)+1);

    ui->matrix->setHorizontalHeaderItem(0,new QTableWidgetItem(" "));
    ui->matrix->setVerticalHeaderItem(0,new QTableWidgetItem(" "));


    for (int var = 1; var <= sizeof(sSeq1); var++) {

        ui->matrix->setHorizontalHeaderItem(var,new QTableWidgetItem(seq1[var-1]));

    }

    for (int var = 1; var <= sizeof(sSeq2); var++) {

        ui->matrix->setVerticalHeaderItem(var,new QTableWidgetItem(seq2[var-1]));

    }


    for(int i = 0; i< sizeof(sSeq1)+1; i++)
    {
        if(i==0)
        {
            ui->matrix->setItem(0,i,new QTableWidgetItem(QString::number(i)));
        }
        else
        {
            ui->matrix->setItem(0,i, new QTableWidgetItem(QString::number(i * -2)));
        }

    }

    for(int j = 0; j< sizeof(sSeq2)+1; j++)
    {
        if(j!=0)
        {
            ui->matrix->setItem(j,0, new QTableWidgetItem(QString::number(j * -2)));
        }

    }


    //CALCULATION PART
    //check top (up value + indel)
    //check left (left value + indel)
    //check diagonal (diagonal value (if col/row match then value + match) (if col/row mismatch then value +mismatch)

    //(1;1)
    //xxxxxxx
    //x
    //x
    //x
    //x
    int up = 1;
    int left = 2;
    int diag = 3;
    //need to store the direction value
    //1 for up
    //2 for left
    //3 for diag

    for (int r = 1; r < sizeof(sSeq2); ++r) {
        for (int c = 1; c < sizeof(sSeq1); ++c) {
            int topsum;
            int diagsum;
            int leftsum;
            int direction;



        }

    }

}


void MainWindow::on_pushButton_clicked()
{
    ui->windows->setCurrentIndex(ui->windows->currentIndex()+1);
}


void MainWindow::on_pushButton_2_clicked()
{
    testAlign();
}

