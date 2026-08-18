#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>

class QPushButton;

class MenuPage : public QWidget
{
    Q_OBJECT

public:
    explicit MenuPage(QWidget *parent = nullptr);

signals:
    void fosaRequested();
    void tanqueRequested();
    void techoRequested();
    void kilocaloriaRequested();

private:
    QPushButton *m_fosaButton = nullptr;
    QPushButton *m_tanqueButton = nullptr;
    QPushButton *m_techoButton = nullptr;
    QPushButton *m_kilocaloriaButton = nullptr;
};

#endif // MENUPAGE_H
