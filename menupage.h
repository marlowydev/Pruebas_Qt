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

private:
    QPushButton *m_fosaButton = nullptr;
    QPushButton *m_tanqueButton = nullptr;
};

#endif // MENUPAGE_H
