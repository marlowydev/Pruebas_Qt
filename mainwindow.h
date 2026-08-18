#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class FosaPage;
class KilocaloriaPage;
class MenuPage;
class QStackedWidget;
class TanquePage;
class TechoPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void mostrarFosa();
    void mostrarTanque();
    void mostrarTecho();
    void mostrarKilocaloria();
    void mostrarMenu();

private:
    QStackedWidget *m_stack = nullptr;
    MenuPage *m_menu = nullptr;
    FosaPage *m_fosa = nullptr;
    TanquePage *m_tanque = nullptr;
    TechoPage *m_techo = nullptr;
    KilocaloriaPage *m_kilocaloria = nullptr;
};

#endif // MAINWINDOW_H
