#pragma once

#include <QtWidgets>
#include "ui_FlexDialog.h"
#include "FlexWindow.h"

class FlexDialog : public QDialog
{
	Q_OBJECT

public:
	FlexDialog(QWidget* parent = Q_NULLPTR);
	~FlexDialog();

	int penWidth = 1;
	int FPS = 60;
	bool useAntiAliasing = false;
	int flexBaseMode = 1; //2==freq based, 1==phase based

private:
	Ui::FlexDialog ui;
private slots:
	void setBrush(int value);
	void changeBase(int value);
	void useAntialiasingState(int state);
	void setFPS(int value);
};