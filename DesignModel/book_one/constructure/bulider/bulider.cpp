#include "../abstract_factory/maze.h"

class MazeBulider
{
public:
    // Provides an interface only to the bulider, and is non-abstract, because the concrete implementation can vary widely
    virtual void BulidMaze() {}
    virtual void BulidRoom(int room) {}
    virtual void BulidDoor(int roomFrom, int roomTo) {}

    virtual Maze *GetMaze() { return 0; }

protected:
    MazeBulider();
};

class StandardMazeBulider : public MazeBulider
{
public:
    StandardMazeBulider();

    virtual void BulidMaze();
    virtual void BulidRoom(int);
    virtual void BulidDoor(int, int);

    virtual Maze *GetMaze();

private:
    Direction CommonWall(Room *, Room *);
    Maze *_currentMaze;
};
StandardMazeBulider::StandardMazeBulider()
{
    _currentMaze = 0;
}

void StandardMazeBulider::BulidMaze() { _currentMaze = new Maze; }

Maze *StandardMazeBulider::GetMaze() { return _currentMaze; }

void StandardMazeBulider::BulidRoom(int n)
{
    if (!_currentMaze->RoomNo(n))
    {
        Room *room = new Room(n);
        _currentMaze->AddRoom(room);

        room->SetSide(North, new Wall);
        room->SetSide(South, new Wall);
        room->SetSide(East, new Wall);
        room->SetSide(West, new Wall);
    }
}

void StandardMazeBulider::BulidDoor(int n1, int n2)
{
    Room *r1 = _currentMaze->RoomNo(n1);
    Room *r2 = _currentMaze->RoomNo(n2);
    Door *d = new Door(r1, r2);

    r1->SetSide(CommonWall(r1, r2), d);
    r2->SetSide(CommonWall(r1, r2), d);
}

// Now client can use CreateMaze and StandardMazeBulider to create a maze
/*
Maze* maze;
MazeGame game;
StandardMazeBulider bulider;
maze=game.CreateMaze(bulider);
*/

// A more special class
class CountingMazeBulider : public MazeBulider
{
public:
    CountingMazeBulider();

    virtual void BulidMaze();
    virtual void BulidRoom(int);
    virtual void BulidDoor(int, int);
    virtual void AddWall(int, Direction);

    void GetCounts(int &, int &) const;

private:
    int _doors;
    int _rooms;
};

CountingMazeBulider::CountingMazeBulider() { _rooms = _doors = 0; }

void CountingMazeBulider::BulidRoom(int) { _rooms++; }
void CountingMazeBulider::BulidDoor(int, int) { _doors++; }
void CountingMazeBulider::GetCounts(int &rooms, int &doors) const
{
    rooms = _rooms;
    doors = _doors;
}

// Here's how a client might use
/*
int rooms,doors;
MazeGame game;
CountingMzeBulider bulider;

game.CreateMaze(bulider);
bulider.GetCounts(rooms,doors);
cout<<"The maze has "
    <<rooms<<" rooms and "
    <<doors<<" doors"<<endl;
*/