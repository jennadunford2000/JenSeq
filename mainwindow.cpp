#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include <cstdlib>
#include <QRegularExpression>
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <QMovie>


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
    ui->selectExample->addItem("GPX");
    ui->selectExample->addItem("Small Example");
    ui->selectExample->setCurrentIndex(0);

    ui->alignedOne->clear();
    ui->compseq->clear();
    ui->compseq_2->clear();

    QMovie *movie = new QMovie("D:/Escape2026/JenSeq/dna.gif");
    if (!movie->isValid())
    {
        std::cout << "why movie no work waaaah";
    }
    QSize size(150,100);
    movie->setScaledSize(size);
    ui->DNA->setMovie(movie);
    movie->start();

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

void setTableFeatures(QTableWidget *table, int vertSize, int horiSize, int fontsize)
{
    table->horizontalHeader()->setMinimumSectionSize(horiSize);
    table->horizontalHeader()->setDefaultSectionSize(horiSize);

    table->verticalHeader()->setMinimumSectionSize(vertSize);
    table->verticalHeader()->setDefaultSectionSize(vertSize);
    QFont font("Calibri", fontsize, QFont::Bold);
    table->setFont(font);
}


string readfile(string filename){
    // Open the text file for reading
    std::ifstream f(filename);

    // Check if the file was opened successfully
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        return "";
    }

    std::string s;

    while (std::getline(f, s))
        std::cout << s << std::endl;

    // Read each line from the file

    // Close the file
    f.close();

    return s;
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

    ui->alignedOne->setText("");
    ui->compseq->setText("");
    ui->compseq_2->setText("");

    int timedelay = 3;
    int timedelaytrace =20;
    ui->textEdit->insertPlainText("we out here 0 \n");
    //we need our two sequences
    //QString seq1[] = {"T","T","G","A","C","G","T"};
    //QString seq2[] = {"T","G","A","C","G"};

   // char sSeq1[] = {};
   // char sSeq2[] = {};
    //QString sSeq1 = "CCGCAAGCTGCGTAAGCGGCTCCTCCGCGATGCCGATGACCTGCAGAAGCGCCTGGCAGTGTACCAGGCCGGGGCCCGCGAGGGCGCCGAGCGCGGCCTCAGCG";
   // QString sSeq2 = "GCGCAAGCTGCGTAAGCGGCTCCTCCGCGATGCCGATGACCTGCAGAAGTGCCTGGCAGTGTACCAGGCCGGGGCCCGCGAGGGCGCCGAGCGCGGCCTCAGCG";

    QString sSeq1;
    QString sSeq2;

    QString theAlignedOne = "";

    if(ui->selectExample->currentIndex() == 0)
    {
        sSeq1 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/GPX_me.txt"));
        sSeq2 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/GPX_other.txt"));
        setTableFeatures(ui->matrix, 9, 18, 3);
        timedelay = 3;
        timedelaytrace =20;
    }
    else
    {
        sSeq1 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/ex1.txt"));
        sSeq2 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/ex2.txt"));
        setTableFeatures(ui->matrix, 30, 30, 12);
        timedelay = 10;
        timedelaytrace =100;
    }


    //QString sSeq1 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/ex1.txt"));
   // QString sSeq2 = QString::fromStdString(readfile("D:/Escape2026/JenSeq/ex2.txt"));
  //  char sSeq1[] = {'T','T','G','A','C','G','T'};
  //  char sSeq2[] = {'T','G','A','C','G'};

    //char seq1[] = {'C','C','G','C','A','A','G','C','T','G','C','G','T','A','A','G','C','G','G','C','T','C','C','T','C','C','G','C','G','A','T','G','C','C','G','A','T','G','A','C','C','T','G','C','A','G','A','A','G','C','G','C','C','T','G','G','C','A','G','T','G','T','A','C','C','A','G','G','C','C','G','G','G','G','C','C','C','G','C','G','A','G','G','G','C','G','C','C','G','A','G','C','G','C','G','G','C','C','T','C','A','G','C','G'};
    //char seq2[] = {'G','C','G','C','A','A','G','C','T','G','C','G','T','A','A','G','C','G','G','C','T','C','C','T','C','C','G','C','G','A','T','G','C','C','G','A','T','G','A','C','C','T','G','C','A','G','A','A','G','T','G','C','C','T','G','G','C','A','G','T','G','T','A','C','C','A','G','G','C','C','G','G','G','G','C','C','C','G','C','G','A','G','G','G','C','G','C','C','G','A','G','C','G','C','G','G','C','C','T','C','A','G','C','G'};

    char seq1[sSeq1.size()+1];
    strcpy(seq1, (sSeq1.toStdString()).c_str());

    char seq2[sSeq2.size()+1];
    strcpy(seq2, (sSeq2.toStdString()).c_str());


    ui->textEdit->insertPlainText("we out here 1 \n");


    ui->textEdit->insertPlainText("seq1 size: " + QString::number(sizeof(seq1)) + "\n");
    ui->textEdit->insertPlainText("seq2 size: " + QString::number(sizeof(seq2)) + "\n");


    ui->textEdit->insertPlainText("we out here 0 \n");



    //declaring the matrix
    Eigen::MatrixXd AlignMatrix(sizeof(seq1)+5,sizeof(seq2)+5);
    Eigen::MatrixXd DirectionMatrix(sizeof(seq1)+5,sizeof(seq2)+5);


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


    //ui->matrix->setRowCount(sizeof(sSeq2)+1);
    //ui->matrix->setColumnCount(sizeof(sSeq1)+1);


    ui->matrix->setColumnCount(sizeof(seq1));
    ui->matrix->setRowCount(sizeof(seq2));

    ui->matrix->setHorizontalHeaderItem(0,new QTableWidgetItem(" "));
    ui->matrix->setVerticalHeaderItem(0,new QTableWidgetItem(" "));


    for (int var = 1; var <= sizeof(seq1); var++) {

        ui->matrix->setHorizontalHeaderItem(var,new QTableWidgetItem(QString(seq1[var-1])));

        QString base = QString(seq1[var-1]);
        QTableWidgetItem* item =ui->matrix->horizontalHeaderItem(var);

        if(base == "G")
        {
            QColor color(QColor("yellow"));
            item->setBackground(color);

        }
        else if(base == "T")
        {
            QColor color(QColor("cyan"));
            item->setBackground(color);
        }
        else if(base == "A")
        {
            QColor color(QColor("magenta"));
            item->setBackground(color);
        }
        else if(base == "C")
        {
            QColor color(QColor("green"));
            item->setBackground(color);
        }
    }


    for (int var = 1; var <= sizeof(seq2); var++) {

        ui->matrix->setVerticalHeaderItem(var,new QTableWidgetItem(QString(seq2[var-1])));

        QString base = QString(seq2[var-1]);
        QTableWidgetItem* item =ui->matrix->verticalHeaderItem(var);

        if(base == "G")
        {
            QColor color(QColor("yellow"));
            item->setBackground(color);

        }
        else if(base == "T")
        {
            QColor color(QColor("cyan"));
            item->setBackground(color);
        }
        else if(base == "A")
        {
            QColor color(QColor("magenta"));
            item->setBackground(color);
        }
        else if(base == "C")
        {
            QColor color(QColor("green"));
            item->setBackground(color);
        }

    }


    for(int i = 0; i<= sizeof(seq1); i++)
    {
        if(i==0)
        {
            std::cout << "here" << std::endl;
            ui->matrix->setItem(0,i,new QTableWidgetItem(QString::number(i)));
            AlignMatrix(0,i) = 0;
        }
        else
        {
                ui->matrix->setItem(0,i, new QTableWidgetItem(QString::number(i * -2)));
                AlignMatrix(0,i) = i * -2;

        }

    }

    for(int j = 0; j<= sizeof(seq2); j++)
    {
        if(j!=0)
        {
            ui->matrix->setItem(j,0, new QTableWidgetItem(QString::number(j * -2)));
            AlignMatrix(j,0) = j * -2;
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
    const int up = 1;
    const int left = 2;
    const int diag = 3;
    //need to store the direction value
    //1 for up
    //2 for left
    //3 for diag

    for (int r = 1; r < sizeof(seq2); ++r) {
        for (int c = 1; c < sizeof(seq1); ++c) {
            int topsum;
            int diagsum;
            int leftsum;
            int highsum;
            int direction; //1 - top, 2 - left, 3 - diagonal

            topsum = AlignMatrix(r-1,c) + indel;
            if(sSeq1[c-1] == sSeq2[r-1])
            {
                diagsum = AlignMatrix(r-1,c-1) + match;
                ui->textEdit->insertPlainText(QString(seq1[c-1]) + " and " +  QString(seq2[r-1]) + " match \n");
            }else{
                diagsum = AlignMatrix(r-1,c-1) + mismatch;
                ui->textEdit->insertPlainText(QString(seq1[c-1]) + " and " +  QString(seq2[r-1]) + " do not match \n");

            }
            leftsum = AlignMatrix(r,c-1) + indel;
            highsum = max ({topsum, diagsum, leftsum});
            if(highsum == topsum)
            {
                direction = up;
            }
            else if(highsum == leftsum)
            {
                direction = left;
            }
            else if(highsum == diagsum)
            {
                direction = diag;
            }
            AlignMatrix(r,c) = highsum;
            DirectionMatrix(r,c) = direction;
            ui->matrix->setItem(r,c,new QTableWidgetItem(QString::number(highsum)));
            QTimer timer;
            timer.setInterval(timedelay);
            QEventLoop loop;
            connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
            timer.start();
            loop.exec();
        }
        QTimer timer;
        timer.setInterval(timedelay);
        QEventLoop loop;
        connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        timer.start();
        loop.exec();


    }

    ui->textEdit->insertPlainText("Beginning traceback \n");

   // if(DirectionMatrix(sizeof(seq2),sizeof(seq1)) == 3)
  //  {
  //      theAlignedOne.append(sSeq1[sizeof(seq1)]);
   // }
  //  else{
  //      theAlignedOne.append("-");
  //  }


    QTableWidgetItem* item = ui->matrix->item(sizeof(seq2)-1,sizeof(seq1)-1);
    ui->alignedOne->clear();
    ui->alignedOne->setText(theAlignedOne);
    QColor color(QColor("red"));
    item->setBackground(color);
    for (int r = sizeof(seq2)-1; r >= 1;){
        for(int c = sizeof(seq1)-1; c >= 1;)
        {
            int directionCheck = DirectionMatrix(r,c);
            ui->sequence->insertPlainText("we are on " + QString(QChar::fromLatin1((seq1[c-1]))) + "\n");
            ui->sequence->insertPlainText("coordinates are " + QString::number(r) + "," + QString::number(c) + "\n");
            ui->sequence->insertPlainText("the direction is: " + QString::number(directionCheck) + "\n");
            switch(directionCheck){
            case up:
                theAlignedOne.append("-");
                ui->alignedOne->clear();
                ui->alignedOne->setText(theAlignedOne);
                r = r-1;
                ui->textEdit->insertPlainText("direction was up \n");
                break;
            case left:
                theAlignedOne.append("-");
                ui->alignedOne->clear();
                ui->alignedOne->setText(theAlignedOne);
                c = c-1;
                ui->textEdit->insertPlainText("direction was left \n");
                break;
            case diag:
                theAlignedOne.append(seq1[c-1]);
                ui->alignedOne->clear();
                ui->alignedOne->setText(theAlignedOne);
                c = c-1;
                r = r-1;
                ui->textEdit->insertPlainText("direction was diagonal \n");
                break;
            default:
                break;
            }

            QTimer timer;
            timer.setInterval(timedelaytrace);
            QEventLoop loop;
            connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
            timer.start();
            loop.exec();


            QTableWidgetItem* item = ui->matrix->item(r,c);
            QColor color(QColor("red"));
            item->setBackground(color);


        }
    }

    ui->alignedOne->clear();
    std::reverse(theAlignedOne.begin(), theAlignedOne.end());
    ui->alignedOne->setText(theAlignedOne);
    ui->compseq->setText(sSeq1);
    ui->compseq_2->setText(sSeq2);

}


void MainWindow::on_pushButton_clicked()
{
    ui->windows->setCurrentIndex(ui->windows->currentIndex()+1);
}


void MainWindow::on_pushButton_2_clicked()
{
    testAlign();
}

