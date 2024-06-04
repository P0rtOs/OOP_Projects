#include "CustomTitleBar.h"


CustomTitleBar::CustomTitleBar(QWidget* parent) : QWidget(parent)
    {
        // Set up layout
        QHBoxLayout* layout = new QHBoxLayout(this);

        // Window icon
        QLabel* iconLabel = new QLabel(this);
        iconLabel->setPixmap(QPixmap(":/path/to/your/icon.png").scaled(16, 16)); // Replace with your icon path
        layout->addWidget(iconLabel);

        // Title
        QLabel* titleLabel = new QLabel("My Application", this);
        layout->addWidget(titleLabel);

        // Spacer
        layout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        // Minimize button
        QPushButton* minimizeButton = new QPushButton("-", this);
        connect(minimizeButton, &QPushButton::clicked, this, &CustomTitleBar::minimizeWindow);
        layout->addWidget(minimizeButton);

        // Maximize/restore button
        QPushButton* maximizeButton = new QPushButton("□", this);
        connect(maximizeButton, &QPushButton::clicked, this, &CustomTitleBar::maximizeRestoreWindow);
        layout->addWidget(maximizeButton);

        // Close button
        QPushButton* closeButton = new QPushButton("X", this);
        connect(closeButton, &QPushButton::clicked, this, &CustomTitleBar::closeWindow);
        layout->addWidget(closeButton);

        // Set layout margins and spacing
        layout->setContentsMargins(5, 5, 5, 5);
        layout->setSpacing(5);

        setLayout(layout);
        setFixedHeight(30); // Set the height of the title bar
    }

void CustomTitleBar::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        mousePressPos = event->globalPosition();
        windowFramePos = window()->frameGeometry().topLeft();
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        const QPointF delta = event->globalPosition() - mousePressPos;
        window()->move(windowFramePos + delta);
    }
}

void CustomTitleBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void CustomTitleBar::minimizeWindow()
{
    window()->showMinimized();
}

void CustomTitleBar::maximizeRestoreWindow()
{
    if (window()->isMaximized()) {
        window()->showNormal();
    }
    else {
        window()->showMaximized();
    }
}

void CustomTitleBar::closeWindow()
{
    window()->close();
}

