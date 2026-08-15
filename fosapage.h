#ifndef FOSAPAGE_H
#define FOSAPAGE_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QShowEvent;

class FosaPage : public QWidget
{
    Q_OBJECT

public:
    explicit FosaPage(QWidget *parent = nullptr);

signals:
    void backRequested();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void recalcular();

private:
    QLabel *createResultLabel();
    QLineEdit *createLineEdit(double min, double max, int decimals);

    QLineEdit *m_largo = nullptr;
    QLineEdit *m_ancho = nullptr;
    QLineEdit *m_tiempo = nullptr;
    QLineEdit *m_pe = nullptr;
    QLineEdit *m_pa = nullptr;

    QLabel *m_areaResult = nullptr;
    QLabel *m_gpmResult = nullptr;
    QLabel *m_gaeResult = nullptr;
    QLabel *m_geResult = nullptr;
    QLabel *m_gaResult = nullptr;
    QLabel *m_warning = nullptr;
};

#endif // FOSAPAGE_H
