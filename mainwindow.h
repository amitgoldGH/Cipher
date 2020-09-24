#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_encryptBtn_clicked();

    QString en_decrypt(QString input, int shift, bool mode);
    QString custom_de_encrypt(QString input, QString keyword, bool mode);
    void on_decryptBtn_clicked();

    void on_customEncrypt_clicked();

    void on_customDecrypt_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
