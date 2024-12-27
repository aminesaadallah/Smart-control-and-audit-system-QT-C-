#include "todolist.h"
#include "ui_todolist.h"
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

todolist::todolist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::todolist)
{
    ui->setupUi(this);
    todoFilePath = "C:/Users/PC/Downloads/Projet manar/Projet manar/gestions_normes/doings/todo.txt";
    doneFilePath = "C:/Users/PC/Downloads/Projet manar/Projet manar/gestions_normes/doings/done.txt";
    loadTasks(ui->listWidget, todoFilePath);
    loadTasks(ui->listWidget_2, doneFilePath);
}



todolist::~todolist()
{
    delete ui;
}

void todolist::on_pushButton_clicked()
{
    QString todo = ui->lineEdit->text();
    if (todo.isEmpty())
        return;
    ui->listWidget->addItem(todo);
    saveTask(todo, todoFilePath);
}

void todolist::on_pushButton_2_clicked()
{
    QListWidgetItem *item = ui->listWidget->takeItem(selected);
    ui->listWidget_2->addItem(item);
    saveTask(item->text(), doneFilePath);
    ui->listWidget->removeItemWidget(item);
}

void todolist::on_listWidget_currentRowChanged(int currentRow)
{
    selected = currentRow;
}

void todolist::saveTasks(const QListWidget *listWidget, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (int i = 0; i < listWidget->count(); ++i) {
            QListWidgetItem *item = listWidget->item(i);
            out << item->text() << "\n";
        }
        file.close();
    }
}

void todolist::saveTask(const QString &task, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        QTextStream out(&file);
        out << task << "\n";
        file.close();
    }
}


void todolist::loadTasks(QListWidget *listWidget, const QString &fileName)
{
    QFile file(fileName);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString task = in.readLine();
            listWidget->addItem(task);
        }
        file.close();
    }
}
