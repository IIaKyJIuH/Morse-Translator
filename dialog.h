#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}
class MTAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MTAboutDialog(QWidget *parent = nullptr);
    ~MTAboutDialog();

private:
    Ui::Dialog *ui;

    void setLabelText();
};

#endif // DIALOG_H
