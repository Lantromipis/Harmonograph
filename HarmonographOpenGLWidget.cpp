#include "HarmonographOpenGLWidget.h"
#include <qdebug.h>

HarmonographOpenGLWidget::HarmonographOpenGLWidget(QWidget* parent, HarmonographManager* manager){
	this->manager = manager;
}

HarmonographOpenGLWidget::~HarmonographOpenGLWidget(){
}

void HarmonographOpenGLWidget::wheelEvent(QWheelEvent* event){
	QPoint numDegrees = event->angleDelta() / 8;

	float yDegrees = numDegrees.y()/2000.0;

	const float temp = manager->getDrawParameters().zoom + yDegrees;
	if (temp > minZoom && temp < maxZoom) {
		manager->setZoom(temp);
	}
	this->update();
}

void HarmonographOpenGLWidget::mouseMoveEvent(QMouseEvent* event){
	if (isMousePressed) {
		int dx = previousX - static_cast<int>(event->globalX());
		int dy = previousY - static_cast<int>(event->globalY());

		float dfX = ((dx / stepPhaseX) * piTwo);
		float dfY = ((dy / stepPhaseY) * piTwo);

		previousX = event->globalX();
		previousY = event->globalY();

		manager->rotateXY(dfX, dfY);
	}
	this->update();
}

void HarmonographOpenGLWidget::mousePressEvent(QMouseEvent* event){
	isMousePressed = true;
	previousX = event->globalX();
	previousY = event->globalY();
	this->setCursor(Qt::ClosedHandCursor);
	this->update();
}

void HarmonographOpenGLWidget::mouseReleaseEvent(QMouseEvent* event){
	isMousePressed = false;
	this->setCursor(Qt::OpenHandCursor);
	this->update();
}

void HarmonographOpenGLWidget::initializeGL() {
	QColor back = manager->getDrawParameters().backgroundColor;
	glClearColor(back.redF(), back.greenF(), back.blueF(), 1);
	glLineWidth(manager->getDrawParameters().penWidth);
	glPointSize(manager->getDrawParameters().penWidth);
}

void HarmonographOpenGLWidget::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)w / (float)h;
	glLoadIdentity();
	glOrtho(-aspect, aspect, -1, 1, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void HarmonographOpenGLWidget::paintGL(){
	DrawParameters parameters = manager->getDrawParameters();
	
	QColor back = parameters.backgroundColor;
	glClearColor(back.redF(), back.greenF(), back.blueF(), 1);

	glLineWidth(parameters.penWidth);
	glPointSize(parameters.penWidth);

	switch (parameters.drawMode) {
		case DrawModes::linesMode:
			glBegin(GL_LINE_STRIP);
			break;
		case DrawModes::pointsMode:
			glBegin(GL_POINTS);
			break;
		default:
			glBegin(GL_LINE_STRIP);
			break;
	}

	float xCurrent = 0;
	float yCurrent = 0;

	int stepCount = (int)(255 / 1e-02) + 10;
	float stepR = ((float)(parameters.secondColor.redF() - parameters.firstColor.redF()) / stepCount);
	float stepG = ((float)(parameters.secondColor.greenF() - parameters.firstColor.greenF()) / stepCount);
	float stepB = ((float)(parameters.secondColor.blueF() - parameters.firstColor.blueF()) / stepCount);
	int i = 1;

	for (float t = 0; t < 255; t += 1e-02) {
		glColor3f(parameters.firstColor.redF() + stepR * i, parameters.firstColor.greenF() + stepG * i, parameters.firstColor.blueF() + stepB * i);

		xCurrent = (manager->getCoordinateByTime(Dimension::x, t) * parameters.zoom);
		yCurrent = (manager->getCoordinateByTime(Dimension::y, t) * parameters.zoom);

		glVertex3f(xCurrent, yCurrent, 0);
		i++;
	}
	glEnd();
}

void HarmonographOpenGLWidget::setEnableAA(bool isEnabled) {
	if(isEnabled) {
		QSurfaceFormat format = QSurfaceFormat::defaultFormat();
		format.setSamples(4);
		this->setFormat(format);
		glEnable(GL_MULTISAMPLE);
	} else {
		QSurfaceFormat format = QSurfaceFormat::defaultFormat();
		this->setFormat(format);
		glDisable(GL_MULTISAMPLE);
	}

}