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
#ifndef KONQUEST_NEWGAMEDLG_H
#define KONQUEST_NEWGAMEDLG_H


#include <QDialog>

#include "planet.h"
#include "minimapview.h"
#include "ui_newGameDialog.h"
#include "../players/player.h"
#include "../players/player_gui.h"


// Maximum Number of Players
#define MAX_PLAYERS 10


class NewGameDlgUI : public QWidget, public Ui::newGameDialog
{
public:
    explicit NewGameDlgUI( QWidget *parent ) : QWidget( parent ) {
	setupUi( this );
    }
        ~NewGameDlgUI() {}
};


/*************************************************************************
 New Game Dialog
 ************************************************************************/


class NewGameDlg : public QDialog
{
public:
    NewGameDlg( QWidget *parent, Game *game);
    ~NewGameDlg();

    void  save();

protected:
    void  slotNewMap();
    void  slotUpdateNeutrals(int);
    void  slotAddPlayer(int);
    void  slotRemovePlayer();

    void  slotUpdateSelection(const Coordinate &coord);
    void  slotNewOwner(int);
    void  slotNewKillPercentage(double);
    void  slotNewProduction(int);

public:
    void  updateButtonOk();

private:
    void  updateOwnerCB();
    void  init();

    QList<PlayerGui *> m_selectablePlayer;
    QMenu            *m_playerTypeChooser;
    QPushButton      *okButton;

    Game             *m_game;
    Player           *m_neutral;

    NewGameDlgUI     *m_w;
};

#endif // KONQUEST_NEWGAMEDLG_H
