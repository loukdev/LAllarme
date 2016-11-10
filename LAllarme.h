#ifndef LALLARME_H
#  define LALLARME_H

#  include <QTranslator>

#  include <QMainWindow>
#  include <QStatusBar>
#  include <QWhatsThis>

#  include <QMessageBox>
#  include <QInputDialog>
#  include <QFontDialog>
#  include <QColorDialog>

#  include <QTextEdit>
#  include <QLabel>

#  include <QTimer>
#  include <QTime>

#  include "ui_lallarme.h"

#  include "AboutLAllarme.h"

#  include "LAllarmeOptions.h"

#  define MSG_TIMEOUT 2000

class LAllarmeOptions;
class LAllarmeWidget;
class LChronoWidget;

class LAllarme : public QMainWindow, public Ui::LAllarme
{
    Q_OBJECT
    
	public :

        explicit LAllarme(QWidget *parent = 0);
        ~LAllarme();

	public slots :
    // Details in .cpp file

        //void setPalette(const QPalette & palette);

		void adjustSize();						// Adjust size considering the alarm mode and the visible widgets.

		void setLanguage(const LAlla::Language& language);
		void setMode(const LAlla::Mode& mode);

		void aboutLAllarme();					// Open a window (defined in "AboutLallarme.h") about LAllarme application.

	// Auto-called slots
		//void on_Action_ChangeFontColor_triggered();
		void on_Action_ChangeFont_triggered();
		void on_Action_Help_triggered();
		void on_Action_Options_triggered();
		void on_Action_Quit_triggered();

		void on_Action_Alarm_triggered();
		void on_Action_Chrono_triggered();
		void on_Action_Clock_triggered();

	// Time slots
		void timeChanged(QTime time);
		void timePaused(bool onPause);
		void timeStarted(QTime time);
		void timeStopped(QTime time);
		void timeSUp();

	protected :

		LAllarmeOptions *Options;

		LAllarmeWidget	*AlarmWidget;
		LChronoWidget	*ChronoWidget;

		QLabel *Lbl_PermanentTime;

		LAlla::rmeData data;

		LAlla::Mode m_mode;
};

#endif // LALLARME_H
