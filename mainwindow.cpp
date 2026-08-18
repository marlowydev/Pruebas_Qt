#include "mainwindow.h"

#include "fosapage.h"
#include "kilocaloriapage.h"
#include "menupage.h"
#include "tanquepage.h"
#include "techopage.h"

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
    m_techo = new TechoPage(this);
    m_kilocaloria = new KilocaloriaPage(this);

    m_stack = new QStackedWidget(this);
    m_stack->addWidget(m_menu);
    m_stack->addWidget(m_fosa);
    m_stack->addWidget(m_tanque);
    m_stack->addWidget(m_techo);
    m_stack->addWidget(m_kilocaloria);

    setCentralWidget(m_stack);

    connect(m_menu, &MenuPage::fosaRequested, this, &MainWindow::mostrarFosa);
    connect(m_menu, &MenuPage::tanqueRequested, this, &MainWindow::mostrarTanque);
    connect(m_menu, &MenuPage::techoRequested, this, &MainWindow::mostrarTecho);
    connect(m_menu, &MenuPage::kilocaloriaRequested, this, &MainWindow::mostrarKilocaloria);
    connect(m_fosa, &FosaPage::backRequested, this, &MainWindow::mostrarMenu);
    connect(m_tanque, &TanquePage::backRequested, this, &MainWindow::mostrarMenu);
    connect(m_techo, &TechoPage::backRequested, this, &MainWindow::mostrarMenu);
    connect(m_kilocaloria, &KilocaloriaPage::backRequested, this, &MainWindow::mostrarMenu);
}

void MainWindow::mostrarFosa()
{
    m_stack->setCurrentWidget(m_fosa);
}

void MainWindow::mostrarTanque()
{
    m_stack->setCurrentWidget(m_tanque);
}

void MainWindow::mostrarTecho()
{
    m_stack->setCurrentWidget(m_techo);
}

void MainWindow::mostrarKilocaloria()
{
    m_stack->setCurrentWidget(m_kilocaloria);
}

void MainWindow::mostrarMenu()
{
    m_stack->setCurrentWidget(m_menu);
}
