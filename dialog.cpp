#include "dialog.h"
#include "ui_dialog.h"

#include <QString>

MTAboutDialog::MTAboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle(tr("О программе"));

    setLabelText();
    adjustSize();
}

MTAboutDialog::~MTAboutDialog()
{
    delete ui;
}

void MTAboutDialog::setLabelText()
{
    const QString message = tr("<html>\
            <b>%1</b> - переводчик с латиницы на азбуку Морзе или наоборот\
            <p><b>Версия</b>: %2<br>\
            <b>Дата сборки</b>: %3</p>\
            <p>Автор программы - <i>Пакулин Сергей Леонидович</i><br>\
            Контактные данные: \
            <a href=\"mailto:pakylin3@mail.ru?subject=Приложение на Qt\">почта</a> \
            || <a href=\"https://t.me/maVrode\">телеграм<a></p>")
                                .arg(APP_NAME, APP_VERSION, "18.06.2021");

    ui->textLabel->setText(message);
    ui->textLabel->setOpenExternalLinks(true);
}
