#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include "math.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

double x_a[255];
double y_a[255];
int k = 3;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int q = ui->tab->rowCount();

    for (int i = 0; i<q; i++)
    {
        //создаем массив для 1 столбца
        QTableWidgetItem * u = ui->tab->item(i,0);
        if (u == NULL)
        {
            QMessageBox::information(this,"Внимание","Вы не ввели координаты вершин");
        return;
        }
        if (u != NULL)
        {
            x_a[i] = ui->tab->item(i,0)->text().toFloat();
        //u = ui->tableWidget->item(i,1);
        }

        //создаем массив для 2 столбца
        QTableWidgetItem * h = ui->tab->item(i,1);
        if (h == NULL)
        {
            QMessageBox::information(this,"Внимание","Вы не ввели координаты вершин");
        return;
        }
        if (h != NULL)
        {
            y_a[i] = ui->tab->item(i,1)->text().toFloat();
        }

        if (q <= 2)
        {
            QMessageBox::information(this,"Внимание","Данная фигура является точной или отрезком, а следовательно не обладает площадью");
            return;
        }
    }

    double s=0, p=0, pr1=0, pr2=0;

//    if (q>3) //проверяем на пересечение
//    {
//        for (int i = 0; i<q; i++)
//        {
//            //x:=((x1*y2-x2*y1)*(x4-x3)-(x3*y4-x4*y3)*(x2-x1))/((y1-y2)*(x4-x3)-(y3-y4)*(x2-x1));
//            pr1 = ((x_a[i]*y_a[i+1]-x_a[i+1]*y_a[i])*(x_a[i+3]-x_a[i+2])-(x_a[i+2]*y_a[i+3]-))

//            if ()
//            {

//            }
//        }
//    }

    int q1=q-1;
    for(int i=0; i<q; i++)
    {
        for (int j=2; j<q1; j++)
        //j=2(необходимо иметь 2 стороны)
        {
            //p1 p2 - переменный сторон
            float p1=((x_a[i]*y_a[i+1]-x_a[i+1]*y_a[i])*(x_a[j+1]-x_a[j])-(x_a[j]*y_a[j+1]-x_a[j+1]*y_a[j])*(x_a[i+1]-x_a[i]))/((y_a[i]-y_a[i+1])*(x_a[j+1]-x_a[j])-(y_a[j]-y_a[j+1])*(x_a[i+1]-x_a[i]));
            float p2=((y_a[j]-y_a[j+1])*p1-(x_a[j]*y_a[j+1]-x_a[j+1]*y_a[j]))/(x_a[j+1]-x_a[j]);
            if (((x_a[i]<=p1) and (x_a[i+1]>=p1) and (x_a[j]<=p1) and (x_a[j+1]>=p1)) or ((y_a[i]<=p2) and (y_a[i+1]>=p2) and (y_a[j]<=p2) and (y_a[j+1]>=p2)))
            {
                QMessageBox::information(this, "Ошибка","Стороны вашего многоугольника пересeкаются!");
                return;
            }
        }
    }

    for (int i = 0; i<q-1; i++)
    {
        s = s + x_a[i]*y_a[i+1] - x_a[i+1]*y_a[i];
    }
    s = s + x_a[q-1]*y_a[0]-x_a[0]*y_a[q-1];
    s=s/2;

    if (s==0)
    {
        QMessageBox::information(this,"Внимание","Площадь равна 0, следовательно фигура не является многоугольником по определению");
    }

    ui->pl->setText(QString::number(fabs(s)));


    if (s != 0)
    {
        for (int i=0; i<q-1;i++)
        {
            p = p + sqrt(pow((x_a[i+1]-x_a[i]),2) + pow((y_a[i+1]-y_a[i]),2));
        }
       p = p + sqrt(pow((x_a[0]-x_a[q-1]),2) + pow((y_a[0]-y_a[q-1]),2));

       ui->per->setText(QString::number(fabs(p)));
    }



QFile file("E:/QT/MNOGOUGOL/N_ug.txt");

file.open(QIODevice::ReadWrite);
file.remove();
file.close();

if (file.open(QIODevice::ReadWrite | QIODevice::Append))
{
 QTextStream out (&file);
 out << "X Y \r\n";
 for (int i=0;i< ui->tab->rowCount();i++)
 {
     out << x_a[i]<< " " << y_a[i] << "\r\n";
 }
 out << "--------------------------------------------------------"<< "\r\n"<< "Vershini =" << q <<   " " <<"P=" << p <<  " "<<  "S="  << abs(s) <<"\r\n"<< "--------------------------------------------------------";

//  file.write(S_Q ,sizeof( QString ));


file.close();
}
file.open(QIODevice::ReadWrite);

ui->textBrowser->setText(file.readAll());

file.close();

}











void Widget::on_pushButton_2_clicked()
{
    ui->tab->setRowCount(ui->tab->rowCount()-1);
}

void Widget::on_pushButton_3_clicked()
{
    ui->tab->setRowCount(ui->tab->rowCount()+1);
}

void Widget::on_pushButton_4_clicked()
{
    QFile file(QFileDialog::getSaveFileName(this, "Сохранить как","E:/QT/MNOGOUGOL", "Text (*.txt)"));
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<ui->tab->rowCount()<< "\r\n";

    for (int i=0; i<ui->tab->rowCount(); i++)
    {
        out<< x_a[i]<< " " << y_a[i]<< "\r\n";
    }

    file.close();

}

void Widget::on_pushButton_5_clicked()
{
    QFile file(QFileDialog::getOpenFileName(this, "Сохранить как","E:/QT/MNOGOUGOL", "Text (*.txt)"));
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);

    int a=0;
    out>>a;
    ui->tab->setRowCount(a);

    QString x, y;
    for (int i=0; i<ui->tab->rowCount(); i++)
    {
        out >> x >> y;
        ui->tab->setItem(i,0,new QTableWidgetItem(x));
        ui->tab->setItem(i,1,new QTableWidgetItem(y));

    }
    file.close();

}
