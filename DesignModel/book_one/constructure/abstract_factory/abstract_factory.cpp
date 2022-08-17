#include "maze.h"

class MazeFactory
{
public:
    MazeFactory();

    virtual Maze *MakeMaze() const { return new Maze; }
    virtual Wall *MakeWall() const { return new Wall; }
    virtual Room *MakeRoom(int n) const { return new Room(n); }
    virtual Door *MakeDoor(Room *r1, Room *r2) const { return new Door(r1, r2); }
};

class EnchantedMazeFactory : public MazeFactory
{
public:
    EnchantedMazeFactory();

    virtual Room *MakeRoom(int n) const
    {
        return new EnchantedRoom(n, CastSpell());
    }

    virtual Door *MakeDoor(Room *r1, Room *r2) const { return new DoorNeedingSpell(r1, r2); }

protected:
    Spell *CastSpell() const;
};

class BombedMazeFactory : public MazeFactory
{
public:
    BombedMazeFactory();
    Wall *MakeWall() const;
    Room *MakeRoom() const;
};

Maze *GameMaze::CreateMaze(MazeFactory &factory)
{
    Maze *aMaze = factory.MakeMaze();
    Room *r1 = factory.MakeRoom(1);
    Room *r2 = factory.MakeRoom(2);

    Door *aDoor = factory.MakeDoor(r1, r2);

    aMaze->AddRoom(r1);
    aMaze->AddRoom(r2);

    r1->SetSide(North, factory.MakeWall());
    r1->SetSide(East, aDoor);
    r1->SetSide(South, factory.MakeWall());
    r1->SetSide(West, factory.MakeWall());
    r2->SetSide(North, factory.MakeWall());
    r2->SetSide(South, factory.MakeWall());
    r2->SetSide(East, factory.MakeWall());
    r2->SetSide(West, aDoor);

    return aMaze;
}

Wall *BombedMazeFactory::MakeWall() const { return new BombedWall; }
Room *BombedMazeFactory::MakeRoom() const { return new RoomWithBombed(n); }

/*
In order to build a maze containing bombs, we just need BombedMazeFactory calling CreateMaze

MazeGame game;
BombedMazeFactory factory;
game.CreateMaze(factory);
*/