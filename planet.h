#ifndef __PLANET_H__
#define __PLANET_H__

#include <QObject>
#include <QList>
#include "fleet.h"

class Player;
class Sector;
class Map;

//**************************************************************
// class Planet
//**************************************************************

class Planet : public QObject
{
    Q_OBJECT

private:

    Planet( QString planetName, Sector &newParentSector,
            Player *initialOwner, int newProd,
            double newKillP, double newMorale );

public:
    // FIXME: Nobody inherits Planet.  Why virtual?  /iw
    virtual ~Planet();

    static Planet *createPlayerPlanet( Sector &parentSector,
                                       Player *initialOwner, QString planetName );
    static Planet *createNeutralPlanet( Sector &parentSector,
                                        Player *initialOwner, QString planetName );

    Sector        &sector()     const { return m_parentSector; }
    Player        *player()     const { return m_owner; }

    const QString &name()       const { return m_name; }
    DefenseFleet  &getFleet()         { return m_homeFleet; }



    double         getKillPercentage() const { return m_killPercentage; }

    void           setKillPercentage( double newValue );
    double         morale()     const { return m_morale; }
    void           setMorale( double );
    int            production() const { return m_productionRate; }
    void           setProduction( int );

    void select();
    void conquer(  AttackFleet *conqueringFleet );
    void coup( Player *luckyPlayer );
    void turn();

signals:
    void update();
    void selected();

private:
    QString       m_name;
    Player       *m_owner;
    Sector       &m_parentSector;
    DefenseFleet  m_homeFleet;

    double        m_killPercentage;
    double        m_morale;
    int           m_productionRate;
};

typedef QList<Planet *> PlanetList;

#endif
