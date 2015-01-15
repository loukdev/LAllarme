#include "LAlla.h"
#include <QObject>

#define tr(s)	(QObject::tr(QString::fromLatin1(s).toStdString().c_str()))

namespace LAlla {
	int toms(int ms, int s, int mn, int hr)  { return ms + s*1000 + mn*60000 + hr*3600000; }
	// Convert hours, minutes seconds and milliseconds to ms.
	int toms(const QTime &time) { return time.msec() + time.second()*1000 + time.minute()*60000 + time.hour()*3600000; }
	// Convert a QTime in milliseconds.
	QTime toQTime(int ms, int s, int mn, int hr)
	{
		s += ms / 1000;
		ms %= 1000;
		mn += s / 60;
		s %= 60;
		hr += mn / 60;
		mn %= 60;
		return QTime(hr, mn, s, ms);
	}
	/* Convert time to a QTime object.
	 * Simplifly milliseconds, seconds and minutes. At the end, ms < 1000 ; s < 60 ; mn < 60
	 */

	AppData::AppData(const QFont& font, const Language& language, const QColor& color)
		: m_font(font), m_color(color), m_lang(language) {}

	AlarmData::AlarmData(const QString& messageToDisplay, const QString& commandToExecute, const bool& ringWhenTimesUp)
		: m_msg(tr(messageToDisplay.toStdString().c_str())), m_cmd(commandToExecute), m_ring(ringWhenTimesUp) {}

	ChronoData::ChronoData(const bool& notesHidden, const bool clearNotes)
		: m_notesHid(notesHidden), m_clrNotes(clearNotes) {}
}
