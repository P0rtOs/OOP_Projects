#pragma once

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

class CustomTitleBar : public QWidget
{
    Q_OBJECT

public:
    CustomTitleBar(QWidget* parent = nullptr);
   

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
private slots:

    void minimizeWindow();
    void maximizeRestoreWindow();
    void closeWindow();

private:
    QPointF mousePressPos;
    QPointF windowFramePos;
};
