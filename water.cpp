#include "water.h"

#include <QTimer>
#include <QPainter>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <KConfig>
#include <KGlobal>
#include <KApplication>

KWaterScreenSaver::KWaterScreenSaver(WId id)
	: KScreenSaver(id)
	, m_timer(new QTimer)
	, m_desktopPixmap(QPixmap::grabWindow(KApplication::desktop()->winId()))
{
	readSettings();
	init();

	connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_timer->start(40);
}

KWaterScreenSaver::~KWaterScreenSaver()
{
	m_timer->stop();
	delete m_timer;
}

void KWaterScreenSaver::resizeEvent(QResizeEvent *event)
{
	m_backgroundPixmap = m_desktopPixmap.scaled(event->size());
}

void KWaterScreenSaver::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawPixmap(0, 0, m_backgroundPixmap);
}

void KWaterScreenSaver::init()
{
}

void KWaterScreenSaver::timeout()
{
	update();
}

void KWaterScreenSaver::readSettings()
{
	//KConfigGroup config(KGlobal::config(), "Settings");
	// ....
}

//----------------------------------------------------------------------------

KWaterSetup::KWaterSetup(QWidget *parent)
	: KDialog(parent)
{
	// configure amount of drops, drop size/strength
	// water color ...
}

KWaterSetup::~KWaterSetup()
{
}

void KWaterSetup::updateSettings()
{
}

void KWaterSetup::readSettings()
{
}

//----------------------------------------------------------------------------
// libkscreensaver interface
//----------------------------------------------------------------------------

class KWaterScreenSaverInterface : public KScreenSaverInterface
{
public:
	virtual KAboutData *aboutData() {
		return new KAboutData("kwater.kss", 0, ki18n("Water"), "0.1", ki18n("Water"));
	}
	
	virtual KScreenSaver *create(WId id) {
		return new KWaterScreenSaver(id);
	}

	virtual QDialog *setup() {
		return new KWaterSetup();
	}
};

int main(int argc, char *argv[])
{
	KWaterScreenSaverInterface kss;
	return kScreenSaverMain(argc, argv, kss);
}
