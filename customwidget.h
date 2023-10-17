#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

class CustomWidget : public QWidget
{
    Q_OBJECT

public:
    CustomWidget(QWidget *parent = nullptr);

    void setImagePath(const QString &path);
    void setUserInfo(const QString &name, const QString &gender);
    void saveUserInfoToFile(const QString& filePath);
    void setLoadedUserInfo(const QString& name, const QString& gender);


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString imagePath;
    QString userName;
    QString gender;
};

#endif
