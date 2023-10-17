#include "mainwindow.h"
#include "customwidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    nameLabel = new QLabel("Enter your name:");
    nameEdit = new QLineEdit();
    fileButton = new QPushButton("Select Image");
    submitButton = new QPushButton("Submit");
    loadSettingsButton = new QPushButton("Load Settings");
    resetButton = new QPushButton("Reset");

    genderCombo = new QComboBox();
    genderCombo->addItem("Male");
    genderCombo->addItem("Female");

    customWidget = new CustomWidget();
    customWidget->setStyleSheet("background-color: yellow;");
    customWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(400, 500);

    layout->addWidget(customWidget);
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);
    layout->addWidget(fileButton);
    layout->addWidget(genderCombo);
    layout->addWidget(submitButton);
    layout->addWidget(loadSettingsButton);
    layout->addWidget(resetButton);

    connect(fileButton, &QPushButton::clicked, this, &MainWindow::openImageFileDialog);
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::displayUserInfo);
    connect(submitButton, &QPushButton::clicked, this, &MainWindow::saveUserInfoToFile);
    connect(loadSettingsButton, &QPushButton::clicked, this, &MainWindow::loadSettingsFromFile);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetUserInfo);
}

void MainWindow::openImageFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!filePath.isEmpty())
    {
        customWidget->setImagePath(filePath);
        customWidget->update();
    }
}
void MainWindow::displayUserInfo()
{
    QString userName = nameEdit->text();
    QString gender = genderCombo->currentText();

    qDebug() << "User Name:" << userName << ", Gender:" << gender;

    customWidget->setUserInfo(userName, gender);
    customWidget->update();

    qDebug() << "Displaying user information...";
}

void MainWindow::saveUserInfoToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save User Info"), "", tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        customWidget->saveUserInfoToFile(filePath);
        QMessageBox::information(this, tr("File Saved"), tr("User information saved to file."));
    }
}

void MainWindow::loadSettingsFromFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Load Settings"), "", tr("Text Files (*.txt)"));
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            QString line;
            QString loadedName;
            QString loadedGender;
            while (!(line = stream.readLine()).isNull()) {
                if (line.startsWith("Name:")) {
                    loadedName = line.mid(6).trimmed();
                } else if (line.startsWith("Gender:")) {
                    loadedGender = line.mid(8).trimmed();
                } else if (line.startsWith("Image:")) {
                    customWidget->setImagePath(line.mid(7).trimmed());
                }
            }
            file.close();
            customWidget->setLoadedUserInfo(loadedName, loadedGender);
        }
    }
}

void MainWindow::resetUserInfo()
{
    customWidget->setImagePath("");
    customWidget->setUserInfo("", "");
}
