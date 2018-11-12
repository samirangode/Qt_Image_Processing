#include <QMainWindow>
#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //ui->textBrowser->setText("Sample text for testing");

}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{  // Ui::MainWindow w;

    w.show();
}

void Form::on_pushButton_2_clicked()
{
   h.show();
}
