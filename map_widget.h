#ifndef _MAP_WIDGET_H
#define _MAP_WIDGET_H


#include <QWidget>
#include <q3frame.h>
#include <qpixmap.h>

#include <q3gridview.h>

#include <QTimer>
//Added by qt3to4:
#include <QMouseEvent>

#include "gamecore.h"
#include "images.h"

class ConquestMap : public Q3GridView
{
    Q_OBJECT

    // Constructors
public:
    ConquestMap( Map *newMap, QWidget *parent = 0 );
    virtual ~ConquestMap();

    // Interface
public:
    void unselectPlanet();

protected:
    virtual void contentsMousePressEvent( QMouseEvent *e );
    virtual void contentsMouseMoveEvent( QMouseEvent *e );
    virtual void paintCell( QPainter *p, int row, int col );

private slots:
    void mapUpdate();
    void squareBlink();

signals:
    void planetSelected( Planet * );
    void planetHighlighted( Planet * );

private:
    const int SECTOR_HEIGHT;
    const int SECTOR_WIDTH;

    const int BOARD_HEIGHT;
    const int BOARD_WIDTH;

    void drawSector( QPainter *, Sector &, bool borderStrobe = true, bool highlight = false );

    Map *map;
    QColor gridColor;
    QFont labelFont;

    int hiLiteRow, hiLiteCol;
};


#endif
