#ifndef ABOUTLALLARME_H
#define ABOUTLALLARME_H

#include <QDialog>
#include "ui_about_lallarme.h"

class AboutLAllarme : public QDialog, public Ui::AboutLAllarme
{
	Q_OBJECT

	public :

		explicit AboutLAllarme(QWidget *parent = 0);
};

#endif // ABOUTLALLARME_H
