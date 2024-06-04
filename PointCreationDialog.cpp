#include "PointCreationDialog.h"
#include <QCheckBox>
#include <QHeaderView>

#include <qtablewidget.h>

#include "pointClass.h"


PointCreationDialog::PointCreationDialog(int pointId, double x, double y, const std::vector<Point*>& nearestPoints, QWidget* parent)
    : QDialog(parent)
{
    setupUi(pointId, x, y, nearestPoints);
}

void PointCreationDialog::setupUi(int pointId, double x, double y, const std::vector<Point*>& nearestPoints)
{
    idLabel = new QLabel(QString("ID: %1").arg(pointId), this);
    coordLabel = new QLabel(QString("Coordinates: (%1, %2)").arg(x).arg(y), this);

    typeComboBox = new QComboBox(this);
    typeComboBox->addItem("House", QVariant::fromValue(PointType::House));
    typeComboBox->addItem("School", QVariant::fromValue(PointType::School));
    typeComboBox->addItem("Hospital", QVariant::fromValue(PointType::Hospital));
    typeComboBox->addItem("Post Office", QVariant::fromValue(PointType::PostOffice));
    typeComboBox->addItem("Police Station", QVariant::fromValue(PointType::PoliceStation));

    connectionsTable = new QTableWidget(this);
    connectionsTable->setRowCount(nearestPoints.size());
    connectionsTable->setColumnCount(2);
    connectionsTable->setHorizontalHeaderLabels(QStringList() << "Point ID" << "Connect");
    connectionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (size_t i = 0; i < nearestPoints.size(); ++i) {
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(nearestPoints[i]->getPointId()));
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        connectionsTable->setItem(i, 0, idItem);

        QCheckBox* connectCheckBox = new QCheckBox(this);
        QWidget* checkBoxWidget = new QWidget();
        QHBoxLayout* checkBoxLayout = new QHBoxLayout(checkBoxWidget);
        checkBoxLayout->addWidget(connectCheckBox);
        checkBoxLayout->setAlignment(Qt::AlignCenter);
        checkBoxLayout->setContentsMargins(0, 0, 0, 0);
        checkBoxWidget->setLayout(checkBoxLayout);
        connectionsTable->setCellWidget(i, 1, checkBoxWidget);
    }

    createButton = new QPushButton("Create", this);
    cancelButton = new QPushButton("Cancel", this);

    connect(createButton, &QPushButton::clicked, this, &PointCreationDialog::onCreateButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &PointCreationDialog::onCancelButtonClicked);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(idLabel);
    mainLayout->addWidget(coordLabel);
    mainLayout->addWidget(typeComboBox);
    mainLayout->addWidget(connectionsTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setWindowTitle("Create Point");
}

PointType PointCreationDialog::getSelectedPointType() const
{
    return typeComboBox->currentData().value<PointType>();
}

std::vector<int> PointCreationDialog::getSelectedConnections() const
{
    std::vector<int> selectedConnections;
    for (int i = 0; i < connectionsTable->rowCount(); ++i) {
        QCheckBox* checkBox = qobject_cast<QCheckBox*>(connectionsTable->cellWidget(i, 1)->layout()->itemAt(0)->widget());
        if (checkBox->isChecked()) {
            selectedConnections.push_back(connectionsTable->item(i, 0)->text().toInt());
        }
    }
    return selectedConnections;
}


void PointCreationDialog::onCreateButtonClicked()
{
    accept();
}

void PointCreationDialog::onCancelButtonClicked()
{
    reject();
}
