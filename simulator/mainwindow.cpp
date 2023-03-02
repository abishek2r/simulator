#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <list>
#include <QtMath>
#include <QVector>
QList<float> n;
QList<QList<float>> final;
QVector<double> tri;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->customplot->addGraph();
    ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customplot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customplot->xAxis->setLabel("a");
    ui->customplot->yAxis->setLabel("b");
    ui->customplot->xAxis->setRange(100,100);
    ui->customplot->xAxis->setRange(100,100);
    qDebug()<<"a";
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP ::iRangeZoom | QCP::iSelectPlottables);
    QVector<double> x={1,2,3},y={5,6,7};
    ui->customplot->graph(0)->setData(x,y);

}

MainWindow::~MainWindow()
{
    delete ui;
}





void Write(QString Filename,QString n){
    QFile mFile(Filename);
    if (!mFile.open(QFile::WriteOnly|QFile::Text ))
    {
        qDebug()<<"not";
        return;
    }
    QTextStream out(&mFile);

    out<<n;
    mFile.flush();
    mFile.close();
}
QString Read(QString Filename){
    QFile mFile(Filename);
    if (!mFile.open(QFile::ReadOnly | QFile::Text))
    {   qDebug()<<"cou";
        return "a";
    }
    QTextStream in (&mFile);
    QString mText = in.readAll();
    mFile.close();
    return mText;
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    ui->label->setText(ui->tableWidget->item(row,column)->text());
}


void MainWindow::on_pushButton_clicked()
{QString n;
    int a=ui->tableWidget->columnCount();
    int b=ui->tableWidget->rowCount();
    for(int i=0;i<b;i++){
        for (int j=0;j<a;j++){
            n=n+ui->tableWidget->item(i,j)->text()+" ";
        }
       n=n+"\n";
    }
    QString filename2=QFileDialog::getSaveFileName(
                    this,
                    tr("open"),
                    "D://",
                    "All files(*.*) "
                    );

    Write(filename2,n);
}


void MainWindow::on_pushButton_2_clicked()
{QString filename1=QFileDialog::getOpenFileName(
                this,
                tr("open"),
                "D://",
                "All files(*.*) "
                );
    QString mText=Read(filename1);
    QList a=mText.split("\n");
    int len=a.size()-1;
    QTableWidgetItem *l;

    for (int i=0;i<len;i++){
        QList b=a[i].split(" ");
        for (int j=0;j<3;j++){
            l=new QTableWidgetItem;
            l->setText(b[j]);
            ui->tableWidget->setItem(i,j,l);
        }

    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
}

void triangle(int d,float v){
    float x=0;
    int T=d/v;
    qDebug()<<T;
    n={};

    for (int q=0;q<=T;q++){
        if (q<T/2){

       x=x+(4.0*d)/(T*T)*q;

        tri.append((4.0*d)/(T*T)*q);
        n.append(x);
        }
        else{
                 x=x+(4.0*d)/(T*T)*(T-q);
                 n.append(x);
                 tri.append((4.0*d)/(T*T)*(T-q));

        }
}
}
void trapezoidal(int d,int v){
    int x=0;
    int T=d/v;


    for (int q=0;q<=100;q++){
        if (q<T/6){

       x=x+(36*d)*(T)/(5*T*T);

       n.append(x);}
         else if(q<5*T/6){
                 x=x+(d*6)/(T*5);
               n.append(x);


        }
        else{
            x=x+(36*d)*(T-q)/(5*T*T);
            n.append(x);

        }

    }
}
void sine(int d,int v){
        double x=0;
        int T=d/v;
        int a=0;
        int b=0;
        for (int q=0;q<=100;q++){
            x=x+d*T*7*sin(q*22/(T*7))/44;
            n.append(x);
            }
}
void MainWindow::on_pushButton_4_clicked()
{    int a=ui->tableWidget->columnCount();
     int b=ui->tableWidget->rowCount();
     for(int i=1;i<b;i++){

             float x1=(ui->tableWidget->item(i-1,0)->text()).toFloat();
             float y1=(ui->tableWidget->item(i-1,1)->text()).toFloat();
             float z1=(ui->tableWidget->item(i-1,2)->text()).toFloat();
             float x2=(ui->tableWidget->item(i,0)->text()).toFloat();
             float y2=(ui->tableWidget->item(i,1)->text()).toFloat();
             float z2=(ui->tableWidget->item(i,2)->text()).toFloat();


    float x=x2-x1;
    float y=y2-y1;
    float z=z2-z1;
    float V=(ui->lineEdit->text()).toFloat();
    float d=qSqrt(x*x+y*y+z*z);
    int T=d/V;
    float ratiox=x/d;
    float ratioy=y/d;
    float ratioz=z/d;

    if (ui->radioButton->isChecked()){
        triangle(d,V);}
    if (ui->radioButton_2->isChecked()){

        trapezoidal(d,V);}
    if(ui->radioButton_3->isChecked()){
        sine(d,V);}
    int le=n.length();

    float diff=(d-n[le-1])/T;
    qDebug()<<diff;
    for (int p=0;p<le;p++){
        qDebug()<<n[p]+diff<<p;
        float yu=diff*p;
        final.append({(n[p]+yu)*ratiox+x1,(n[p]+yu)*ratioy+y1,(n[p]+yu)*ratioz+z1});
    }



}
      int l=final.length();
      QString h="";
       QTableWidgetItem *nq;
      for(int i=0;i<l;i++){
          ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
          for (int j=0;j<3;j++){

              nq=new QTableWidgetItem;
              nq->setText(QString::number(final[i][j]));
              ui->tableWidget_2->setItem(i,j,nq);
              h=h+QString::number(final[i][j])+" ";
          }
         h=h+"\n";
      }
       }


void MainWindow::on_pushButton_5_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
}


void MainWindow::on_pushButton_6_clicked()
{
    float no=tri.length();
    QVector<double> x={0},y={0};
ui->customplot->graph(0)->setData(x,y);
    for (float i=0;i<no;i++){
        x.append(i);
        y.append(tri[i]);
   }
     ui->customplot->graph(0)->setData(x,y);
}

