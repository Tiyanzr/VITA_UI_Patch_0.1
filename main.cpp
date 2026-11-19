#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include "ui_Landingpage.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    Ui::LandingPage ui;
    ui.setupUi(&window);
    ui.stackedWidget->setCurrentIndex(0);   // mulai dari landing page

    // Landing -> Student Info
    QObject::connect(ui.StartTraining, &QPushButton::clicked, [&ui]() {
        ui.stackedWidget->setCurrentIndex(1);
    });

    // Student Info
    QObject::connect(ui.Back1, &QPushButton::clicked, [&ui]() {
        ui.stackedWidget->setCurrentIndex(0);
    });
    QObject::connect(ui.Next1, &QPushButton::clicked, [&ui]() {
        ui.stackedWidget->setCurrentIndex(2);
    });

    // Scenario
    QObject::connect(ui.back2, &QPushButton::clicked, [&ui]() {
        ui.stackedWidget->setCurrentIndex(1);
    });
    QObject::connect(ui.Start, &QPushButton::clicked, [&ui, &window]() {
        int minutes = 0;
        if (ui.btn05menit->isChecked()) minutes = 5;
        else if (ui.btn10menit->isChecked()) minutes = 10;
        else if (ui.btn15menit->isChecked()) minutes = 15;
        else if (ui.btn20menit->isChecked()) minutes = 20;

        QString scenario;
        for (QRadioButton *r : {ui.radioButton_1, ui.radioButton_2,
                                ui.radioButton_3, ui.radioButton_4, ui.radioButton_5}) {
            if (r->isChecked()) scenario = r->text();
        }

        if (minutes == 0 || scenario.isEmpty()) {
            QMessageBox::warning(&window, "Setup", "Pilih durasi dan scenario dulu.");
            return;
        }
        QMessageBox::information(&window, "Setup",
            QString("Durasi: %1 menit\nScenario: %2").arg(minutes).arg(scenario));
    });

    // Exit
    QObject::connect(ui.Exit1, &QPushButton::clicked, &window, &QWidget::close);
    QObject::connect(ui.Exit2, &QPushButton::clicked, &window, &QWidget::close);

    window.show();
    return app.exec();
}