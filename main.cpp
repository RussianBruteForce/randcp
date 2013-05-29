/******************* randcp ********************
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *         Version 2, December 2004
 *
 * Copyright (C) 2013 Victor Hackeridze <bruteforce@sigil.tk>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 * DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 ***********************************************/

#include <QTranslator>
#include <QString>
#include <QDir>
#include <QFile>
//#include <QDate>
#include <QTime>
//#include <QDateTime>
#include <unistd.h>
#include <iostream>
//#include <QDebug>

QStringList filesToCopy;
QStringList nameFilters;
QDir fromDir, toDir;
bool recursively = false;
bool verbose = false;
//QDateTime noOlderTime;

int randomize(int Min, int Max)
{
	qsrand(QTime::currentTime().msec());

	if (Min > Max)
	{
		int Temp = Min;
		Min = Max;
		Max = Temp;
	}
	return ((qrand()%(Max-Min+1))+Min);
}

void recAppending() {
	QStringList dirs = fromDir.entryList(QDir::AllDirs | QDir::NoSymLinks | QDir::Readable | QDir::NoDotAndDotDot);
	if (!dirs.isEmpty())
		for(int i = 0; i < dirs.size(); i++) {
			fromDir.cd(dirs.at(i));
			if (recursively)
				recAppending();
			fromDir.cdUp();
		}
	else {
		QStringList l = fromDir.entryList(nameFilters,
						QDir::Files | QDir::NoSymLinks | QDir::Readable | QDir::NoDotAndDotDot);
		for(int i = 0; i < l.size(); i++) {
			l[i].prepend("/");
			l[i].prepend(fromDir.absolutePath());
		}
		filesToCopy.append(l);
	}
}

//QDateTime parseDateTimeFormString(QString string)
//{
//	int d, h, m, s = 0;
//	for (int i = 0; i < string.size(); i++) {
//		QChar c = string.at(i);
//		if (!c.isLower())
//			continue;
//		switch ((int)c.toLatin1()) {
//		case 'd':
//			d = (int)string.at(i-1).toLatin1() - 48;
//			d += (
//			     (int)string.at(i-2).toLatin1()
//			     - 48)
//			     * 10;
//			break;
//		case 'h':
//			h = (int)string.at(i-1).toLatin1() - 48;
//			h += (
//			     (int)string.at(i-2).toLatin1()
//			     - 48)
//			     * 10;
//			break;
//		case 'm':
//			m = (int)string.at(i-1).toLatin1() - 48;
//			m += (
//			     (int)string.at(i-2).toLatin1()
//			     - 48)
//			     * 10;
//			break;
//		case 's':
//			s = (int)string.at(i-1).toLatin1() - 48;
//			s += (
//			     (int)string.at(i-2).toLatin1()
//			     - 48)
//			     * 10;
//			break;
//		default:
//			break;
//		}
//	}
//	QTime time = QTime::currentTime();
//	time = time - QTime(h, m, s);
//	QDate date = QDate::currentDate();

//	qDebug() << date << time;
//	return QDateTime(QDate(0, 0, d),
//			 QTime(h, m, s),
//			 Qt::LocalTime);
//}

void printHelp()
{
	std::cout << QTranslator::tr("randcp by Victor <BruteForce> Hackeridze").toStdString() << '\n' <<
		     "e-mail: bruteforce@sigil.tk" << '\n' <<
		     QTranslator::tr("randcp is for random copying files; license: WTFPL").toStdString() << '\n' <<
		     QTranslator::tr("Usage:").toStdString() << '\n' <<
		     QTranslator::tr("\trancp -f FROM -t TO").toStdString() << '\n' <<
		     QTranslator::tr("Options:").toStdString() << '\n' <<
		     QTranslator::tr("\t-h\t\tPrint this help.").toStdString() << '\n' <<
		     QTranslator::tr("\t-f DIR\t\tSet the FROM directory.").toStdString() << '\n' <<
		     QTranslator::tr("\t-t DIR\t\tSet the TO directory.").toStdString() << '\n' <<
		     QTranslator::tr("\t-e EXT\t\tCopy only files with EXT extension.").toStdString() << '\n' <<
//		     QTranslator::tr("\t-o [##d##h##m##s]\tCopy only files which no older than TIME.").toStdString() << '\n' <<
		     QTranslator::tr("\t-v\t\tPrint verbose info.").toStdString() << '\n' <<
		     QTranslator::tr("\t-r\t\tCopy files recursively.").toStdString() << '\n';
	_exit(0);
}

void printVerbose(QString from, QString to)
{
	std::cout << QTranslator::tr("from ").toStdString() <<
		     from.toStdString() <<
		     QTranslator::tr(" to ").toStdString() <<
		     to.toStdString();
}

void printDebugInfo(QString fileName, QString errorString)
{
	std::cout << QTranslator::tr("Copying ").toStdString() <<
		     fileName.toStdString() <<
		     QTranslator::tr(" failed!\n").toStdString() <<
		     errorString.toStdString() <<
		     '\n';
}

int main(int argc, char *argv[])
{
	QString toDirString, fromDirString, extension;
	int c;
	while ((c = getopt(argc, argv, "hrvt:f:e:o:")) != -1)
		switch (c)
		{
		case 'h':
			printHelp();
			break;
		case 'r':
			recursively = true;
			break;
		case 'v':
			verbose = true;
			break;
		case 't':
			toDirString.append(optarg);
			break;
		case 'f':
			fromDirString.append(optarg);
			break;
		case 'e':
			extension.append(optarg);
			break;
//		case 'o':
//			noOlderTime = parseDateTimeFormString(optarg);
//			qDebug() << noOlderTime;
//			break;
		case '?':
			if (optopt == 'c')
				std::cerr << "Option " << optopt << " requires an argument.\n";
			else if (isprint (optopt))
				std::cerr << "Unknown option " << optopt << ".\n";
			else
				std::cerr << "Unknown option character " << optopt << ".\n";
				return 1;
		default:
			abort();
	}

	if (toDirString.isEmpty() || fromDirString.isEmpty()) {
		std::cerr << QTranslator::tr("You should set FROM and TO directories!").toStdString() << '\n' <<
			     QTranslator::tr("Try randcp -h for usage and simple help.").toStdString() << '\n';
		return 1;
	}

	fromDir.setPath(fromDirString);
	toDir.setPath(toDirString);
	if (!toDir.exists() || !fromDir.exists()) {
		std::cerr << QTranslator::tr("Directory does not exists!").toStdString() << '\n' <<
			     QTranslator::tr("Try another one!").toStdString() << '\n';
		return 1;
	}

	if(!extension.isEmpty())
		nameFilters.append("*." + extension);

	recAppending();

	int filesInList = filesToCopy.size();
	int counter = 0;
	QTime now = QTime::currentTime();
	qsrand(now.msec());
	while (!filesToCopy.isEmpty()) {
		QString s = filesToCopy.takeAt(randomize(0,filesToCopy.size()-1));
		QFile f(s);
		QFileInfo fInfo(f);
		std::cout << ++counter << '/' << filesInList << '\t' <<
			     QTranslator::tr("Copying ").toStdString() <<
			     fInfo.fileName().toStdString() << ' ';
		if (verbose)
			printVerbose(fInfo.filePath(), toDir.absolutePath());
		std::cout << "...\n";

		if (f.copy(toDir.absolutePath() +
			    QString("/" + fInfo.fileName())))
			std::cout << QTranslator::tr("Done!\n").toStdString();
		else if (verbose)
			printDebugInfo(fInfo.fileName(), f.errorString());
		else
			std::cout << QTranslator::tr("Error!\n").toStdString();
	}
	std::cout << QTranslator::tr("Nothing to copy! Exiting...\n").toStdString();
	return 0;
}
