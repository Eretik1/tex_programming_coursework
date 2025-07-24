#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFile>
#include <QStyle>

class ResultsMenu : public QWidget {
    Q_OBJECT

public:
    ResultsMenu(QWidget *parent = nullptr);
    ~ResultsMenu() override = default;
    void setResults(const QString &Results);    

signals:
    void backRequested();    

private:
    QLabel *ResultsMassege;
    QPushButton *btnBack;
};