#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class CustomWidget;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QPushButton *fileButton;
    QPushButton *submitButton;
    QComboBox *genderCombo;
    CustomWidget *customWidget;
    QPushButton* loadSettingsButton;
    QPushButton* resetButton;

private slots:
    void openImageFileDialog();
    void displayUserInfo();
    void saveUserInfoToFile();
    void loadSettingsFromFile();
    void resetUserInfo();
};

#endif
