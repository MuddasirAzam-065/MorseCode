#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <windows.h>
#include <QtConcurrent>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::convertToMorse(const QString &text)
{
    QString letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    const char* morse[] = {
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",
        ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",
        "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
        "-----", ".----", "..---", "...--", "....-", ".....", "-....",
        "--...", "---..", "----.", "/"
    };

    QString result;
    for (QChar ch : text.toUpper())
    {
        int index = letters.indexOf(ch);
        if (index != -1) {
            result += morse[index];
            result += " ";
        }
    }
    return result.trimmed();
}

void MainWindow::on_convert_clicked()
{
    QString input = ui->textEdit->toPlainText();
    QString morse = convertToMorse(input);
    ui->textEdit_2->setPlainText(morse);
}

void MainWindow::on_clear_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

void MainWindow::on_count_clicked()
{
    int count = ui->textEdit->toPlainText().length();
    QMessageBox::information(this, "Character Count", "Characters: " + QString::number(count));
}

void MainWindow::playMorse(const QString &morseCode)
{
    for (QChar ch : morseCode) {
        if (ch == '.')
        {
            Beep(750, 200);
        } else if (ch == '-')
        {
            Beep(750, 600);
        }
        QThread::msleep(200);
    }
}

void MainWindow::on_play_clicked()
{
    QString morse = ui->textEdit_2->toPlainText();
    (void)QtConcurrent::run([this, morse]() {
        this->playMorse(morse);
    });
}

void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Morse Code", "", "Text Files (*.txt)");
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << "Text: " << ui->textEdit->toPlainText() << "\n";
            out << "Morse Code: " << ui->textEdit_2->toPlainText() << "\n";
            file.close();
            QMessageBox::information(this, "Success", "Morse code saved.");
        } else {
            QMessageBox::warning(this, "Error", "Cannot save file.");
        }
    }
}
