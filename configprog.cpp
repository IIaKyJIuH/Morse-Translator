#include "configprog.h"
#include <QSettings>
#include <QStandardPaths>

#define STANDARDPATH \
    QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/settings.ini"

MTProgramConfig g_programConfig;

MTProgramConfig::MTProgramConfig(QObject *parent)
    : QObject(parent)
{
    loadGeometry();
}

MTProgramConfig::~MTProgramConfig()
{
    saveGeometry();
}

QByteArray MTProgramConfig::getGeometry()
{
    return m_windowGeometry;
}

void MTProgramConfig::setGeometry(const QByteArray &data)
{
    m_windowGeometry = data;
}

void MTProgramConfig::saveGeometry()
{
    m_settings.beginGroup("WINDOW_SETTINGS");
    m_settings.setValue("total", m_windowGeometry);
    m_settings.endGroup();
}

void MTProgramConfig::loadGeometry()
{
    QSettings m_settings(STANDARDPATH, QSettings::IniFormat);
    m_settings.beginGroup("WINDOW_SETTINGS");
    m_windowGeometry = m_settings.value("total").toByteArray();
    m_settings.endGroup();
}
