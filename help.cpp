#include "help.h"
#include "ui_help.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>

Help::Help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);

/*    QFile file("/home/samiran/build-Image_gui-Desktop-Debug/help_Qt_test.txt");

    QTextStream in(&file);

    ui->textBrowser->setPlainText(in.readAll());
*/
/*    QFile file("/home/samiran/build-Image_gui-Desktop-Debug/help_Qt_test.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString content = stream.readAll();
    file.close();
    //setPlainText(content);
    ui->textBrowser->setPlainText(content);
*/

//   ui->textBrowser->setPlainText("this is a sample");


}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{

}
