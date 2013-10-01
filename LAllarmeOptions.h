#ifndef LALLARMEOPTIONS_H
#  define LALLARMEOPTIONS_H

#  include <QDialog>
#  include <QTextCodec>

#  include <QTimer>
#  include <QTimeEdit>

#  include "ui_lallarme_options.h"

#  include "LAlla.h"

class LAllarmeOptions : public QDialog, public Ui::LAllarmeOptions
{
    Q_OBJECT

	public :

		explicit LAllarmeOptions(LAlla::rmeData &data, QWidget *parent = 0);
		~LAllarmeOptions();

	public slots :

      // Auto-called slots
        void on_BtnBox_accepted();
        void on_BtnBox_rejected();

	private :

		LAlla::rmeData &m_data;
};

#endif // LALLARMEOPTIONS_H
