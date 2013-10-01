#ifndef LALLA_H
#  define LALLA_H

#  include <QString>

#  ifdef unix
#    define los_p_s	"(deb)"
#    define los_s	"deb"
#  else
#    define los_p_s	"(win)"
#    define los_s	"win"
#  endif

#  define lversion	"1-5"
#  define lv_comp_s		"Beta"
#  define LVERSION		(QString("LAllarme ") + lversion + " " + lv_comp_s + " " + los_p_s).toStdString().c_str()
#  define LAPP_VERSION	(QString(lversion) + "-" + lv_comp_s + "-" + los_p_s).toStdString().c_str()

#  include <QColor>
#  include <QFont>
#  include <QTime>

namespace LAlla {
	enum PseBtnState { None, Pause, Continue };

	inline int toms(int ms, int s = 0, int mn = 0, int hr = 0);
	// Convert hours, minutes seconds and milliseconds to ms.
	int toms(const QTime &time);
	// Convert a QTime in milliseconds.
	QTime toQTime(int ms, int s = 0, int mn = 0, int hr = 0);
	/* Convert time to a QTime object.
	 * Simplifly milliseconds, seconds and minutes. At the end, ms < 1000 ; s < 60 ; mn < 60
	 */

	// Enum used to know in which mode LAllarme is.
	enum Mode { Alarm, Chrono };
	enum Language {
		Britton = 0,
		English,
		French
	};

	struct AppData {
		AppData(const QFont& font, const Language& language = French, const QColor& color = QColor());

		QFont		m_font;
		QColor		m_color;
		Language	m_lang;
	};

	struct AlarmData {
			AlarmData(const QString& messageToDisplay = QString::fromAscii("L'alarme a sonné !"), const QString& commandToExecute = "", const bool& ringWhenTimesUp = true);

		QString		m_msg,
					m_cmd;
		bool		m_ring;
	};

	struct ChronoData {
		ChronoData(const bool& notesHidden = false, bool const clearNotes = true);

		bool		m_notesHid,
					m_clrNotes;
	};

	// Struct used to save changes in the options and to have an easier communication between the main window and the option window.
	struct rmeData {
		rmeData(AppData& appData, AlarmData& alarmData = (*new AlarmData), ChronoData& chronoData = *(new ChronoData))
			: m_app(appData), m_alarm(alarmData), m_chrono(chronoData)
		{}

		AppData&	m_app;
		AlarmData&	m_alarm;
		ChronoData&	m_chrono;
	};
}

#endif // LALLA_H
