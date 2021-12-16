#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QDebug>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    progbar = new QProgressBar();
    statusBar()->addWidget(progbar);


    cfg = new QSettings("webcam.ini", QSettings::IniFormat);
    readconfig();

    connect(ui->pbConnect,SIGNAL(clicked(bool)), this, SLOT(onConnect(bool)));
    connect(ui->cbCams,SIGNAL(currentIndexChanged(int)), this, SLOT(onIdxChanged(int)));
    connect(ui->wev, SIGNAL(loadFinished(bool)), this, SLOT(onloadFinished(bool)));
    connect(ui->wev, SIGNAL(loadProgress(int)), this, SLOT(onLoadProgress(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readconfig(){
    cfg->beginGroup("main");
    ui->leIP->setText(cfg->value("ip", "http://192.168.0.20").toString());
    ui->leURL->setText(cfg->value("url", "/video/mjpg.cgi").toString());

    cfg->endGroup();
    cfg->beginGroup("camlist");
    //cam list
    QStringList camkeys = cfg->childKeys();
    if (camkeys.size()>0){
        for (int i = 0; i < camkeys.size(); ++i){
            camlist << cfg->value(camkeys.at(i)).toString();
        }
    } else {
        //default value
        camlist << "DCS-930L" << "DCS-5030L";
    }
    ui->cbCams->addItem("");
    for (int i = 0; i < camlist.size(); ++i){
//        qDebug() << i << ": " << camlist.at(i);
        ui->cbCams->addItem(camlist.at(i));
    }
    cfg->endGroup();

}

void MainWindow::saveconfig(){
    cfg->beginGroup("main");
    cfg->setValue("ip", ui->leIP->text());
    cfg->setValue("url", ui->leURL->text());
    cfg->endGroup();
}

void MainWindow::onConnect(bool checked){
    //ui->wev->load(QUrl("http://admin:@192.168.50.15/video/mjpg.cgi"));
    Q_UNUSED(checked);
    QString ip = ui->leIP->text();
    QString url = ui->leURL->text();
    if ((ip!="") && (url != "")) {
        QUrl target = QUrl(ip + url);
        ui->wev->load(target);
    }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveconfig();
    event->accept();
}

void MainWindow::onIdxChanged(int idx){
    QString cam = ui->cbCams->itemText(idx);
    cfg->beginGroup(cam);
    QString url = cfg->value("url", "").toString();
    cfg->endGroup();
    setStatus("url:" + url);
    if (url != "") {
        ui->leURL->setText(url);
    }

}
void MainWindow::setStatus(QString msg){
    statusBar()->showMessage(msg);
}

void MainWindow::onLoadProgress(int prog){
    progbar->setValue(prog);
}

void MainWindow::onloadFinished(bool ok){
//    progbar->setValue(100);
    qDebug() << "onloadFinished";
    progbar->reset();
    Q_UNUSED(ok);
}
