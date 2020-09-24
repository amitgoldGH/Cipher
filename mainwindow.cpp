#include "mainwindow.h"
#include "ui_mainwindow.h"
static constexpr QChar alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::en_decrypt(QString input, int shift, bool mode)
{
    QString result = "";
    if (mode)
        shift *= -1;

    for (int i = 0; i < input.length(); i++)
        result.append(alphabet[((input.at(i).toLatin1() - 65) + shift) % 25]);

    return result;
}

QString MainWindow::custom_de_encrypt(QString input, QString keyword, bool mode)
{
    QString reverseKey = "", result = "";
    for (int i = keyword.length()-1; i >= 0; i--)
        reverseKey.append(keyword[i]);
    int inputCounter = 0;
    int keyLength = keyword.length();
    int currIndex, flag = 1;
    if (mode)
        flag *= -1;
    while (inputCounter < input.length())
    {
        for(int i = 0; i < keyLength && inputCounter < input.length(); i++)
        {
            currIndex = ((input.at(inputCounter++).toLatin1() - 65) + flag * (keyword.at(i).toLatin1() - 65)) % 25;
            if (currIndex < 0)
                currIndex += 25;
            result.append(alphabet[currIndex]);
        }
        for (int i = 0; i < keyLength && inputCounter < input.length(); i++)
        {
            currIndex = ((input.at(inputCounter++).toLatin1() - 65) + flag * (reverseKey.at(i).toLatin1() - 65)) % 25;
            if (currIndex < 0)
                currIndex += 25;
            result.append(alphabet[currIndex]);
        }
        int i = 0;

        for (; i < keyLength && inputCounter < input.length(); i += 2)
        {
            currIndex = ((input.at(inputCounter++).toLatin1() - 65) + flag * (keyword.at(i).toLatin1() - 65)) % 25;
            if (currIndex < 0)
                currIndex += 25;
            result.append(alphabet[currIndex]);
        }
        i--;

        for (; i >= 0 && inputCounter < input.length(); i -= 2)
        {
            currIndex = ((input.at(inputCounter++).toLatin1() - 65) + flag * (keyword.at(i).toLatin1() - 65)) % 25;
            if (currIndex < 0)
                currIndex += 25;
            result.append(alphabet[currIndex]);
        }
    }

    return result;
}

void MainWindow::on_encryptBtn_clicked()
{
    ui->encryptedtext->setText(en_decrypt(ui->unencryptedText->toPlainText().toUpper(), ui->shiftBox->value(), 0));
}

void MainWindow::on_decryptBtn_clicked()
{
    ui->unencryptedText->setText(en_decrypt(ui->encryptedtext->toPlainText().toUpper(), ui->shiftBox->value(), 1));
}

void MainWindow::on_customEncrypt_clicked()
{
    ui->keywordText->setText(ui->keywordText->toPlainText().toUpper());
    ui->encryptedtext->setText(custom_de_encrypt(ui->unencryptedText->toPlainText().toUpper(), ui->keywordText->toPlainText().toUpper(), 0));
}

void MainWindow::on_customDecrypt_clicked()
{
    ui->keywordText->setText(ui->keywordText->toPlainText().toUpper());
    ui->unencryptedText->setText(custom_de_encrypt(ui->encryptedtext->toPlainText().toUpper(), ui->keywordText->toPlainText().toUpper(), 1));
}
