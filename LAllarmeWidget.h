#ifndef LALLARMEWIDGET_H
#  define LALLARMEWIDGET_H

#  include <QGroupBox>

#  ifndef LTIMERWIDGETS_H
#    include "LTimerWidget.h"
#  endif

class LAllarmeWidget : public LTimerWidget
{
	Q_OBJECT

	public :

		explicit LAllarmeWidget(const QString& title = QString(""), QWidget* parent = 0);
		virtual ~LAllarmeWidget() {}

	public slots :

		void next();

	signals :

		void timeSUp();

	protected :

		void setup();
};

#endif // LALLARMEWIDGET_H
