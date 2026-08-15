#ifndef TANQUEPAGE_H
#define TANQUEPAGE_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QShowEvent;

class TanquePage : public QWidget
{
    Q_OBJECT

public:
    explicit TanquePage(QWidget *parent = nullptr);

signals:
    void backRequested();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void recalcular();

private:
    QLabel *createResultLabel();
    QLineEdit *createLineEdit(double min, double max, int decimals);

    QLineEdit *m_diametro = nullptr;
    QRadioButton *m_metrosRadio = nullptr;
    QRadioButton *m_piesRadio = nullptr;
    QLineEdit *m_ia = nullptr;
    QLineEdit *m_tiempo = nullptr;
    QLineEdit *m_pe = nullptr;
    QLineEdit *m_pa = nullptr;

    QLabel *m_diametroPiesResult = nullptr;
    QLabel *m_areaResult = nullptr;
    QLabel *m_gpmResult = nullptr;
    QLabel *m_gaeResult = nullptr;
    QLabel *m_geResult = nullptr;
    QLabel *m_gaResult = nullptr;
    QLabel *m_warning = nullptr;
};

#endif // TANQUEPAGE_H
