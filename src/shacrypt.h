#ifndef SHACRYPT_SHACRYPT_H
#define SHACRYPT_SHACRYPT_H

#include <QString>
#include <QMainWindow>

#include "ui_main.h"

class ShaCrypt : public QMainWindow
{
    Q_OBJECT

public:
	ShaCrypt(QWidget *parent = 0);

private slots:
	void btnHashOnClick();
	void btnExitOnClick(bool checked = false);
private:
	Ui::MainWindow ui;
};

#endif
