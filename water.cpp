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
#include "water.h"

#include <QPainter>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <KApplication>
#include <KDebug>

KWaterScreenSaver::KWaterScreenSaver(WId id)
	: KScreenSaver(id)
	, m_desktopPixmap(QPixmap::grabWindow(KApplication::desktop()->winId()))
	, m_currentWaterImage(0)
{
	m_waterImages[0] = QImage(size(), QImage::Format_Indexed8);
	m_waterImages[1] = QImage(size(), QImage::Format_Indexed8);

	readSettings();
	initialize();
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_timer.start(400);
}

KWaterScreenSaver::~KWaterScreenSaver()
{
	m_timer.stop();
}

void KWaterScreenSaver::resizeEvent(QResizeEvent *event)
{
	m_backgroundPixmap = m_desktopPixmap.scaled(event->size());
	m_waterImages[0] = m_waterImages[0].scaled(event->size());
	m_waterImages[1] = m_waterImages[1].scaled(event->size());
}

void KWaterScreenSaver::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	//painter.drawPixmap(rect(), m_backgroundPixmap);
	painter.drawImage(rect(), m_waterImages[m_currentWaterImage]);
	painter.drawText(rect(), Qt::AlignCenter, "Water Screensaver");
}

void KWaterScreenSaver::initialize()
{
}

void KWaterScreenSaver::timeout()
{
	QImage newImg = m_waterImages[m_currentWaterImage];
	QImage oldImg = m_waterImages[m_currentWaterImage == 0 ? 1 : 0];

	for (int y = 1; y < newImg.height() - 1; y++) {
		for (int x = 1; x < newImg.width() - 1; x++) {
			int value = (oldImg.pixelIndex(x, y - 1) + 
					oldImg.pixelIndex(x, y + 1) + 
					oldImg.pixelIndex(x - 1, y) + 
					oldImg.pixelIndex(x + 1, y)) / 2 - oldImg.pixelIndex(x, y);
			newImg.setPixel(x, y, value);
			newImg.setPixel(x, y, newImg.pixelIndex(x, y) - newImg.pixelIndex(x, y) >> 4); // Apply damping
		}
	}

	update();
	// Flip the pointer to the current water pixmap
	m_currentWaterImage == 0 ? m_currentWaterImage = 1 : m_currentWaterImage= 0;
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
