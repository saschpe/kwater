/*******************************************************************
 *
 * Copyright 2008 Sascha Peilicke <sasch.pe@gmx.de>
 *
 * This file is part of the KDE project "KWater Screen Saver"
 *
 * KGo is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * KGo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KReversi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *******************************************************************
 */

/** @file
 * This file is part of KWater Screen Saver.
 *
 * @author Sascha Peilicke <sasch.pe@gmx.de>
 */
#ifndef KWATERSCREENSAVER_H
#define KWATERSCREENSAVER_H

#include <QTimer>
#include <QPixmap>
#include <QImage>
#include <kscreensaver.h>
#include <KDialog>

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
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void timeout();

private:
	void readSettings();

	QTimer m_timer;					///< The animation timer
	QPixmap m_desktopPixmap;		///< Stores the current desktop as pixmap
	QPixmap m_backgroundPixmap;		///< Scaled desktop pixmap
	QImage m_waterImage1;
	QImage m_waterImage2;
	QImage* m_curImg;
	QImage* m_oldImg;
};

/**
 * Setup screen to configure the water screensaver.
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
