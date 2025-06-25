#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QSound>
#include <unistd.h>
#include <thread.h>
#include <algorithm>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);


    thread = new Thread();

    connect(thread, SIGNAL(showtim(int)), this, SLOT(showTim()));

//    QTime qtim = QTime::currentTime();
//    printf("%lld\n", qtim.msec());

}



LL MainWindow::getTim() {
    return QDateTime::currentMSecsSinceEpoch();
}



QString MainWindow::toStr(LL n) {
    return QString().sprintf("%02lld : %02lld : %02lld . %02lld", n / 3600000, n % 3600000 / 60000, n % 60000 / 1000, n % 1000 / 10);
}

void MainWindow::timeOut() {

    ui->tim->setText("00 : 00 : 00 . 00");
    ui->ss->setText("Start");
    QSound::play("./CountDownAudio.wav");
    return ;
}

void MainWindow::showTim()
{
    if (!flag)
        return ;

    LL tmp = t - getTim() + lstTime;

    if (tmp <= 0) {
        stop();
        timeOut();
        return ;
    }

    ui->tim->setText(toStr(tmp));

    return ;
}

std::pair<LL, LL> MainWindow::find(LL w, std::string s) {
    LL res = 0;
    unsigned long long i;
    for (i = w; i < s.size(); ++i)
        if ('0' <= s[i] && s[i] <= '9')
            break;
    for (; i < s.size(); ++i) {
        if ('0' > s[i] || s[i] > '9')
            break;
        res = res * 10 + s[i] - '0';
    }
    return std::make_pair(res, i);
}

LL MainWindow::getT() {
    std::string str = ui->input->text().toStdString();
    std::pair<LL, LL> h, m, s, ms;
    h = find(0, str);
    m = find(h.second, str);
    s = find(m.second, str);
    ms = find(s.second, str);
    return h.first * 3600000 + m.first * 60000 + s.first * 1000 + ms.first * 10;
}

void MainWindow::start() {
    lstTime = getTim();
    if (t > 0) {
        flag = true;
        thread->start();
    }
    return ;
}

void MainWindow::stop() {
    t -= getTim() - lstTime;
    flag = false;
    thread->stop();
}

void MainWindow::clean() {
    if (ui->ss->text() == "Stop")
        stop();

    lstTime = t = 0;

    ui->ss->setText("Start");

    ui->input->setText("");

    ui->tim->setText("00 : 00 : 00 . 00");

    return ;
}


void MainWindow::on_ss_clicked()
{
    if (ui->ss->text() == "Start") {
        t = getT();
        if (t <= 0)
            return ;
        ui->input->setText(toStr(t));
        ui->tim->setText(toStr(t));
        ui->ss->setText("Continue");
    }
    if (ui->ss->text() == "Continue") {
        start();
        ui->ss->setText("Stop");
    } else {
        stop();
        ui->ss->setText("Continue");
    }
    return ;
}



void MainWindow::on_cl_clicked()
{
    clean();
    return ;
}



MainWindow::~MainWindow()
{
    delete ui;
}
