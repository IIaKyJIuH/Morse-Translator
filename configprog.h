#ifndef CONFIGPROG_H
#define CONFIGPROG_H

#include <QObject>
#include <QSettings>

class MTProgramConfig : public QObject
{
    Q_OBJECT
public:
    explicit MTProgramConfig(QObject *parent = nullptr);
    ~MTProgramConfig();

    QByteArray getGeometry();
    void setGeometry(const QByteArray &data);
    void saveGeometry();

private:
    QSettings m_settings;
    QByteArray m_windowGeometry; // здесь всё про размеры окна: ширина|высота|x|y

    void loadGeometry();
};

extern MTProgramConfig g_programConfig;

#endif // CONFIGPROG_H
