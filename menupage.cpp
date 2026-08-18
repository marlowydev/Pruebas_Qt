#include "menupage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MenuPage::MenuPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel *title = new QLabel(tr("Calculadora de Cuantificación\nAgua y Espumas"), this);
    title->setObjectName("menuTitle");
    title->setAlignment(Qt::AlignCenter);

    QLabel *subtitle = new QLabel(tr("Seleccione el tipo de cálculo a realizar:"), this);
    subtitle->setObjectName("menuSubtitle");
    subtitle->setAlignment(Qt::AlignCenter);

    m_fosaButton = new QPushButton(tr("Fosas"), this);
    m_fosaButton->setObjectName("menuButton");
    m_fosaButton->setMinimumHeight(140);
    m_fosaButton->setMinimumWidth(220);

    m_tanqueButton = new QPushButton(tr("Tanques"), this);
    m_tanqueButton->setObjectName("menuButton");
    m_tanqueButton->setMinimumHeight(140);
    m_tanqueButton->setMinimumWidth(220);

    m_techoButton = new QPushButton(tr("Tanques\nTecho Flotante"), this);
    m_techoButton->setObjectName("menuButton");
    m_techoButton->setMinimumHeight(140);
    m_techoButton->setMinimumWidth(220);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_fosaButton);
    buttonsLayout->addSpacing(24);
    buttonsLayout->addWidget(m_tanqueButton);
    buttonsLayout->addSpacing(24);
    buttonsLayout->addWidget(m_techoButton);
    buttonsLayout->addStretch();

    m_kilocaloriaButton = new QPushButton(tr("Calcular Kilocalorias"), this);
    m_kilocaloriaButton->setObjectName("menuButtonRed");
    m_kilocaloriaButton->setMinimumHeight(56);
    m_kilocaloriaButton->setMaximumWidth(420);

    QHBoxLayout *kilocaloriaRow = new QHBoxLayout;
    kilocaloriaRow->addStretch();
    kilocaloriaRow->addWidget(m_kilocaloriaButton);
    kilocaloriaRow->addStretch();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(subtitle);
    layout->addSpacing(32);
    layout->addLayout(buttonsLayout);
    layout->addSpacing(24);
    layout->addLayout(kilocaloriaRow);
    layout->addStretch();

    connect(m_fosaButton, &QPushButton::clicked, this, &MenuPage::fosaRequested);
    connect(m_tanqueButton, &QPushButton::clicked, this, &MenuPage::tanqueRequested);
    connect(m_techoButton, &QPushButton::clicked, this, &MenuPage::techoRequested);
    connect(m_kilocaloriaButton, &QPushButton::clicked, this, &MenuPage::kilocaloriaRequested);
}
