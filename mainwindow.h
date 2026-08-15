#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FosaPage;
class MenuPage;
class QStackedWidget;
class TanquePage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void mostrarFosa();
    void mostrarTanque();
    void mostrarMenu();

private:
    QStackedWidget *m_stack = nullptr;
    MenuPage *m_menu = nullptr;
    FosaPage *m_fosa = nullptr;
    TanquePage *m_tanque = nullptr;
};

#endif // MAINWINDOW_H
