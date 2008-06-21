#ifndef WATER_H
#define WATER_H

#include <kscreensaver.h>
#include <KDialog>
#include <QPixmap>

class QTimer;
class QResizeEvent;

/**
 *
 */
class KWaterScreenSaver : public KScreenSaver
{
	Q_OBJECT

public:
	explicit KWaterScreenSaver(WId id);
	virtual ~KWaterScreenSaver();

protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);

private slots:
	void init();
	void timeout();

private:
	void readSettings();

	QTimer *m_timer;
	QPixmap m_desktopPixmap;
	QPixmap m_backgroundPixmap;
};

/**
 *
 */
class KWaterSetup : public KDialog
{
	Q_OBJECT

public:
	explicit KWaterSetup(QWidget *parent = 0);
	virtual ~KWaterSetup();

protected:
	void updateSettings();
	void readSettings();

private:

};

#endif
