#include "mainwindow.h"

#include "fosapage.h"
#include "menupage.h"
#include "tanquepage.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Calculadora de Agua y Espumas"));
    resize(960, 620);
    setMinimumSize(720, 520);

    m_menu = new MenuPage(this);
    m_fosa = new FosaPage(this);
    m_tanque = new TanquePage(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(m_menu);
    m_stack->addWidget(m_fosa);
    m_stack->addWidget(m_tanque);

    setCentralWidget(m_stack);

    connect(m_menu, &MenuPage::fosaRequested, this, &MainWindow::mostrarFosa);
    connect(m_menu, &MenuPage::tanqueRequested, this, &MainWindow::mostrarTanque);
    connect(m_fosa, &FosaPage::backRequested, this, &MainWindow::mostrarMenu);
    connect(m_tanque, &TanquePage::backRequested, this, &MainWindow::mostrarMenu);
}

void MainWindow::mostrarFosa()
{
    m_stack->setCurrentWidget(m_fosa);
}

void MainWindow::mostrarTanque()
{
    m_stack->setCurrentWidget(m_tanque);
}

void MainWindow::mostrarMenu()
{
    m_stack->setCurrentWidget(m_menu);
}
