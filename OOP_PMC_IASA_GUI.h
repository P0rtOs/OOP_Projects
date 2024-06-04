#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOP_PMC_IASA_GUI.h"


class CustomTitleBar;
class Sidebar;
class Workspace;

class OOP_PMC_IASA_GUI : public QMainWindow
{
    Q_OBJECT

public:
    OOP_PMC_IASA_GUI(QWidget *parent = nullptr);
    ~OOP_PMC_IASA_GUI();

private:
    void setupUI();
    Workspace* workspace;
    Sidebar* sidebar;
    Ui::OOP_PMC_IASA_GUIClass ui;
    CustomTitleBar* titleBar;
};
