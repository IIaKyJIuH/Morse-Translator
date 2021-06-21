#include "translator.h"
#include <QDebug>
#include <QString>

MTTranslator::MTTranslator(QObject *parent)
    : QObject(parent)
{
    initHashTables();
}

QString MTTranslator::encodeToMorse(const QString &words)
{
    QString encodedString; // строка со словами азбуки Морзе
    encodedString.reserve(words.size()); // реаллокации всё равно будут, но хоть что-то
    for (const QString &word : words.split(' ')) {
        for (const QChar &chr : word)
            if (m_charToMorseMap.contains(chr))
                encodedString.append(m_charToMorseMap[chr] + ' '); // делим буквы в слове

        if (!encodedString.isEmpty())
            encodedString.append(" "); // уже для разделения слов
    }

    if (!encodedString.isEmpty())
        encodedString.chop(2);
    return encodedString;
}

QString MTTranslator::decodeFromMorse(const QString &codes)
{
    QString decodedString; // строка со словами
    decodedString.reserve(codes.count(' ') + 1);
    for (const QString &encodedWord : codes.split("  ")) {
        for (const QString &code : encodedWord.split(" "))
            if (m_morseToCharMap.contains(code))
                decodedString.append(m_morseToCharMap[code]);
        decodedString.append(" "); // разделяем так слова
    }

    decodedString.chop(1); // убираем последний лишний пробел
    return decodedString;
}

void MTTranslator::initHashTables()
{
    m_charToMorseMap = {{'a', ".-"},    {'b', "-..."},   {'c', "-.-."}, {'d', "-.."},
                        {'e', "."},     {'f', "..-."},   {'g', "--."},  {'h', "...."},
                        {'i', ".."},    {'j', ".---"},   {'k', "-.-"},  {'l', ".-.."},
                        {'m', "--"},    {'n', "-."},     {'o', "---"},  {'p', ".--."},
                        {'q', "--.-"},  {'r', ".-."},    {'s', "..."},  {'t', "-"},
                        {'u', "..-"},   {'v', "...-"},   {'w', ".--"},  {'x', "-..-"},
                        {'y', "-.--"},  {'z', "--.."},

                        {',', "..-.."}, {'.', ".-.-.-"}, {';', "-.-.-"}};

    for (const QChar &letter : m_charToMorseMap.keys()) // обратная таблица
        m_morseToCharMap[m_charToMorseMap[letter]] = letter;

    for (const QChar &letter : m_charToMorseMap.keys()) // добавляем верхний регистр
        m_charToMorseMap[letter.toUpper()] = m_charToMorseMap[letter];
}

bool MTTranslator::isMorseCode(const QString &input)
{
    for (const QChar &letter : input)
        if (letter != '.' && letter != '-' && letter != ' ')
            return false;
    return true;
}
