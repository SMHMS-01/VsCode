
enum Direction
{
    North,
    South,
    East,
    West
};
class MapSite
{
public:
    virtual void Enter() = 0;
};

class Room : public MapSite
{
public:
    Room(int roomNo);

    MapSite *GetSide(Direction) const;
    void SetSide(Direction, MapSite *);

    virtual void Enter();

private:
    MapSite *_sides[4];
    int _roomNumber;
};

class Wall : public MapSite
{
public:
    Wall();

    virtual void Enter();
};

class Door : public MapSite
{
public:
    Door(Room *r1 = 0, Room *r2 = 0);

    virtual void Enter();
    Room *OtherSideFrom(Room *);

private:
    Room *_room1;
    Room *_room2;
    bool _isOpen;
};

class Maze
{
public:
    Maze();

    void AddRoom(Room *);
    Room *RoomNo(int) const;

private:
};

class BombedWall : public Wall
{
public:
    BombedWall();
};

class RoomWithBombed : public Room
{
public:
    RoomWithBombed(int n) : Room(n) {}
};

class GameMaze : public Maze
{
public:
    GameMaze();
    Maze *CreateMaze(MazeFactory &factory);
};

