#include "kilocaloriapage.h"

#include <QButtonGroup>
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
const double GALONES_A_LITROS = 3.785;
const double FACTOR_A = 4444.0;
const double FACTOR_B = 8888.0;

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

KilocaloriaPage::KilocaloriaPage(QWidget *parent)
    : QWidget(parent)
{
    QLabel *title = new QLabel(tr("Calculadora de Kilocalorías"), this);
    title->setObjectName("pageTitle");
    title->setAlignment(Qt::AlignCenter);

    QPushButton *backButton = new QPushButton(tr("< Volver al menu"), this);
    backButton->setObjectName("backButton");
    connect(backButton, &QPushButton::clicked, this, &KilocaloriaPage::backRequested);

    QGridLayout *headerLayout = new QGridLayout;
    headerLayout->setColumnStretch(1, 1);
    headerLayout->addWidget(backButton, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
    headerLayout->addWidget(title, 0, 1, Qt::AlignCenter);
    QWidget *rightSpacer = new QWidget(this);
    rightSpacer->setMinimumWidth(backButton->sizeHint().width());
    headerLayout->addWidget(rightSpacer, 0, 2);

    QGroupBox *dataGroup = new QGroupBox(tr("Datos de entrada"), this);

    m_cantidad = createLineEdit(0.0, 1000000.0, 2);
    m_cantidad->setPlaceholderText(tr("Cantidad"));
    m_cantidad->setToolTip(tr("Cantidad del producto (litros o galones)"));

    m_litrosRadio = new QRadioButton(tr("Litros"), this);
    m_litrosRadio->setChecked(true);
    m_litrosRadio->setToolTip(tr("El producto ya está en litros"));

    m_galonesRadio = new QRadioButton(tr("Galones"), this);
    m_galonesRadio->setToolTip(tr("Se convertirá a litros (×3.785)"));

    QButtonGroup *unidadGroup = new QButtonGroup(this);
    unidadGroup->addButton(m_litrosRadio);
    unidadGroup->addButton(m_galonesRadio);

    QHBoxLayout *unidadCantLayout = new QHBoxLayout;
    unidadCantLayout->addWidget(m_litrosRadio);
    unidadCantLayout->addWidget(m_galonesRadio);
    unidadCantLayout->addStretch();

    m_densidad = createLineEdit(0.0, 10000.0, 3);
    m_densidad->setPlaceholderText(tr("Densidad"));
    m_densidad->setToolTip(tr("Densidad del producto"));

    m_largo = createLineEdit(0.0, 1000000.0, 2);
    m_largo->setPlaceholderText(tr("Largo"));
    m_largo->setToolTip(tr("Largo del área en metros"));

    m_ancho = createLineEdit(0.0, 1000000.0, 2);
    m_ancho->setPlaceholderText(tr("Ancho"));
    m_ancho->setToolTip(tr("Ancho del área en metros"));

    m_fuegoARadio = new QRadioButton(tr("Tipo A"), this);
    m_fuegoARadio->setChecked(true);
    m_fuegoARadio->setToolTip(tr("Fuego tipo A — factor 4444"));

    m_fuegoBRadio = new QRadioButton(tr("Tipo B"), this);
    m_fuegoBRadio->setToolTip(tr("Fuego tipo B — factor 8888"));

    QButtonGroup *fuegoGroup = new QButtonGroup(this);
    fuegoGroup->addButton(m_fuegoARadio);
    fuegoGroup->addButton(m_fuegoBRadio);

    QHBoxLayout *tipoFuegoLayout = new QHBoxLayout;
    tipoFuegoLayout->addWidget(m_fuegoARadio);
    tipoFuegoLayout->addWidget(m_fuegoBRadio);
    tipoFuegoLayout->addStretch();

    QFormLayout *formLayout = new QFormLayout(dataGroup);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    formLayout->addRow(tr("Cantidad:"), m_cantidad);
    formLayout->addRow(tr("Unidad:"), unidadCantLayout);
    formLayout->addRow(tr("Densidad:"), m_densidad);
    formLayout->addRow(tr("Largo (m):"), m_largo);
    formLayout->addRow(tr("Ancho (m):"), m_ancho);
    formLayout->addRow(tr("Tipo de fuego:"), tipoFuegoLayout);

    QLabel *hint = new QLabel(tr("Si la cantidad está en galones se convertirá a litros (×3.785). El área es largo × ancho en metros."), dataGroup);
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #4a6178; font-size: 12px;");
    formLayout->addRow(hint);

    QGroupBox *resultGroup = new QGroupBox(tr("Resultados"), this);
    m_litrosResult = createResultLabel();
    m_areaResult = createResultLabel();
    m_factorResult = createResultLabel();
    m_resultadoResult = createResultLabel();

    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);
    resultLayout->setContentsMargins(12, 16, 12, 12);
    resultLayout->setSpacing(8);
    resultLayout->addLayout(makeResultRow(tr("Litros totales:"), m_litrosResult));
    resultLayout->addLayout(makeResultRow(tr("Área (m²):"), m_areaResult));
    resultLayout->addLayout(makeResultRow(tr("Factor tipo fuego:"), m_factorResult));
    resultLayout->addLayout(makeResultRow(tr("Resultado (kcal/m²):"), m_resultadoResult));

    QLabel *note = new QLabel(tr("Resultado = (litros × densidad × factor) ÷ área"), this);
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

    connect(m_cantidad, &QLineEdit::textChanged, this, &KilocaloriaPage::recalcular);
    connect(m_litrosRadio, &QRadioButton::toggled, this, &KilocaloriaPage::recalcular);
    connect(m_galonesRadio, &QRadioButton::toggled, this, &KilocaloriaPage::recalcular);
    connect(m_densidad, &QLineEdit::textChanged, this, &KilocaloriaPage::recalcular);
    connect(m_largo, &QLineEdit::textChanged, this, &KilocaloriaPage::recalcular);
    connect(m_ancho, &QLineEdit::textChanged, this, &KilocaloriaPage::recalcular);
    connect(m_fuegoARadio, &QRadioButton::toggled, this, &KilocaloriaPage::recalcular);
    connect(m_fuegoBRadio, &QRadioButton::toggled, this, &KilocaloriaPage::recalcular);

    recalcular();
}

QLineEdit *KilocaloriaPage::createLineEdit(double min, double max, int decimals)
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

void KilocaloriaPage::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    m_cantidad->setFocus();
}

QLabel *KilocaloriaPage::createResultLabel()
{
    QLabel *label = new QLabel(this);
    label->setObjectName("resultValue");
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    return label;
}

void KilocaloriaPage::recalcular()
{
    const double cantidad = m_cantidad->text().toDouble();
    const double densidad = m_densidad->text().toDouble();
    const double largo = m_largo->text().toDouble();
    const double ancho = m_ancho->text().toDouble();

    double litros = cantidad;
    if (m_galonesRadio->isChecked()) {
        litros = litros * GALONES_A_LITROS;
    }

    const double area = largo * ancho;
    const double factor = m_fuegoARadio->isChecked() ? FACTOR_A : FACTOR_B;
    const double producto = litros * densidad * factor;
    const double resultado = (area > 0.0) ? (producto / area) : 0.0;

    m_litrosResult->setText(QString::number(litros, 'f', 2));
    m_areaResult->setText(QString::number(area, 'f', 2));
    m_factorResult->setText(QString::number(factor, 'f', 0));
    m_resultadoResult->setText(QString::number(resultado, 'f', 2));
}
