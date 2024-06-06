#include "tile.h"

#include "assets.h"

Tile::Tile() :
    Actor(),
    sprite(nullptr),
    tileState(TileState::Default),
    isSelected(false),
    f(0),
    g(0),
    h(0),
    isBlocked(false),
    isInOpenSet(false),
    isInClosedSet(false),
    parent(nullptr)
{
    sprite = new SpriteComponent(this, Assets::getTexture("TileBrown"));
}

Tile::Tile(const Tile& tileP) :
    Actor(),
    sprite(nullptr),
    tileState(tileP.tileState),
    isSelected(tileP.isSelected),
    f(tileP.f),
    g(tileP.g),
    h(tileP.h),
    isBlocked(tileP.isBlocked),
    isInOpenSet(tileP.isInOpenSet),
    isInClosedSet(tileP.isInClosedSet),
    parent(tileP.parent)
{
    sprite = new SpriteComponent(this, Assets::getTexture("TileBrown"));
}

Tile Tile::operator=(Tile const& tileP) {
    Tile t;
    t.sprite = new SpriteComponent(this, Assets::getTexture("TileBrown"));
    t.tileState = tileP.tileState;
    t.isSelected = tileP.isSelected;
    t.f = tileP.f;
    t.g = tileP.g;
    t.h = tileP.h;
    t.isBlocked = tileP.isBlocked;
    t.isInOpenSet = tileP.isInOpenSet;
    t.isInClosedSet = tileP.isInClosedSet;
    t.parent = tileP.parent;
    return t;
}

void Tile::setTileState(TileState tileStateP) {
    tileState = tileStateP;
    updateTexture();
}

void Tile::toggleSelect() {
    isSelected = !isSelected;
    updateTexture();
}

void Tile::updateTexture() {
    std::string text;
    switch(tileState) {
        case TileState::Start:
            text = "TileTan";
            break;
        case TileState::Base:
            text = "TileGreen";
            break;
        case TileState::Path:
            text = isSelected ? "TileGreySelected" : "TileGrey";
            break;
        case TileState::Obstacle:
            isBlocked = true;
            text = isSelected ? "TileRedSelected" : "TileRed";
            break;
        case TileState::Default:
        default:
            text = isSelected ? "TileBrownSelected" : "TileBrown";
            break;
    }
    sprite -> setTexture(Assets::getTexture(text));
}
