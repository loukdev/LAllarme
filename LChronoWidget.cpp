
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

#include "LChronoWidget.h"

#define tr(s)	tr(QString::fromAscii(s).toStdString().c_str())

LChronoWidget::LChronoWidget(const QString &title, QWidget *parent)
	: LTimerWidget(10, title, parent), LnEdt_NoteSuffix(new QLineEdit(this)), PshBtn_AddNote(new QPushButton(tr("Noter"), this)),
	  TxtEdt_Notes(new QPlainTextEdit(this)), m_noteNb(0), m_notesHidden(false), m_clearNotes(true)
{
	this->setup();
	this->setConnections();
}


void LChronoWidget::addNote()
{
	m_noteNb++;
	QString s = "#" + QString("").setNum(m_noteNb) + " : " + TimeEdit->text();
	if(!LnEdt_NoteSuffix->text().isEmpty())
		s += " - " + LnEdt_NoteSuffix->text();

	TxtEdt_Notes->appendPlainText(s);
}

void LChronoWidget::hideNotes(const bool &hide)
{
	if(hide && !m_notesHidden)
	{
		LnEdt_NoteSuffix->setVisible(false);
		PshBtn_AddNote->setVisible(false);
		TxtEdt_Notes->setVisible(false);
	}
	if(!hide && m_notesHidden)
	{
		LnEdt_NoteSuffix->setVisible(true);
		PshBtn_AddNote->setVisible(true);
		TxtEdt_Notes->setVisible(true);
	}
	m_notesHidden = hide;
}

void LChronoWidget::next()
{
	if(m_noteNb != 0 && TxtEdt_Notes->toPlainText().isEmpty())
		m_noteNb = 0;
	LTimerWidget::next();
}

void LChronoWidget::stop()
{
	LTimerWidget::stop();
	if(m_clearNotes)
		this->clearNotes();
}


void LChronoWidget::setConnections()
{
	LTimerWidget::setConnections();

	connect(PshBtn_AddNote, SIGNAL(clicked()), this, SLOT(addNote()));
}

void LChronoWidget::setup()
{
	TimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
	TimeEdit->setReadOnly(true);
	TimeEdit->setDisplayFormat("hh:mm:ss:zzz");
	TimeEdit->setTime(QTime(0, 0));

	// The three tool-buttons (start, pause, stop).
	QHBoxLayout* HLay_ToolBtns = new QHBoxLayout;
	HLay_ToolBtns->addWidget(Button_Start);
	HLay_ToolBtns->addWidget(Button_Pause);
	HLay_ToolBtns->addWidget(Button_Stop);

	// Widgets which manage the chronometer.
	QVBoxLayout* VLay_Chrono = new QVBoxLayout;
	VLay_Chrono->addLayout(HLay_ToolBtns);
	VLay_Chrono->addWidget(TimeEdit);

	// The line-edit and the addNote push-button.
	QHBoxLayout* HLay_AddNote = new QHBoxLayout;
	HLay_AddNote->addWidget(LnEdt_NoteSuffix);
	HLay_AddNote->addWidget(PshBtn_AddNote);

	// Graphical optimization with addNote widgets.
	QSpacerItem* VSpacer = new QSpacerItem(0, 40, QSizePolicy::Expanding);
	QVBoxLayout* VLay_AddNote = new QVBoxLayout;
	VLay_AddNote->addSpacerItem(VSpacer);
	VLay_AddNote->addLayout(HLay_AddNote);

	// Assembling upper half layouts.
	QHBoxLayout* HLay_UpperHalf = new QHBoxLayout;
	HLay_UpperHalf->addLayout(VLay_Chrono);
	HLay_UpperHalf->addLayout(VLay_AddNote);

	QVBoxLayout* VLay_Main = new QVBoxLayout;
	VLay_Main->addLayout(HLay_UpperHalf);
	VLay_Main->addWidget(TxtEdt_Notes);

	this->setLayout(VLay_Main);
}
