#if !defined(GRID_H)
#define GRID_H

#include "actor.h"
#include <vector>

class Tile;

class Grid : public Actor {
public:
    Grid();

    void processClick(int x, int y);
    Tile& getStartTile();
    Tile& getEndTile();

    bool findPath(Tile& start, Tile const& goal);
    void updateActor(float dt) override;
    void buildTower();

private:
    void selectTile(size_t row, size_t col);
    void updatePathTiles(Tile const& start);

    Tile* selectedTile;

    std::vector<std::vector<Tile*>> tiles;

    float nextEnemyTimer;
    const float TIME_BETWEEN_ENEMIES = 1.5f;

    const size_t NB_ROWS = 7;
    const size_t NB_COLS = 16;

    const float START_Y = 192.f;
    const float TILESIZE = 64.f;
};

#endif
