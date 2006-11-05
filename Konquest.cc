#include <kapplication.h>
#include <klocale.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>

#include "version.h"
#include "mainwin.h"
#include "mapview.h"

static const char description[] = I18N_NOOP("Galactic Strategy KDE Game");

int
main(int argc, char **argv)
{
    KAboutData aboutData( "konquest", I18N_NOOP("Konquest"),
        KONQUEST_VERSION, description, KAboutData::License_GPL,
        I18N_NOOP("Copyright (c) 1999-2001, Developers"));
    aboutData.addAuthor("Russ Steffen",0, "rsteffen@bayarea.net");
    KCmdLineArgs::init( argc, argv, &aboutData );

    KApplication a;
    KGlobal::locale()->insertCatalog("libkdegames");

    if (a.isSessionRestored())
        RESTORE(MainWindow)
    else {
        MainWindow *w = new MainWindow;
        w->show();
    }
    return a.exec();
}

