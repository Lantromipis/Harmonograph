#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "ImagePainter.h"
#include "HarmonographSaver.h"
#include "settings.h"
#include "PendulumEquationParametersEnum.h"
#include "Dimension.h"
#include <deque>
#include <cmath>

class HarmonographManager{
public:
	float const pi = atan(1) * 4;
	float const maxDampingValue = 0.01;
	float const maxFreqModuleValue = 0.1;
	int const sliderMaxValue = 150;


	HarmonographManager();

	QGraphicsPixmapItem* getRenderedGraphicsItem();
	Harmonograph* getHarmCopy();

	void updateRandomValues();

	void changeXAxisRotation(float radians);
	void rotateXY(float x, float y);

	void saveCurrentImage(ImageSettings* settings);

	void saveParametersToFile(QString filename);
	void loadParametersFromFile(QString filename);

	void changeZoom(float value);

	void enableTwoColorMode(bool isEnabled);
	void changeFirstColor(QColor color);
	void changeSecondColor(QColor color);

	void ratioStateEnabled(bool isEnabled);
	void changeFirstRatioValue(int value);
	void changeSecondRatioValue(int value);

	void circleStateEnabled(bool isEnabled);
	void changePenWidth(int width);

	void setFrequencyPoint(float freqPt);
	void setNumOfPendulums(int newNum);

	void undoUpdate();
	int getHistorySize() {
		return history.size();
	}

	void changeParameter(int pendulumNum, EquationParameter parameter, Dimension dimension, int value);

	std::vector<Pendulum*> getPendlumsCopy() {
		return harmonograph->getPundlumsCopy();
	}

private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	HarmonographSaver* imageSaver;
	std::deque<Harmonograph*> history;
};

