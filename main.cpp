#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle(QStyleFactory::create("Fusion"));

    app.setStyleSheet(R"(
        QMainWindow {
            background-color: #f2f5f9;
        }
        QLabel#pageTitle, QLabel#menuTitle {
            font-size: 24px;
            font-weight: bold;
            color: #1b3a5c;
        }
        QLabel#menuSubtitle {
            font-size: 14px;
            color: #4a6178;
        }
        QPushButton#menuButton {
            font-size: 20px;
            font-weight: bold;
            color: white;
            background-color: #1b6ca8;
            border-radius: 12px;
            padding: 20px;
        }
        QPushButton#menuButton:hover {
            background-color: #2188c8;
        }
        QPushButton#menuButton:pressed {
            background-color: #15547f;
        }
        QPushButton#backButton {
            font-size: 13px;
            color: #1b6ca8;
            border: 1px solid #1b6ca8;
            border-radius: 8px;
            padding: 6px 14px;
            background-color: white;
        }
        QPushButton#backButton:hover {
            background-color: #e3f0fa;
        }
        QPushButton#calcularButton {
            font-size: 16px;
            font-weight: bold;
            color: white;
            background-color: #2e9e5b;
            border-radius: 8px;
            padding: 10px;
        }
        QPushButton#calcularButton:hover {
            background-color: #37b56b;
        }
        QLabel#sectionTitle {
            font-size: 15px;
            font-weight: bold;
            color: #1b3a5c;
        }
        QLabel#resultValue {
            font-size: 15px;
            font-weight: bold;
            color: #0d7a3d;
        }
        QGroupBox {
            font-weight: bold;
            color: #1b3a5c;
            border: 1px solid #c9d6e3;
            border-radius: 8px;
            margin-top: 12px;
            padding-top: 12px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 6px;
        }
        QLineEdit, QComboBox, QRadioButton {
            font-size: 14px;
        }

        QRadioButton {
            spacing: 6px;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border: 2px solid #1b6ca8;
            border-radius: 9px;
            background: #ffffff;
        }
        QRadioButton::indicator:hover {
            border-color: #15547f;
            background: #e3f0fa;
        }
        QRadioButton::indicator:checked {
            background: #1b6ca8;
        }
        QRadioButton::indicator:disabled {
            border-color: #c9d6e3;
            background: #f2f5f9;
        }
    )");

    MainWindow window;
    window.show();

    return app.exec();
}
