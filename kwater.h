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
 * This file is part of the KDE Water screensaver.
 *
 * @author Sascha Peilicke <sasch.pe@gmx.de>
 */
#ifndef KWATER_H
#define KWATER_H

#include <QPixmap>
#include <QImage>
#include <QVector>
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

protected:
	void resizeEvent(QResizeEvent *event);
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void timeout();

private:
	void readSettings();

	QPixmap m_desktopPixmap;		///< Current desktop
	QImage m_backgroundImage;		///< Scaled desktop
	QImage m_waterImage;			///< Water effect paint target
	int m_width;
	int m_height;
	QVector<int> m_water1;			///< Used for the water algorithm
	QVector<int> m_water2;			///< Used for the water algorithm
	QVector<int> *m_cur;			///< Used for the water algorithm
	QVector<int> *m_old;			///< Used for the water algorithm
};

/**
 * Setup screen to configure the water screensaver.
 */
class KWaterSetup : public KDialog
{
	Q_OBJECT

public:
	explicit KWaterSetup(QWidget *parent = 0);
	~KWaterSetup();

protected:
	void updateSettings();
	void readSettings();

private:

};

#endif
