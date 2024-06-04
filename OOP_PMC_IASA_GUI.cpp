#include "OOP_PMC_IASA_GUI.h"
#include "Workspace.h"
#include "Sidebar.h"
#include <QDockWidget>
#include <QHBoxLayout>
#include "CustomTitleBar.h"

#include "SimulationController.h"


OOP_PMC_IASA_GUI::OOP_PMC_IASA_GUI(QWidget* parent)
    : QMainWindow(parent), workspace(new Workspace(this)), sidebar(new Sidebar(this))
{
    ui.setupUi(this);
    setupUI();

    SimulationController* controller = new SimulationController(workspace, sidebar, this);

    setCentralWidget(workspace);
}


OOP_PMC_IASA_GUI::~OOP_PMC_IASA_GUI()
{}


void OOP_PMC_IASA_GUI::setupUI()
{
    resize(1200, 800);
    setCentralWidget(workspace);

    QDockWidget* dock = new QDockWidget("Controls", this);
    dock->setWidget(sidebar);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    QMenuBar* menuBar = this->menuBar();
    QMenu* fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("Exit", this, &QMainWindow::close);

    QToolBar* toolBar = addToolBar("Main Toolbar");
    toolBar->addAction("Exit", this, &QMainWindow::close);

    QStatusBar* statusBar = this->statusBar();
    statusBar->showMessage("Ready");
}