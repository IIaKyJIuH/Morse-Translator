#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QChar>
#include <QHash>
#include <QObject>
#include <QString>

class MTTranslator : public QObject
{
    Q_OBJECT

public:
    explicit MTTranslator(QObject *parent = nullptr);

    QString encodeToMorse(const QString &words);
    QString decodeFromMorse(const QString &codes);
    bool isMorseCode(const QString &input);

private:
    QHash<QChar, QString> m_charToMorseMap;
    QHash<QString, QChar> m_morseToCharMap;
    void initHashTables();
};

#endif // TRANSLATOR_H
