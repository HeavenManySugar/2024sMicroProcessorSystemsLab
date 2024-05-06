#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "light.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->checkBox->checkState() == Qt::CheckState::Checked) {
        ui->label->setPixmap(QPixmap("../light-bulb_on.png"));
        light::lightOn(0);
    } else {
        ui->label->setPixmap(QPixmap("../light-bulb.png"));
        light::lightOff(0);
    }
    if(ui->checkBox_2->checkState() == Qt::CheckState::Checked) {
        ui->label_2->setPixmap(QPixmap("../light-bulb_on.png"));
        light::lightOn(1);
    } else {
        ui->label_2->setPixmap(QPixmap("../light-bulb.png"));
        light::lightOff(1);
    }
    if(ui->checkBox_3->checkState() == Qt::CheckState::Checked) {
        ui->label_3->setPixmap(QPixmap("../light-bulb_on.png"));
        light::lightOn(2);
    } else {
        ui->label_3->setPixmap(QPixmap("../light-bulb.png"));
        light::lightOff(2);
    }
    if(ui->checkBox_4->checkState() == Qt::CheckState::Checked) {
        ui->label_4->setPixmap(QPixmap("../light-bulb_on.png"));
        light::lightOn(3);
    } else {
        ui->label_4->setPixmap(QPixmap("../light-bulb.png"));
        light::lightOff(3);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    timer = new QTimer(this);
    cnt = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(on_TimeOut()));
    timer->start(500);
    ui->pushButton->click();
}


void MainWindow::on_TimeOut() {
    if(cnt>(ui->lineEdit->text().toInt()*2-1)) {
        timer->stop();
        ui->checkBox->setChecked(false);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
        cnt = 0;
    } else {
        if(cnt&1) {
            ui->checkBox->setChecked(true);
            ui->checkBox_2->setChecked(true);
            ui->checkBox_3->setChecked(false);
            ui->checkBox_4->setChecked(false);
        } else {
            ui->checkBox->setChecked(false);
            ui->checkBox_2->setChecked(false);
            ui->checkBox_3->setChecked(true);
            ui->checkBox_4->setChecked(true);
        }
        cnt++;
    }
    ui->pushButton->click();
    return;
}
