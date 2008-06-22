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
	, m_waterImage1(QImage(size(), QImage::Format_Indexed8))
	, m_waterImage2(QImage(size(), QImage::Format_Indexed8))
{
	m_curImg = &m_waterImage1;
	m_oldImg = &m_waterImage2;
	for (int i = 0; i < 255; i++) {
		m_curImg->setColor(i, qGray(i, i, i));
		m_oldImg->setColor(i, qGray(i, i, i));
	}

	readSettings();
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
	m_timer.start(200);	// 40 -> 25 FPS
}

KWaterScreenSaver::~KWaterScreenSaver()
{
	m_timer.stop();
}

void KWaterScreenSaver::resizeEvent(QResizeEvent *event)
{
	m_backgroundPixmap = m_desktopPixmap.scaled(event->size());
	m_waterImage1 = m_waterImage1.scaled(event->size());
	m_waterImage2 = m_waterImage2.scaled(event->size());
}

void KWaterScreenSaver::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);
	//painter.drawPixmap(rect(), m_backgroundPixmap);
	painter.drawImage(rect(), *m_oldImg);
	painter.drawText(rect(), Qt::AlignCenter, "Water Screensaver");
}

void KWaterScreenSaver::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		m_curImg->setPixel(event->x() + 1, event->y() + 1, 255);
		m_curImg->setPixel(event->x() + 1, event->y(), 255);
		m_curImg->setPixel(event->x() + 1, event->y() - 1, 255);
		m_curImg->setPixel(event->x(), event->y() + 1, 255);
		m_curImg->setPixel(event->x(), event->y(), 255);
		m_curImg->setPixel(event->x(), event->y() - 1, 255);
		m_curImg->setPixel(event->x() - 1, event->y() + 1, 255);
		m_curImg->setPixel(event->x() - 1, event->y(), 255);
		m_curImg->setPixel(event->x() - 1, event->y() - 1, 255);
	}
}

void KWaterScreenSaver::timeout()
{
	for (int y = 1; y < m_curImg->height() - 1; y++) {
		for (int x = 1; x < m_curImg->width() - 1; x++) {
			int value = (m_oldImg->pixelIndex(x, y - 1) + 
					m_oldImg->pixelIndex(x, y + 1) + 
					m_oldImg->pixelIndex(x - 1, y) + 
					m_oldImg->pixelIndex(x + 1, y)) / 2 - m_curImg->pixelIndex(x, y);
			value -= value >> 4;	// Apply damp factor
			m_curImg->setPixel(x, y, value);
		}
	}

	update();
	// Flip the pointer to the current water pixmap
	QImage *tmp = m_curImg;
	m_curImg = m_oldImg;
	m_oldImg = tmp;
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
// libkscreensaver interface implementation
//----------------------------------------------------------------------------

class KWaterScreenSaverInterface : public KScreenSaverInterface
{
public:
	virtual KAboutData *aboutData() {
		return new KAboutData("kwater.kss", 0, ki18n("Water"), "0.1", ki18n("Water Screensaver"), KAboutData::License_GPL);
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
