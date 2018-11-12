#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString sPath = "/home/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);

    ui->treeView->setModel(dirmodel);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(sPath);

    ui->listView->setModel(filemodel);

    ui->comboBox->addItem("Homogeneous Blur");
    ui->comboBox->addItem("Gaussian Blur");
    ui->comboBox->addItem("Median Blur");
    ui->comboBox->addItem("Erosion");
    ui->comboBox->addItem("Dilation");
    ui->comboBox->addItem("Sobel");
    ui->comboBox->addItem("Scharr");
    ui->comboBox->addItem("Laplace");
    ui->comboBox->addItem("Canny");
    ui->comboBox->addItem("Affine");
    ui->comboBox->addItem("Rotation");
    //ui->comboBox->addItem("Bilateral Blur");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString filepath = filemodel->fileInfo(index).absoluteFilePath();
    matOriginal = cv::imread(filepath.toStdString());
    cv::flip(matOriginal,matOriginal,1);
    cv::cvtColor(matOriginal,matOriginal,CV_BGR2RGB);

    QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->comboBox->currentText().toStdString().compare("Homogeneous Blur")==0)
    {   int i = ui->lineEdit->text().toInt();
        //for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
        cv::blur( matOriginal, matProcessed, cv::Size( i, i ), cv::Point(-1,-1) );
                 //if( display_dst( DELAY_BLUR ) != 0 ) { break; }

        QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
        ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
        ui->label_2->resize(ui->label_2->pixmap()->size());
    }

    if(ui->comboBox->currentText().toStdString().compare("Gaussian Blur")==0)
    {   int i = ui->lineEdit->text().toInt();
        //for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
        cv::GaussianBlur( matOriginal, matProcessed, cv::Size( i, i ), 0, 0 );
        QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
        ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
        ui->label_2->resize(ui->label_2->pixmap()->size());
    }

    if(ui->comboBox->currentText().toStdString().compare("Median Blur")==0)
    {   int i = ui->lineEdit->text().toInt();
        cv::medianBlur(matOriginal,matProcessed,i);
        QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
        ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
        ui->label_2->resize(ui->label_2->pixmap()->size());
    }

    if(ui->comboBox->currentText().toStdString().compare("Erosion")==0)
    {   int i = ui->lineEdit->text().toInt();
        cv::Mat element = cv::getStructuringElement(  cv::MORPH_RECT,
                                   cv::Size( 2*i + 1, 2*i+1 ),
                               cv::Point( i, i ) );

        cv::erode( matOriginal, matProcessed, element );
        QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
        ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
        //ui->label_2->resize(ui->label_2->pixmap()->size());
    }

    if(ui->comboBox->currentText().toStdString().compare("Dilation")==0)
    {   int i = ui->lineEdit->text().toInt();
        cv::Mat element = cv::getStructuringElement(  cv::MORPH_RECT,
                                   cv::Size( 2*i + 1, 2*i+1 ),
                               cv::Point( i, i ) );
        cv::dilate(matOriginal,matProcessed,element);
        QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
        ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
        //ui->label_2->resize(ui->label_2->pixmap()->size());
   }
   if(ui->comboBox->currentText().toStdString().compare("Sobel")==0)
   {
       cv::Mat mat_temp = matOriginal;
       cv::GaussianBlur( mat_temp, mat_temp, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
       cv::Mat mat_gray,grad_x, grad_y, abs_grad_x, abs_grad_y ;
       cv::cvtColor( mat_temp, mat_gray, cv::COLOR_RGB2GRAY );

       cv::Sobel( mat_gray, grad_x,CV_16S , 1, 0, 3, 1, 0, cv::BORDER_DEFAULT );
       cv::Sobel( mat_gray, grad_y,CV_16S, 0, 1, 3, 1, 0, cv::BORDER_DEFAULT );
       cv::convertScaleAbs( grad_x, abs_grad_x );
       cv::convertScaleAbs( grad_y, abs_grad_y );
       cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, matProcessed );
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       ui->label_2->resize(ui->label_2->pixmap()->size());
   }

   if(ui->comboBox->currentText().toStdString().compare("Scharr")==0)
   {
       cv::Mat mat_temp = matOriginal;
       cv::GaussianBlur( mat_temp, mat_temp, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
       cv::Mat mat_gray,grad_x, grad_y, abs_grad_x, abs_grad_y ;
       cv::cvtColor( mat_temp, mat_gray, cv::COLOR_RGB2GRAY );

       cv::Scharr( mat_gray, grad_x,CV_16S, 1, 0, 1, 0, cv::BORDER_DEFAULT );
       cv::Scharr( mat_gray, grad_y,CV_16S, 0, 1, 1, 0, cv::BORDER_DEFAULT );
       cv::convertScaleAbs( grad_x, abs_grad_x );
       cv::convertScaleAbs( grad_y, abs_grad_y );
       cv::addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, matProcessed );
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       ui->label_2->resize(ui->label_2->pixmap()->size());
   }

   if(ui->comboBox->currentText().toStdString().compare("Laplace")==0)
   {   int i = ui->lineEdit->text().toInt();
       cv::Mat mat_temp = matOriginal;
       cv::GaussianBlur( mat_temp, mat_temp, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
       cv::Mat mat_gray;
       cv::cvtColor( mat_temp, mat_gray, cv::COLOR_RGB2GRAY );
       cv::Mat abs_processed;
       cv::Laplacian( mat_gray, abs_processed, CV_16S, 2*i+1, 1, 0, cv::BORDER_DEFAULT );
       cv::convertScaleAbs( abs_processed, matProcessed );
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       ui->label_2->resize(ui->label_2->pixmap()->size());
   }

   if(ui->comboBox->currentText().toStdString().compare("Canny")==0)
   {   int i = ui->lineEdit->text().toInt();
       int j = ui->spinBox->value();
       int lowThreshold = i;
       int kernel_size = j;
       cv::Mat mat_temp = matOriginal;
       cv::Mat mat_gray;
       cv::cvtColor(mat_temp, mat_gray, cv::COLOR_BGR2GRAY);
       cv::blur(mat_gray,matProcessed,cv::Size(3,3));
       cv::Canny(matProcessed, matProcessed, lowThreshold, lowThreshold*3, kernel_size);
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       ui->label_2->resize(ui->label_2->pixmap()->size());
   }
   if(ui->comboBox->currentText().toStdString().compare("Affine")==0)
   {
       cv::Point2f srcTri[3];
       cv::Point2f dstTri[3];
       cv::Mat warp_mat( 2, 3, CV_32FC1 );
       cv::Mat src, warp_dst, warp_rotate_dst;
       src = matOriginal;
       srcTri[0] = cv::Point2f( 0,0 );
       srcTri[1] = cv::Point2f( src.cols - 1, 0 );
       srcTri[2] = cv::Point2f( 0, src.rows - 1 );
       dstTri[0] = cv::Point2f( src.cols*0.0, src.rows*0.33 );
       dstTri[1] = cv::Point2f( src.cols*0.85, src.rows*0.25 );
       dstTri[2] = cv::Point2f( src.cols*0.15, src.rows*0.7 );
       warp_mat =  cv::getAffineTransform( srcTri, dstTri );
       cv::warpAffine( src, warp_dst, warp_mat, warp_dst.size() );
       matProcessed = warp_dst;
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       ui->label_2->resize(ui->label_2->pixmap()->size());
   }

   if(ui->comboBox->currentText().toStdString().compare("Rotation")==0)
   {   float angle = ui->lineEdit->text().toFloat();
       double scale = 0.6;
       cv::Point center = cv::Point( matOriginal.cols/2, matOriginal.rows/2 );
       cv::Mat rot_mat( 2, 3, CV_32FC1 );
       rot_mat = cv::getRotationMatrix2D( center, angle, scale );
       cv::warpAffine( matOriginal, matProcessed, rot_mat, matOriginal.size() );
       QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matOriginal.rows, matProcessed.step, QImage::Format_Indexed8);
       ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
       //ui->label_2->resize(ui->label_2->pixmap()->size());
   }

}

void MainWindow::on_pushButton_2_clicked()
{
    h.show();
}
