 #include "tanquepage.h"

#include <QDoubleValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>
#include <QPushButton>
#include <QRadioButton>
#include <QShowEvent>
#include <QVBoxLayout>

namespace {
const double PI = 3.1416;
const double METROS_A_PIES = 3.3;

QHBoxLayout *makeResultRow(const QString &name, QLabel *value)
{
    QHBoxLayout *row = new QHBoxLayout;
    row->setContentsMargins(0, 0, 0, 0);
    QLabel *nameLabel = new QLabel(name);
    nameLabel->setStyleSheet("font-size: 14px; color: #1b3a5c;");
    row->addWidget(nameLabel);
    row->addStretch();
    row->addWidget(value);
    return row;
}
}

TanquePage::TanquePage(QWidget *parent)
    : QWidget(parent)
{
    QLabel *title = new QLabel(tr("Cuantificación de Agua y Espumas - Tanques"), this);
    title->setObjectName("pageTitle");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *backButton = new QPushButton(tr("< Volver al menu"), this);
    backButton->setObjectName("backButton");
    connect(backButton, &QPushButton::clicked, this, &TanquePage::backRequested);

    QGridLayout *headerLayout = new QGridLayout;
    headerLayout->setColumnStretch(1, 1);
    headerLayout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    headerLayout->addWidget(title, 0, 1, Qt::AlignCenter);
    QWidget *rightSpacer = new QWidget(this);
    rightSpacer->setMinimumWidth(backButton->sizeHint().width());
    headerLayout->addWidget(rightSpacer, 0, 2);

    QGroupBox *dataGroup = new QGroupBox(tr("Datos de entrada"), this);

    m_diametro = createLineEdit(0.0, 1000000.0, 2);
    m_diametro->setPlaceholderText(tr("Diámetro"));
    m_diametro->setToolTip(tr("Diámetro del tanque, en la unidad seleccionada"));

    m_metrosRadio = new QRadioButton(tr("Metros"), this);
    m_metrosRadio->setChecked(true);
    m_metrosRadio->setToolTip(tr("Metros"));

    m_piesRadio = new QRadioButton(tr("Pies"), this);
    m_piesRadio->setToolTip(tr("Pies"));

    QHBoxLayout *unidadLayout = new QHBoxLayout;
    unidadLayout->addWidget(m_metrosRadio);
    unidadLayout->addWidget(m_piesRadio);
    unidadLayout->addStretch();

    m_ia = createLineEdit(0.0, 1000.0, 3);
    m_ia->setPlaceholderText(tr("IA"));
    m_ia->setToolTip(tr("Índice de aplicación (IA) del tanque"));

    m_tiempo = createLineEdit(0.0, 1000000.0, 1);
    m_tiempo->setPlaceholderText(tr("Tiempo"));
    m_tiempo->setToolTip(tr("Tiempo de aplicación en minutos"));

    m_pe = createLineEdit(0.0, 100.0, 2);
    m_pe->setPlaceholderText(tr("PE"));
    m_pe->setToolTip(tr("Porcentaje de espuma (ej. 3 = 3%)"));

    m_pa = createLineEdit(0.0, 100.0, 2);
    m_pa->setPlaceholderText(tr("PA"));
    m_pa->setToolTip(tr("Porcentaje de agua (ej. 97 = 97%)"));

    QFormLayout *formLayout = new QFormLayout(dataGroup);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->addRow(tr("Diámetro (m o pies):"), m_diametro);
    formLayout->addRow(tr("Unidad del diámetro:"), unidadLayout);
    formLayout->addRow(tr("Índice IA:"), m_ia);
    formLayout->addRow(tr("Tiempo (min):"), m_tiempo);
    formLayout->addRow(tr("Espuma PE (%):"), m_pe);
    formLayout->addRow(tr("Agua PA (%):"), m_pa);

    QLabel *hint = new QLabel(tr("Complete cada campo: diámetro en la unidad elegida, tiempo en minutos, y PE / PA en porcentaje (ej. 3 = 3%)."), dataGroup);
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #4a6178; font-size: 12px;");
    formLayout->addRow(hint);

    QGroupBox *resultGroup = new QGroupBox(tr("Resultados"), this);
    m_diametroPiesResult = createResultLabel();
    m_areaResult = createResultLabel();
    m_gpmResult = createResultLabel();
    m_gaeResult = createResultLabel();
    m_geResult = createResultLabel();
    m_gaResult = createResultLabel();

    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    resultLayout->setContentsMargins(12, 16, 12, 12);
    resultLayout->setSpacing(8);
    resultLayout->addLayout(makeResultRow(tr("Diámetro en pies:"), m_diametroPiesResult));
    resultLayout->addLayout(makeResultRow(tr("Área (pies²):"), m_areaResult));
    resultLayout->addLayout(makeResultRow(tr("Total GPM:"), m_gpmResult));
    resultLayout->addLayout(makeResultRow(tr("GA/E (Galones de Agente Espumante):"), m_gaeResult));
    resultLayout->addLayout(makeResultRow(tr("GE (Galones de Espuma):"), m_geResult));
    resultLayout->addLayout(makeResultRow(tr("GA (Galones de Agua):"), m_gaResult));

    m_warning = new QLabel(resultGroup);
    m_warning->setWordWrap(true);
    m_warning->setStyleSheet("color: #b45309; font-size: 12px; font-weight: bold;");
    resultLayout->addWidget(m_warning);

    QLabel *note = new QLabel(tr("GA/E = galones de agente espumante · GE = galones de espuma · GA = galones de agua"), this);
    note->setWordWrap(true);
    note->setStyleSheet("color: #4a6178; font-size: 12px;");

    QHBoxLayout *bodyLayout = new QHBoxLayout;
    bodyLayout->addWidget(dataGroup, 1);
    bodyLayout->addSpacing(16);
    bodyLayout->addWidget(resultGroup, 1);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(24, 16, 24, 24);
    layout->addLayout(headerLayout);
    layout->addSpacing(16);
    layout->addLayout(bodyLayout);
    layout->addWidget(note);

    connect(m_diametro, &QLineEdit::textChanged, this, &TanquePage::recalcular);
    connect(m_metrosRadio, &QRadioButton::toggled, this, &TanquePage::recalcular);
    connect(m_piesRadio, &QRadioButton::toggled, this, &TanquePage::recalcular);
    connect(m_ia, &QLineEdit::textChanged, this, &TanquePage::recalcular);
    connect(m_tiempo, &QLineEdit::textChanged, this, &TanquePage::recalcular);
    connect(m_pe, &QLineEdit::textChanged, this, &TanquePage::recalcular);
    connect(m_pa, &QLineEdit::textChanged, this, &TanquePage::recalcular);

    recalcular();
}

QLineEdit *TanquePage::createLineEdit(double min, double max, int decimals)
{
    QLineEdit *edit = new QLineEdit(this);
    edit->setAlignment(Qt::AlignRight);
    edit->setMinimumWidth(140);
    QDoubleValidator *validator = new QDoubleValidator(min, max, decimals, edit);
    validator->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    validator->setNotation(QDoubleValidator::StandardNotation);
    edit->setValidator(validator);
    return edit;
}

void TanquePage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    m_diametro->setFocus();
}

QLabel *TanquePage::createResultLabel()
{
    QLabel *label = new QLabel(this);
    label->setObjectName("resultValue");
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    return label;
}

void TanquePage::recalcular()
{
    const double diametro = m_diametro->text().toDouble();
    const double ia = m_ia->text().toDouble();
    const double tiempo = m_tiempo->text().toDouble();
    const double pe = m_pe->text().toDouble();
    const double pa = m_pa->text().toDouble();

    double dPies = diametro;
    if (m_metrosRadio->isChecked()) {
        dPies = dPies * METROS_A_PIES;
    }

    const double radio = dPies / 2.0;
    const double area = radio * radio * PI;
    const double gpm = area * ia;
    const double gae = gpm * tiempo;
    const double ge = gae * (pe / 100.0);
    const double ga = gae * (pa / 100.0);

    m_diametroPiesResult->setText(QString::number(dPies, 'f', 2) + tr(" pies"));
    m_areaResult->setText(QString::number(area, 'f', 2));
    m_gpmResult->setText(QString::number(gpm, 'f', 2));
    m_gaeResult->setText(QString::number(gae, 'f', 2));
    m_geResult->setText(QString::number(ge, 'f', 2));
    m_gaResult->setText(QString::number(ga, 'f', 2));

    const double sumaPorcentajes = pe + pa;
    if ((pe > 0.0 || pa > 0.0) && qAbs(sumaPorcentajes - 100.0) > 0.01) {
        m_warning->setText(tr("Atención: PE + PA = ") + QString::number(sumaPorcentajes, 'f', 1)
                           + tr("%. La suma debe ser 100% para que G/E + G/A = GA/E."));
    } else {
        m_warning->clear();
    }
}
