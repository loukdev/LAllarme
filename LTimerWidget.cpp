
/*
	Copyright (c) 2013, Louka FRABOULET
	All rights reserved.
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the University of California, Berkeley nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "LTimerWidget.h"
#include <QMessageBox>

#define tr(s)	tr(QString::fromAscii(s).toStdString().c_str())

LTimerWidget::LTimerWidget(const int &interval, const QString &title, QWidget *parent, const QString& IconsPath)
	: QGroupBox(parent), Button_Start(new QToolButton), Button_Pause(new QToolButton), Button_Stop(new QToolButton),
	  TimeEdit(new QTimeEdit(QTime(0, 10))), timer(new QTimer(this)), initTime(QTime()), inter(interval), btnState(LAlla::Pause)
{
	this->setTitle(title);

	if(interval != 0)
		timer->setInterval(abs(interval));
	else
		timer->setInterval(inter = 1000);
	timer->setSingleShot(false);

	Button_Start->setMinimumSize(QSize(32, 32));
	Button_Pause->setMinimumSize(QSize(32, 32));
	Button_Stop->setMinimumSize(QSize(32, 32));

	Button_Start->setIcon(QIcon(IconsPath + "/Start.png"));
	Button_Pause->setIcon(QIcon(IconsPath + "/Pause.png"));
	Button_Stop->setIcon(QIcon(IconsPath + "/Stop.png"));
	Button_Stop->setIconSize(QSize(16, 16));

	Button_Pause->setEnabled(false);
	Button_Stop->setEnabled(false);
}

void LTimerWidget::start(QTime time)
{
	if(time.isNull())
		time = TimeEdit->time();
	else
		TimeEdit->setTime(time);
	Button_Pause->setEnabled(true);
	Button_Stop->setEnabled(true);
	Button_Start->setEnabled(false);
	timer->start();
	initTime = time;
	emit timeStarted(time);
}

void LTimerWidget::stop()
{
	Button_Pause->setEnabled(false);
	this->setPause(LAlla::Pause);
	Button_Start->setEnabled(true);
	Button_Stop->setEnabled(false);

	timer->stop();
	emit timeStopped(TimeEdit->time());

	TimeEdit->setTime(initTime);
}

void LTimerWidget::next()
{
	int ms = LAlla::toms(TimeEdit->time());
	QTime time = LAlla::toQTime(ms + inter);
	TimeEdit->setTime(time);

	if(this->isVisible())
		emit timeChanged(time);
}

void LTimerWidget::setPause(LAlla::PseBtnState state)
{
	if(state != LAlla::None)
	{
		if(state == LAlla::Continue)
			state = LAlla::Pause;
		else
			state = LAlla::Continue;
	}
	else
		state = btnState;

	if(state == LAlla::Pause)
	{
		timer->stop();
		Button_Pause->setIcon(QIcon("images/Resume.png"));
		emit timePaused(false);
		state = LAlla::Continue;
	}
	else
	{
		timer->start();
		Button_Pause->setIcon(QIcon("images/Pause.png"));
		emit timePaused(true);
		state = LAlla::Pause;
	}
	btnState = state;
}

void LTimerWidget::setVisible(bool visible)
{
	QGroupBox::setVisible(visible);
}

void LTimerWidget::setConnections()
{
	connect(timer, SIGNAL(timeout()), this, SLOT(next()));
	connect(Button_Start, SIGNAL(clicked()), this, SLOT(start()));
	connect(Button_Stop, SIGNAL(clicked()), this, SLOT(stop()));
	connect(Button_Pause, SIGNAL(clicked()), this, SLOT(setPause()));
}

void LTimerWidget::setup()
{
	TimeEdit->setAccelerated(true);

	QHBoxLayout* HLayout = new QHBoxLayout;
	HLayout->addWidget(Button_Start);
	HLayout->addWidget(Button_Pause);
	HLayout->addWidget(Button_Stop);

	QVBoxLayout* VLayout = new QVBoxLayout;
	VLayout->addLayout(HLayout);
	VLayout->addWidget(TimeEdit);
	this->setLayout(VLayout);
}
