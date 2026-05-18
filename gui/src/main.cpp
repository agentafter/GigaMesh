//
// GigaMesh - The GigaMesh Software Framework is a modular software for display,
// editing and visualization of 3D-data typically acquired with structured light or
// structure from motion.
// Copyright (C) 2009-2020 Hubert Mara
//
// This file is part of GigaMesh.
//
// GigaMesh is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// GigaMesh is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with GigaMesh.  If not, see <http://www.gnu.org/licenses/>.
//

//! \mainpage GigaMesh
//!
//! \author Hubert Mara

//! \todo check back later for debuging using http://www.cplusplus.com/reference/std/typeinfo/type_info/ AND find a nice way to demangle the output of .name()

// generic C++ includes:
#include <iostream>

// generic Qt includes:
#include <QApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QMessageBox>
#include <QTranslator>

// Qt Interface includes:
#include "QGMMacros.h"
#include "QGMMainWindow.h"

// Qt data structure:
// none.

// C++ includes:
#include <GigaMesh/printbuildinfo.h>

using namespace std;

#include <GigaMesh/logging/Logging.h>

int main( int argc, char *argv[] ) {
	LOG::initLogging();

	QApplication app( argc, argv );

	/*
	//Initialize translation:
	QTranslator translator;

	if(translator.load("GigaMesh_" + QLocale::system().name(), ":/languages"))
		app.installTranslator(&translator);
	*/

	// Application settings:
	app.setOrganizationName( "GigaMesh" );
	app.setApplicationName( "GigaMesh" );
	QCoreApplication::setApplicationVersion( VERSION_PACKAGE );

	// Command line parsing
	QCommandLineParser parser;
	parser.setApplicationDescription( "GigaMesh Software Framework GUI Interface" );
	parser.addHelpOption();
	parser.addVersionOption();
	// from example: parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source file to copy."));
	// from example: parser.addPositionalArgument("destination", QCoreApplication::translate("main", "Destination directory."));

	// A boolean option with a single name
	QCommandLineOption showLoadLastOption( "load-last", 
	                                       QCoreApplication::translate( "main", "Load the last file used." ) );
	parser.addOption( showLoadLastOption );

	QCommandLineOption showHiDPI20Option( "hidpi20", 
	                                       QCoreApplication::translate( "main", "Assume HiDPI Display scale by a factor of 2." ) );
	parser.addOption( showHiDPI20Option );

	QCommandLineOption setLogLevelOption( "log-level",
	                                      QCoreApplication::translate( "main", "Sets the applications logging level [0-4]."),
	                                      "level", "1");
	parser.addOption( setLogLevelOption);

	// File name(s)
	parser.addPositionalArgument(  "filename", 
	                               QCoreApplication::translate( "main", "File with 3D-data.") );

	// Process the actual command line arguments given by the user
	parser.process( app );

	if(parser.isSet(setLogLevelOption))
	{
		QString param = parser.value(setLogLevelOption);
		if(param.size() != 1 || param[0] < '0' || param[0] > '4')
		{
			std::cerr << "The logging level has to be in the range of [0-4]." << std::endl;
		}
		else
		{
			LOG::setLogLevel(static_cast<LOG::LogLevel>(param.toInt()));
		}
	}

	const QStringList args = parser.positionalArguments();

	QString targetFile;
	if( args.size() > 1 ) {
		std::cout << "[Main] WARINING: More than one filename specified. Additional files will be ignored!" << std::endl;
	}
	if( args.size() >= 1 ) {
		targetFile = args.at( 0 );
		std::cout << "[Main] Loading: " << targetFile.toStdString() << std::endl;
	}

	bool loadLast      = parser.isSet( showLoadLastOption );
	bool hidpi20       = parser.isSet( showHiDPI20Option );

	if( ( targetFile.size() > 0 ) && loadLast ) {
		cerr << "ERROR: Exclusive options: --file and --load-last were given." << endl;
		exit( EXIT_FAILURE );
	}

	// Progress with starting GigaMesh
	cout << "[GigaMesh] using Qt Version: " << qVersion() << endl; // see: http://doc.trolltech.com/4.6/qtglobal.html
	printBuildInfo();

	// System checks:
	if( QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGLES ) {
		LOG::fatal() << "[Main] ERROR: This system has no desktop OpenGL support!\n";
		SHOW_MSGBOX_WARN( "No OpenGL", "ERROR: This system has no desktop OpenGL support!" );
		exit( EXIT_FAILURE );
	}
	// Specify an OpenGL 3.3 or 4.3 Core Profile format.
	// That is, no old-school fixed pipeline functionality
	QSurfaceFormat glFormat;
	glFormat.setVersion( 4, 3 );        // Higher version needed for transparency shader
	glFormat.setProfile( QSurfaceFormat::CoreProfile ); // Do not even think to change the Profile to CompatibilityProfile !!!
	glFormat.setSamples( 4 );
	QSurfaceFormat::setDefaultFormat( glFormat );

	// The main window:
	QGMMainWindow mainWindow;
	mainWindow.show();
	mainWindow.setupMeshWidget( glFormat );
	if( hidpi20 ) {
		mainWindow.setupHighDPI20();
	}

	// Pass arguments to the main window
	if( targetFile.size() > 0 ) {
		mainWindow.load( targetFile );
	} else if( loadLast ) {
		if( !mainWindow.loadLast() ) {
			exit( EXIT_FAILURE );
		}
	} else {
		mainWindow.load();
	}

	return app.exec();
}
