#include "grid.h"

#include "tile.h"
#include "tower.h"
#include "enemy.h"
#include <algorithm>

Grid::Grid() :
    Actor(),
    selectedTile(nullptr),
    nextEnemyTimer(0.f)
{
    tiles.resize(NB_ROWS);
    for (size_t i = 0; i < tiles.size(); i ++) {
        tiles[i].resize(NB_COLS);
    }

    // create tiles
    for (size_t i = 0; i < NB_ROWS; i ++) {
        for (size_t j = 0; j < NB_COLS; j ++) {
            tiles[i][j] = new Tile();
            tiles[i][j] -> setPosition(Vector2(TILESIZE / 2.f + j * TILESIZE, START_Y + i * TILESIZE));
            if (i >= NB_ROWS / 2 - 1 && i <= NB_ROWS / 2 + 1 && j >= NB_COLS / 2 - 1 && j <= NB_COLS / 2 + 1) {
                tiles[i][j] -> setTileState(Tile::TileState::Obstacle);
            } else {
                tiles[i][j] -> setTileState(Tile::TileState::Default);
            }
        }
    }

    // fill adjacent tiles
    for (size_t i = 0; i < NB_ROWS; i ++) {
        for (size_t j = 0; j < NB_COLS; j ++) {
            if (i > 0) {
                tiles[i][j] -> adjacentTiles.push_back(tiles[i - 1][j]);
            }
            if (i < NB_ROWS - 1) {
                tiles[i][j] -> adjacentTiles.push_back(tiles[i + 1][j]);
            }
            if (j > 0) {
                tiles[i][j] -> adjacentTiles.push_back(tiles[i][j - 1]);
            }
            if (j < NB_COLS - 1) {
                tiles[i][j] -> adjacentTiles.push_back(tiles[i][j + 1]);
            }
        }
    }

    findPath(getEndTile(), getStartTile());
    updatePathTiles(getStartTile());

    getStartTile().setTileState(Tile::TileState::Start);
    getEndTile().setTileState(Tile::TileState::Base);
}

void Grid::buildTower() {
    if (selectedTile && !selectedTile -> isBlocked) {
        selectedTile -> isBlocked = true;
        if (findPath(getEndTile(), getStartTile())) {
            Tower* t = new Tower();
            t -> setPosition(selectedTile -> getPosition());
        } else {
            selectedTile -> isBlocked = false;
            findPath(getEndTile(), getStartTile());
        }
        updatePathTiles(getStartTile());
    }
}

void Grid::processClick(int x, int y) {
    y -= static_cast<int>(START_Y - TILESIZE / 2);
    if (y >= 0) {
        x /= static_cast<int>(TILESIZE);
        y /= static_cast<int>(TILESIZE);
        if (x >= 0 && x < static_cast<int>(NB_COLS) && y >= 0 && y < static_cast<int>(NB_ROWS)) {
            selectTile(y, x);
        }
    }
}

Tile& Grid::getStartTile() {
    return *tiles[3][0];
}

Tile& Grid::getEndTile() {
    return *tiles[3][15];
}

bool Grid::findPath(Tile& start, Tile const& goal) {
    // initialize
    for (size_t i = 0; i < NB_ROWS; i ++) {
        for (size_t j = 0; j < NB_COLS; j ++) {
            tiles[i][j] -> g = 0.f;
            tiles[i][j] -> isInOpenSet = false;
            tiles[i][j] -> isInClosedSet = false;
        }
    }

    std::vector<Tile*> openSet;
    Tile* current = &start;
    current -> isInClosedSet = true;

    do {
        for (Tile* neighbour : current -> adjacentTiles) {
            if (neighbour -> isBlocked) {
                continue;
            }

            if (!neighbour -> isInClosedSet) {
                if (!neighbour -> isInOpenSet) {
                    neighbour -> parent = current;
                    neighbour -> h = (neighbour -> getPosition() - goal.getPosition()).length();
                    neighbour -> g = current -> g + TILESIZE;
                    neighbour -> f = neighbour -> g + neighbour -> h;
                    openSet.emplace_back(neighbour);
                    neighbour -> isInOpenSet = true;
                } else {
                    float newG = current -> g + TILESIZE;
                    if (newG < neighbour -> g) {
                        neighbour -> parent = current;
                        neighbour -> g = newG;
                        neighbour -> f = neighbour -> g + neighbour -> h;
                    }
                }
            }
        }
        if (openSet.empty()) {
            break;
        }
        auto iter = std::min_element(begin(openSet), end(openSet), [](Tile* a, Tile* b) { return a -> f < b -> f; });
        current = *iter;
        openSet.erase(iter);
        current -> isInOpenSet = false;
        current -> isInClosedSet = true;
    } while (current != &goal);

    return (current == &goal);
}

void Grid::selectTile(size_t row, size_t col) {
    if (selectedTile != nullptr) {
        selectedTile -> isSelected = false;
        selectedTile -> updateTexture();
    }
    selectedTile = tiles[row][col];
    selectedTile -> isSelected = true;
    selectedTile -> updateTexture();
}
  
void Grid::updateActor(float dt) {
    Actor::updateActor(dt);
    nextEnemyTimer -= dt;
    if (nextEnemyTimer <= 0.f) {
        new Enemy();
        nextEnemyTimer += TIME_BETWEEN_ENEMIES;
    }
}

void Grid::updatePathTiles(Tile const& start) {
    Tile* t = start.parent;
    while (t != &getEndTile()) {
        t -> setTileState(Tile::TileState::Path);
        t = t -> parent;
    }
}
