/*
    Copyright 2003 Russell Steffen <rsteffen@bayarea.net>
    Copyright 2003 Stephan Zehetner <s.zehetner@nevox.org>
    Copyright 2006 Dmitry Suzdalev <dimsuz@gmail.com>
    Copyright 2006 Inge Wallin <inge@lysator.liu.se>
    Copyright 2006 Pierre Ducroquet <pinaraf@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "fleetdlg.h"

#include <QHeaderView>
#include <QTableWidget>

#include <kcomponentdata.h>
#include <kglobal.h>
#include <kpushbutton.h>
#include <KStandardGuiItem>
#include <kguiitem.h>
#include <KLocalizedString>

#include "planet.h"
#include "../players/player.h"


FleetDlg::FleetDlg( QWidget *parent,
                    const AttackFleetList &fleets,
                    const AttackFleetList &newFleets,
                    const AttackFleetList &standingOrders)
    : KDialog(parent), m_newFleetList(newFleets), m_standingOrders(standingOrders), m_fleetList(fleets)
{
    setObjectName( QLatin1String( "FleetDlg" ) );
    setModal( true );
    setCaption( i18n("Fleet Overview") );
    setButtons( KDialog::Ok );

    setupTable();
    update();

    setMainWidget( m_fleetTable );
    connect(this, &FleetDlg::okClicked, this, &FleetDlg::accept);
}


QSize
FleetDlg::sizeHint() const
{
    int w = m_fleetTable->verticalHeader()->width();
    int h = m_fleetTable->horizontalHeader()->height();

    for (int col = 0; col < m_fleetTable->columnCount(); ++col) {
        w += m_fleetTable->columnWidth(col);
    }

    for (int row = 0; row < m_fleetTable->rowCount(); ++row) {
        h += m_fleetTable->rowHeight(row);
    }

    /**
     * @todo The created dialogue should not be larger than the screen, and
     * ideally, it should not be larger than the main application window.
     * As the vertical main application window size is not (yet) known here,
     * simply use a hard-coded limit right now.
     */

    if (h > 480) {

        // As the height of the widget is reduced, a vertical scrollbar is
        // shown. Add the width of that scrollbar to the width of the widget to
        // prevent a horizontal scrollbar from appearing.

        h = 480;
        w += m_fleetTable->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    }

    /**
     * @todo The size calculated here does not yet prevent scrollbars to be
     * shown for the table. Figure out the offsets needed to be added and remove
     * the hard-coded numbers below! One reason here is that this size hint is
     * for the whole dialogue and not just for the table.
     */

    return QSize(w, h) + QSize(40, 80);
}


void
FleetDlg::setupTable()
{
    m_fleetTable = new QTableWidget(this);
    m_fleetTable->setColumnCount(7);
    m_fleetTable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_fleetTable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_fleetTable->setSelectionMode(QAbstractItemView::NoSelection);

    QStringList headerLabels;
    headerLabels
        << QString()
        << i18n("Fleet No.")
        << i18n("Source")
        << i18n("Destination")
        << i18n("Ships")
        << i18n("Kill Percentage")
        << i18n("Arrival Turn");

    m_fleetTable->setHorizontalHeaderLabels(headerLabels);
    m_fleetTable->verticalHeader()->hide();
}


void
FleetDlg::update()
{
    AttackFleetList fleets = m_standingOrders + m_newFleetList + m_fleetList;
    const int standingOrders = m_standingOrders.count();
    const int newFleets = standingOrders + m_newFleetList.count();

    m_fleetTable->setRowCount( fleets.count() );

    int row = 0;
    QTableWidgetItem *item;

    foreach (AttackFleet *curFleet, fleets) {
        item = new QTableWidgetItem();
        if( row < newFleets) {
          item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
          item->setCheckState(Qt::Checked);
          if( row < standingOrders )
              item->setText(i18n("Standing order"));
        } else {
          item->setFlags(Qt::ItemIsEnabled);
        }
        m_fleetTable->setItem(row, 0, item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, row + 1);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 1, item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, curFleet->source->name());
        item->setData(Qt::DecorationRole, curFleet->source->player()->color());
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 2, item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, curFleet->destination->name());
        item->setData(Qt::DecorationRole, curFleet->destination->player()->color());
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 3, item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, curFleet->shipCount());
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 4, item);

        // The number is formatted and added as a string. Sorting by this
        // column sorts by string comparison rather than by floating point
        // number comparison. But as all values have the same amount of
        // characters/digits, sorting by string actually works.

        item = new QTableWidgetItem(QString("%1").arg(KLocale::global()->formatNumber(curFleet->source->killPercentage(), 3)));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 5, item);

        item = new QTableWidgetItem();
        item->setData(Qt::DisplayRole, curFleet->arrivalTurn);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        item->setFlags(Qt::ItemIsEnabled);
        m_fleetTable->setItem(row, 6, item);

        ++row;
    }

    m_fleetTable->setSortingEnabled(true);
    m_fleetTable->resizeColumnsToContents();
}


AttackFleetList*
FleetDlg::uncheckedFleets()
{
    AttackFleetList *fleets = new AttackFleetList();
    QTableWidgetItem *item;
    int count = m_fleetTable->rowCount();

    for( int f = 0; f < count; ++f) {
        item = m_fleetTable->item(f,0);
        if( (item->flags() & Qt::ItemIsUserCheckable) &&
            (item->checkState() == Qt::Unchecked) ) {

            const int pos = m_fleetTable->item(f,1)->text().toInt() - 1;
            if (pos >= 0)
            {
                if(pos < m_standingOrders.count())
                    fleets->append( m_standingOrders.at(pos) );
                else
                    fleets->append( m_newFleetList.at(pos - m_standingOrders.count()) );
            }
        }
    }

    return fleets;
}
