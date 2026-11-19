#include <QApplication>
#include <QMessageBox>
#include <QWidget>
#include "ui_landingpage.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    Ui::LandingPage ui;
    ui.setupUi(&window); // Memuat desain dari landingpage.ui

    // Menghubungkan tombol (pastikan objectName tombol Anda di Qt Designer bernama btnStartTraining, atau sesuaikan)
    QObject::connect(ui.pushButton, &QPushButton::clicked, [&window]() {
        QMessageBox::information(&window, "Navigasi", "Siap pindah ke Page berikutnya!");
    });

    window.show();
    return app.exec();
}