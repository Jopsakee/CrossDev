#include "customwidget.h"
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent)
    : QWidget(parent), imagePath(""), userName(""), gender("")
{
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int availableHeight = height() - 80;

    // Initialize aspectRatio to a default value (1.0) to avoid division by zero
    qreal aspectRatio = 1.0;

    // Draw the image
    if (!imagePath.isEmpty()) {
        QPixmap image(imagePath);

        // Calculate the aspect ratio
        aspectRatio = static_cast<qreal>(image.width()) / image.height();

        // Calculate the width for the image while maintaining its aspect ratio
        int imageWidth = static_cast<int>(availableHeight * aspectRatio);

        // Draw the scaled image
        painter.drawPixmap((width() - imageWidth) / 2, 0, imageWidth, availableHeight, image.scaled(imageWidth, availableHeight, Qt::KeepAspectRatio));

        // Draw user information below the image
        QFont font = painter.font();
        font.setPointSize(10);
        painter.setFont(font);
        int textHeight = 20;
        painter.setPen(QColor(255, 0, 0));
        painter.drawText((width() - imageWidth) / 2, availableHeight + textHeight, "Name:");

        painter.setPen(QColor(0, 0, 255));
        painter.drawText((width() - imageWidth) / 2, availableHeight + 3 * textHeight, "Gender:");
        painter.setPen(QColor(0, 0, 0));
        painter.drawText((width() - imageWidth) / 2 + 60, availableHeight + textHeight, userName);
        painter.drawText((width() - imageWidth) / 2 + 60, availableHeight + 3 * textHeight, gender);
    }
}

void CustomWidget::setImagePath(const QString &path)
{
    imagePath = path;
    update();
}

void CustomWidget::setUserInfo(const QString& name, const QString& gender)
{
    if (!name.isEmpty()) {
        userName = name;
    }

    if (!gender.isEmpty()) {
        this->gender = gender;
    }

    update();
}


void CustomWidget::saveUserInfoToFile(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << "Name: " << userName << "\n";
        stream << "Gender: " << gender << "\n";
        stream << "Image: " << imagePath << "\n";
        file.close();
    }
}

void CustomWidget::setLoadedUserInfo(const QString& name, const QString& gender)
{
    if (!name.isEmpty()) {
        userName = name;
    } else {
        userName.clear();
    }

    if (!gender.isEmpty()) {
        this->gender = gender;
    } else {
        this->gender.clear();
    }

    update();
}


