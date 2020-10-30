#pragma once
#include <QtWidgets>
#include "Harmonograph.h"
#include "ImagePainter.h"
#include "ImageSaver.h"
#include "HarmonographParametersEnum.h"
#include <deque>
#include <cmath>

class HarmonographManager{
public:
	float const pi = atan(1) * 4;
	float const maxDampingValue = 0.01;
	float const maxFreqModuleValue = 0.1;
	int const sliderMaxValue = 100;


	HarmonographManager();

	QGraphicsPixmapItem* getRenderedGraphicsItem();
	void updateRandomValues();

	void changeXAxisRotation(float radians);
	void rotateXY(float x, float y);

	void saveCurrentImage(QString filename);

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

	void setFrequencyPoint(float freqPt);
	void setNumOfPendulums(int newNum);

	void undoUpdate() {
		if (history.size() > 0) {
			Harmonograph* undoHarm = new Harmonograph(history.back());
			history.pop_back();

			delete harmonograph;

			harmonograph = undoHarm;
		}
	}

	void changeParameter(int pendulumNum, HarmonographParameters parameter, int value);

private:
	Harmonograph* harmonograph;
	ImagePainter* imagePainter;
	ImageSaver* imageSaver;
	std::deque<Harmonograph*> history;
};

