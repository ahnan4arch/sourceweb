#include "NavTableWindow.h"
#include "ui_NavTableWindow.h"
#include "TableSupplier.h"
#include <QStringList>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <cstdlib>

NavTableWindow::NavTableWindow(Nav::TableSupplier *supplier, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NavTableWindow),
    supplier(supplier)
{
    ui->setupUi(this);

    QStringList columnLabels = supplier->getColumnLabels();
    ui->treeWidget->setHeaderLabels(columnLabels);

    QList<QList<QString> > data = supplier->getData();
    foreach (const QList<QString> &row, data) {
        ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(row));
    }
}

NavTableWindow::~NavTableWindow()
{
    delete ui;
}

void NavTableWindow::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    supplier->activate(item->text(0));
}

void NavTableWindow::on_treeWidget_itemSelectionChanged()
{
    QList<QTreeWidgetItem*> selection = ui->treeWidget->selectedItems();
    if (selection.size() == 1) {
        supplier->select(selection[0]->text(0));
    }
}