/*
    Copyright 2003 Russell Steffen <rsteffen@bayarea.net>
    Copyright 2003 Stephan Zehetner <s.zehetner@nevox.org>
    Copyright 2006 Dmitry Suzdalev <dimsuz@gmail.com>
    Copyright 2006 Inge Wallin <inge@lysator.liu.se>
    Copyright 2006 Pierre Ducroquet <pinaraf@gmail.com>
    Copyright Sean D'Epagnier <geckosenator@gmail.com>

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

#ifndef KONQUEST_MINIMAPVIEW_H
#define KONQUEST_MINIMAPVIEW_H

#include <QWidget>

#include "map/map.h"


class MiniMapView : public QWidget
{
    Q_OBJECT

public:
    explicit MiniMapView(QWidget *parent = 0);
    ~MiniMapView();

    void setMap(Map *newMap);

    /**
     * @note Always use hasSelection() first to make sure that the returned
     * selection is valid.
     */

    Coordinate selection() const { return m_selection; }

    bool hasSelection() const { return (m_selection.x() >= 0) && (m_selection.x() < m_map->columns()) && (m_selection.y() >= 0) && (m_selection.y() < m_map->rows()); }

Q_SIGNALS:
    void sectorSelected(const Coordinate &coord);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void CalculateOffsets(float &, float &, float &);

    Map  *m_map;
    Coordinate m_selection;
};

#endif // KONQUEST_MINIMAPVIEW_H
