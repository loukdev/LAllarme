
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

#include "LAllarme.h"

#include <cstdlib>

#include "LAllarmeWidget.h"
#include "LChronoWidget.h"

#define tr(s)	tr(QString::fromAscii(s).toStdString().c_str())

LAllarme::LAllarme(QWidget *parent)
	: QMainWindow(parent), AlarmWidget(new LAllarmeWidget(tr("Alarme"), this)),
	  ChronoWidget(new LChronoWidget(tr("Chronomètre"), this)), Lbl_PermanentTime(new QLabel("00:10:00", this)),
	  data(*new LAlla::AppData(this->font()), *new LAlla::AlarmData(tr("L'alarme a sonné !"))), m_mode(LAlla::Alarm)
{
	this->setupUi(this);
	this->setWindowTitle(LVERSION);
	this->setMinimumSize(195, 176);
	this->resize(195, 176);

	ChronoWidget->setVisible(false);

	QHBoxLayout *Layout = new QHBoxLayout;
	Layout->addWidget(AlarmWidget);
	Layout->addWidget(ChronoWidget);
	this->centralWidget()->setLayout(Layout);

	this->setWindowTitle(LVERSION);
	this->setWindowIcon(QIcon("images/LAllarme.png"));
	this->statusBar()->addPermanentWidget(Lbl_PermanentTime);

	connect(Action_AboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(Action_AboutLAllarme, SIGNAL(triggered()), this, SLOT(aboutLAllarme()));

	// Alarm connections
	connect(AlarmWidget, SIGNAL(timeChanged(QTime)), this, SLOT(timeChanged(QTime)));
	connect(AlarmWidget, SIGNAL(timePaused(bool)), this, SLOT(timePaused(bool)));
	connect(AlarmWidget, SIGNAL(timeStarted(QTime)), this, SLOT(timeStarted(QTime)));
	connect(AlarmWidget, SIGNAL(timeStopped(QTime)), this, SLOT(timeStopped(QTime)));
	connect(AlarmWidget, SIGNAL(timeSUp()), this, SLOT(timeSUp()));

	// Chronometer connections
	connect(ChronoWidget, SIGNAL(timeChanged(QTime)), this, SLOT(timeChanged(QTime)));
	connect(ChronoWidget, SIGNAL(timePaused(bool)), this, SLOT(timePaused(bool)));
	connect(ChronoWidget, SIGNAL(timeStarted(QTime)), this, SLOT(timeStarted(QTime)));
	connect(ChronoWidget, SIGNAL(timeStopped(QTime)), this, SLOT(timeStopped(QTime)));
}

LAllarme::~LAllarme()
{}


/*void LAllarme::setPalette(const QPalette &palette)
{
    ui->GpBox_TimeInfos->setPalette(palette);
    ui->GpBox_TimeManagement->setPalette(palette);
    ui->PshBtn_Start->setPalette(palette);
    QMainWindow::setPalette(palette);
}*/

void LAllarme::adjustSize()
{
	if(m_mode == LAlla::Alarm)				// Minimum size is different for each mode.
	{
		this->setMinimumSize(195, 176);
		this->resize(this->minimumSize());
	}
	else if(m_mode == LAlla::Chrono)
	{
		if(ChronoWidget->isHiddenNotes())		// If notes are hidden, it takes less space.
		{
			this->setMinimumSize(250, 176);
			this->resize(this->minimumSize());
		}
		else
		{
			this->setMinimumSize(350, 280);
			QMainWindow::adjustSize();
		}
	}
}


void LAllarme::setLanguage(const LAlla::Language &language)
{
	QTranslator* trans = new QTranslator(this);
	switch(language)
	{
		case LAlla::Britton :
			break;
		case LAlla::English :
			trans->load("lallarme_en");
			break;
		case LAlla::French :
			trans->load("lallarme_fr");
			break;
		default :
			break;
	}
	if(!trans.isEmpty())
		trans->load("lallarme_en");
	qApp->installTranslator(trans);
}

void LAllarme::setMode(const LAlla::Mode& mode)
{
	this->setWindowTitle(LVERSION);		// Reset the window title with the app version.

	if(mode == LAlla::Alarm && m_mode != LAlla::Alarm)
	{
		ChronoWidget->setVisible(false);
		AlarmWidget->setVisible(true);
		if(AlarmWidget->isActive())
			this->setWindowTitle(AlarmWidget->time().toString());

		Lbl_PermanentTime->setText(AlarmWidget->time().toString());

		Action_Alarm->setChecked(true);
		Action_Chrono->setChecked(false);
	}
	if(mode == LAlla::Chrono && m_mode != LAlla::Chrono)
	{
		ChronoWidget->setVisible(true);
		AlarmWidget->setVisible(false);
		if(ChronoWidget->isActive())
			this->setWindowTitle(ChronoWidget->time().toString());

		Lbl_PermanentTime->setText(ChronoWidget->time().toString());

		Action_Alarm->setChecked(false);
		Action_Chrono->setChecked(true);
	}

	m_mode = mode;
	this->adjustSize();
}


void LAllarme::aboutLAllarme()
{
	AboutLAllarme wdw(this);
    wdw.exec();
}


    // Auto-called slots

// Menu (actions) slots
/*void LAllarme::on_Action_ChangeFontColor_triggered()
{
	QColor color = QColorDialog::getColor(this->palette().color(QPalette::ButtonText), this);
	QPalette palette;
	palette.setColor(QPalette::ButtonText, color);
	LAllarme::setPalette(palette);
}*/

void LAllarme::on_Action_ChangeFont_triggered()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, data.m_app.m_font, this, tr("Changer la police"));

	if(ok)
	{
		data.m_app.m_font = font;
		this->setFont(data.m_app.m_font);
	}
}

void LAllarme::on_Action_Help_triggered()
{
    QWhatsThis::enterWhatsThisMode();
}

void LAllarme::on_Action_Options_triggered()
{
	LAlla::Language olang = data.m_app.m_lang;

	LAllarmeOptions optionWindow(data);
	optionWindow.exec();

	if(data.m_app.m_lang != olang)
		this->setLanguage(data.m_app.m_lang);

	//QMessageBox::information(this, "Wouf !", QString("langue : ") + QString().setNum(data.m_app.m_lang));

	ChronoWidget->hideNotes(data.m_chrono.m_notesHid);
	ChronoWidget->clearNotesOnStop(data.m_chrono.m_clrNotes);

	this->adjustSize();
}

void LAllarme::on_Action_Quit_triggered()
{
	/*QString sw, sh;
	sw.setNum(this->width()); sh.setNum(this->height());
	QMessageBox::information(this, "WAF !", "w = " + sw + " ; h = " + sh);*/
	this->close();
}


void LAllarme::on_Action_Alarm_triggered()
{
	if(m_mode != LAlla::Alarm)
		this->setMode(LAlla::Alarm);
}

void LAllarme::on_Action_Chrono_triggered()
{
	if(m_mode != LAlla::Chrono)
		this->setMode(LAlla::Chrono);
}

void LAllarme::on_Action_Clock_triggered()
{
	ClockWidget *clock = new ClockWidget;
	clock->setAttribute(Qt::WA_DeleteOnClose);
	clock->show();
}


	// Time slots.
void LAllarme::timeChanged(QTime time)
{
	Lbl_PermanentTime->setText(time.toString());
	this->setWindowTitle(time.toString());
}

void LAllarme::timePaused(bool onPause)
{
	if(onPause)
		this->statusBar()->showMessage(tr("Remise en route"), MSG_TIMEOUT);
	else
		this->statusBar()->showMessage(tr("Mise en pause"), MSG_TIMEOUT);
}

void LAllarme::timeStarted(QTime time)
{
	this->statusBar()->showMessage(tr("C'est parti !"), MSG_TIMEOUT);
	if(m_mode == LAlla::Alarm)
		Lbl_PermanentTime->setText(time.toString());
	else
		Lbl_PermanentTime->setText(time.toString("hh:mm:ss:zzz"));
}

void LAllarme::timeStopped(QTime time)
{
	if(m_mode == LAlla::Alarm)
		Lbl_PermanentTime->setText(QTime(0, 0).toString());
	else
		Lbl_PermanentTime->setText(QTime(0, 0).toString("hh:mm:ss:zzz"));
	this->setWindowTitle(LVERSION);

	if(m_mode == LAlla::Alarm && LAlla::toms(time) >= 1000)
		this->statusBar()->showMessage(tr("Alarme stoppée"), MSG_TIMEOUT);
	else
		this->statusBar()->showMessage(tr("Chronomètre stoppé"), MSG_TIMEOUT);
}

void LAllarme::timeSUp()
{
	this->statusBar()->showMessage(tr("C'est l'heure !"), MSG_TIMEOUT);
	Lbl_PermanentTime->setText(QTime(0, 0).toString());
	this->setWindowTitle(LVERSION);

	if(data.m_alarm.m_ring)
	{
		QString s = data.m_alarm.m_msg;
		if(!data.m_alarm.m_cmd.isEmpty())
			s += tr("\nExécution de la commande : ") + data.m_alarm.m_cmd;
		QMessageBox::warning(this, tr("Temps écoulé"), s);
	}
	if(!data.m_alarm.m_cmd.isEmpty())
		system(data.m_alarm.m_cmd.toStdString().c_str());
}
