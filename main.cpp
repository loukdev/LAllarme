
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

#include <QApplication>
#include <QLibraryInfo>
#include <QLocale>
#include <QTranslator>

#include "LAllarme.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

	QString locale = /*QLocale::system().name().section('_', 0, 0)*/ "fr";

	/*
	QString locale = QLocale::system().name().section('_', 0, 0);
	QTranslator trans;
	trans.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(&trans);

	QStringList list; QString s, res = ""; bool ok;
	list << "English" << "Francais";

	res = QInputDialog::getItem(0, "Language selection", "Select your language :", list, 0, false, &ok);

	if(!ok || res == "")
		s = "lallarme_" + locale;
	else
	{
		if(res == "English")
			s = "lallarme_en";
		else if(res == "Francais")
			s = "lallarme_fr";
	}


// */QTranslator stdtrans; /*
// */stdtrans.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));/*
// */app.installTranslator(&stdtrans); /*

// */QTranslator usertrans; /*
// */usertrans.load("languages/lallarme_fr"); /*
// */app.installTranslator(&usertrans);

	//QMessageBox::information(0, "WOUF !", VERSION);

	LAllarme IDontKnowHowNameThisObjectAndNowItHasOne;	// Because I'm completely mad
	IDontKnowHowNameThisObjectAndNowItHasOne.show();

	return app.exec();
}
