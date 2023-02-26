/*
 * Created By: Adam Nguyen
 * Created On: August 21st, 2021
 * Snowbots UI
 */

#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

// QT
#include "QDebug"
#include "QDir"
#include "QLabel"
#include "QMessageBox"
#include "QPixmap"
#include "QProcess"

MainWindow::MainWindow(QWidget* parent)
  :

    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("Snowbots Interface");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(twist_values()));
    ;
    timer->start(500);

    // ROS
    ros_f = new RosIntegration();
    qDebug() << "Constructor OK";

    // UI

    // Snowbots Logo
    QPixmap pixmap("./src/snowbots_ui/resources/snowbot2.png");
    ui->label_5->setPixmap(pixmap);
    ui->label_5->show();
    ui->label_5->setScaledContents(true);
    qDebug() << "Current dir:" << QDir::currentPath();
}
MainWindow::~MainWindow() {
    delete ui;
    qDebug() << "Destructor OK";
}

void MainWindow::twist_values() {
    ui->mode_lcd->setText("Hello World"); // replace hellow world with message for mode
    ui->nuc_temp_lcd->display(twist_message_right.linear.x); // message req for updating nuc temp
    ui->rover_temp_lcd->display(twist_message_controller.angular.z); // message req for updating rover temp
    ui->elec_box_temp_lcd->display(twist_message_controller.linear.x); // message req for updating elec box temp
    ros_f->twist_subscriber(); // message req for updating elec box temp
}
// TODOS: 
// Current Mode - status - done
// end effector position feedback (hopefully)
// end effector force feedback as % of grip
// nuc temperature
// rover ambient temp
// elec box temp
// stored arm poses (button)