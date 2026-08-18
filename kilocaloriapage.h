#ifndef KILOCALORIAPAGE_H
#define KILOCALORIAPAGE_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QShowEvent;

class KilocaloriaPage : public QWidget
{
    Q_OBJECT

public:
    explicit KilocaloriaPage(QWidget *parent = nullptr);

signals:
    void backRequested();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void recalcular();

private:
    QLabel *createResultLabel();
    QLineEdit *createLineEdit(double min, double max, int decimals);

    QLineEdit *m_cantidad = nullptr;
    QRadioButton *m_litrosRadio = nullptr;
    QRadioButton *m_galonesRadio = nullptr;
    QLineEdit *m_densidad = nullptr;
    QLineEdit *m_largo = nullptr;
    QLineEdit *m_ancho = nullptr;
    QRadioButton *m_fuegoARadio = nullptr;
    QRadioButton *m_fuegoBRadio = nullptr;

    QLabel *m_litrosResult = nullptr;
    QLabel *m_areaResult = nullptr;
    QLabel *m_factorResult = nullptr;
    QLabel *m_resultadoResult = nullptr;
};

#endif // KILOCALORIAPAGE_H
