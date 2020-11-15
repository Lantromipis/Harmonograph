#pragma once

#include <QDialog>
#include "ui_SaveImageDialog.h"

class SaveImageDialog : public QDialog
{
	Q_OBJECT

public:
	SaveImageDialog(QWidget *parent = Q_NULLPTR);
	~SaveImageDialog();

	bool useAntialising = false;
	bool useSquareImage = false;
	int saveWidth = 1920;
	int saveHeight = 1080;
	int penWidth = 1;
protected:
private:
	Ui::SaveImageDialog ui;
private slots:
	virtual void accept();
};
