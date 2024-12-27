// todolist.h
#ifndef todolist_H
#define todolist_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
    class todolist;
}

class todolist : public QDialog {
    Q_OBJECT

public:
    explicit todolist(QWidget *parent = nullptr);
    ~todolist();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_listWidget_currentRowChanged(int currentRow);

    void saveTasks(const QListWidget *listWidget, const QString &fileName);
    void saveTask(const QString &task, const QString &fileName);
    void loadTasks(QListWidget *listWidget, const QString &fileName);

private:
    Ui::todolist *ui;
    QString todoFilePath;
    QString doneFilePath;
    int selected = -1;
};

#endif // todolist_H
