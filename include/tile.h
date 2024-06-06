#if !defined(TILE_H)
#define TILE_H

#include "actor.h"
#include "grid.h"
#include "spriteComponent.h"
#include <vector>

class Tile : public Actor {
public:
    friend class Grid;
    enum class TileState {
        Default,
        Path,
        Start,
        Base,
        Obstacle
    };

    Tile();
    Tile(Tile const&);
    Tile operator=(Tile const&);

    TileState getTileState() const { return tileState; }
    Tile const* getParent() const { return parent; }

    void setTileState(TileState tileStateP);
    void toggleSelect();

private:
    void updateTexture();
    SpriteComponent* sprite;
    TileState tileState;
    bool isSelected;
    bool isBlocked;

    // pathfinding
    std::vector<Tile*> adjacentTiles;
    Tile* parent;
    float f;
    float g;
    float h;
    bool isInOpenSet;
    bool isInClosedSet;
};

#endif
