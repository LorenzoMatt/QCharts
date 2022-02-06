#ifndef CREATORTAWIDGET_H
#define CREATORTAWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include<QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QPushButton>

#include "string"
#include "map"
using std::map;
using std::string;

class CreaTortaWidget : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* layout;
    QFormLayout* formLayout;
    QMap<QLineEdit*, QLineEdit*> dati;
    QHBoxLayout* layoutBottoni;
public:
    explicit CreaTortaWidget(QWidget *parent = nullptr);
signals:
    void creaTorta(map<std::string, double>);

private slots:
    void finestraDiConferma();
    void confermaCreazioneTorta();
    void aggiungiRiga();

};

#endif // CREATORTAWIDGET_H
