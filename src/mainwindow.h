#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QCloseEvent>
#include <QProgressBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void onConnect(bool checked);
    void onIdxChanged(int idx);
    void onLoadProgress(int prog);
    void onloadFinished(bool ok);
private:
    Ui::MainWindow *ui;
    QProgressBar *progbar;
    QSettings *cfg;
    QStringList camlist;
    void readconfig();
    void saveconfig();
    void setStatus(QString msg);
};
#endif // MAINWINDOW_H
