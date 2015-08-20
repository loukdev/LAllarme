#ifndef LTIMERWIDGET_H
#  define LTIMERWIDGETS_H

#  include <QHBoxLayout>
#  include <QGroupBox>
#  include <QTimeEdit>
#  include <QToolButton>

#  include <QTimer>

#  include "LAlla.h"

class LTimerWidget : public QGroupBox
{
	Q_OBJECT

	public :

		explicit LTimerWidget(const int& interval = -1000, const QString& title = "", QWidget* parent = 0, const QString& IconsPath = "images");
		virtual ~LTimerWidget() {}

		QTime time() const { return TimeEdit->time(); }
		bool isActive() const { return timer->isActive() || btnState == LAlla::Continue;}

	public slots :

		void start(QTime time = QTime());
		// Starts the timer at the given time. If the time is not given, starts at (QTimeEdit) TimeEdit->time().
		void stop();
		// Called when the time's up.
		void next();
		// Called every tick (default : 1 tick = 1 second).
		void setPause(LAlla::PseBtnState state = LAlla::None);
		// If state is Lalla::Continue or Lalla::Pause, set the pause button to respectively resume and pause. Else, the pause button is switched.

		virtual void setVisible(bool visible);

	signals :

		void timeChanged(QTime time);
		void timePaused(bool onPause);
		void timeStarted(QTime time);
		void timeStopped(QTime time);

	protected :

		void setConnections();
		void setup();

		QToolButton *Button_Start,
					*Button_Pause,
					*Button_Stop;

		QTimeEdit	*TimeEdit;
		QTimer		*timer;
		QTime		 initTime;

		int			 inter;

		LAlla::PseBtnState btnState;
};

class ClockWidget : public QTimeEdit
{
	Q_OBJECT

	public :

		ClockWidget(QWidget* parent = NULL) : QTimeEdit(parent)
		{
			QTimer *timer = new QTimer(this);
			timer->setInterval(1000);
			timer->setSingleShot(false);
			this->setReadOnly(true);
			this->setButtonSymbols(QAbstractSpinBox::NoButtons);
			this->setTime();
			this->setWindowTitle("Hour");

			timer->start();

			connect(timer, SIGNAL(timeout()), this, SLOT(setTime()));
		}

	public slots :

		void setTime()
		{
			QTimeEdit::setTime(QTime::currentTime());
		}
};

#endif // LTIMERWIDGETS_H
