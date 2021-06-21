#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MTTranslator;

class MTMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MTMainWindow(QWidget *parent = nullptr);
    ~MTMainWindow();

private:
    Ui::MainWindow *ui;
    MTTranslator *m_translator = nullptr;
    void swapLanguageLabels();
    void swapBrowsersTexts();
    void loadSettings();

private slots:
    void slotTextChanged();
    void slotReverseLanguage();
    void slotOpenFile();
    void slotSaveToFile();
    void slotAboutProgram();
    void slotCopyToClipboard();
};

#endif // MAINWINDOW_H
