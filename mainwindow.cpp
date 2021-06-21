#include "mainwindow.h"
#include "configprog.h"
#include "dialog.h"
#include "translator.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QResource>
#include <QString>
#include <QTextStream>

MTMainWindow::MTMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->encodedBrowser->setReadOnly(false);
    ui->encodedLabel->setText("Английский язык");
    ui->decodedLabel->setText("Азбука Морзе");
    adjustSize();
    const QByteArray geometry = g_programConfig.getGeometry();
    if (!geometry.isEmpty())
        restoreGeometry(geometry);

    m_translator = new MTTranslator(this);

    connect(ui->encodedBrowser, SIGNAL(textChanged()), this, SLOT(slotTextChanged()));
    connect(ui->changeLanguageButton, SIGNAL(clicked()), this, SLOT(slotReverseLanguage()));
    connect(ui->copyButton, SIGNAL(clicked()), this, SLOT(slotCopyToClipboard()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(slotOpenFile()));
    connect(ui->action_Save, SIGNAL(triggered(bool)), this, SLOT(slotSaveToFile()));
    connect(ui->action_About, SIGNAL(triggered(bool)), this, SLOT(slotAboutProgram()));
}

MTMainWindow::~MTMainWindow()
{
    g_programConfig.setGeometry(saveGeometry());

    delete ui;

    delete m_translator; /* Вообще в этом нет необходимости, т.к.
    при создании объекта мы передали родителя-наследника QObject*/
}

void MTMainWindow::swapLanguageLabels()
{
    const QString leftLabelText = ui->encodedLabel->text();
    ui->encodedLabel->setText(ui->decodedLabel->text());
    ui->decodedLabel->setText(leftLabelText);
}

void MTMainWindow::swapBrowsersTexts()
{
    const QString leftBrowserText = ui->encodedBrowser->toPlainText();
    ui->encodedBrowser->setText(ui->decodedBrowser->toPlainText());
    ui->decodedBrowser->setText(leftBrowserText);
}

void MTMainWindow::slotTextChanged()
{
    const QString text = ui->encodedBrowser->toPlainText();
    QString parsedText;
    if (m_translator->isMorseCode(text)) {
        if (ui->encodedLabel->text() == "Английский язык")
            swapLanguageLabels(); // т.к. по умолчанию слева - Английский
        parsedText = m_translator->decodeFromMorse(text);
    } else {
        if (ui->encodedLabel->text() == "Азбука Морзе")
            swapLanguageLabels(); // на случай, если вдруг мешаем два языка
        parsedText = m_translator->encodeToMorse(text.toLower());
    }
    ui->decodedBrowser->setPlainText(parsedText);
    ui->symbolsCounter->setText(QString::number(text.size()));
}

void MTMainWindow::slotReverseLanguage()
{
    swapBrowsersTexts();
    slotTextChanged();
}

void MTMainWindow::slotOpenFile()
{
    const QString filePath = QFileDialog::getOpenFileName(this,
                                                          tr("Открытие файла"),
                                                          "",
                                                          tr("Текстовые файлы (*.txt)"));

    if (filePath.isEmpty()) {
        qWarning("Файл не выбран");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Нельзя открыть файл для чтения");
        return;
    }

    ui->encodedBrowser->setText(file.readAll()); // считываем всё из файла
    file.close();
}

void MTMainWindow::slotSaveToFile()
{
    const QString filePath = QFileDialog::getSaveFileName(this,
                                                          tr("Сохранение файла"),
                                                          "./results.txt",
                                                          tr("Текстовые файлы (*.txt)"));

    if (filePath.isEmpty()) {
        qWarning("Имя файла не выбрано");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qWarning("Не получилось открыть файл для записи");
        return;
    }

    QTextStream stream(&file);
    const QString text = ui->encodedBrowser->toPlainText();
    if (m_translator->isMorseCode(text)) // будем записывать в файл только азбуку Морзе
        stream << text;
    else
        stream << ui->decodedBrowser->toPlainText();
    file.close();
}

void MTMainWindow::slotAboutProgram()
{
    MTAboutDialog dialog;
    dialog.exec();
}

void MTMainWindow::slotCopyToClipboard()
{
    QClipboard *clipboard = QApplication::clipboard();
    const QString text = ui->decodedBrowser->toPlainText();
    clipboard->setText(text, QClipboard::Clipboard);
}
