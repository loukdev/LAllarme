#ifndef LCHRONOWIDGET_H
#  define LCHRONOWIDGET_H

#  include <QPlainTextEdit>
#  include <QPushButton>
#  include <QLineEdit>

#  ifndef LTIMERWIDGETS_H
#    include "LTimerWidget.h"
#  endif

class LChronoWidget : public LTimerWidget
{
	Q_OBJECT

	public :

		LChronoWidget(const QString& title = QString(""), QWidget* parent = 0);
		virtual ~LChronoWidget() {}

		bool isHiddenNotes() const { return m_notesHidden; }
		bool isClearedNotesOnStop() const { return m_clearNotes; }

	public slots :

		void addNote();
		void clearNotes() { TxtEdt_Notes->clear(); m_noteNb = 0; }
		void clearNotesOnStop(const bool& clear) { m_clearNotes = clear; }
		void hideNotes(const bool& hide);

		void next();
		void stop();

	protected :

		void setConnections();
		void setup();

		QLineEdit*		LnEdt_NoteSuffix;
		QPushButton*	PshBtn_AddNote;
		QPlainTextEdit*	TxtEdt_Notes;

		unsigned int	m_noteNb;

		bool			m_notesHidden,
						m_clearNotes;
};

#endif // LCHRONOWIDGET_H
