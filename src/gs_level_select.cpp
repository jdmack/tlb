
#include "gsLevelSelect.h"
#include "levelGraph.h"
#include "levelNode.h"
#include "assets.h"
#include "gfx/graphic.h"



GSLevelSelect::GSLevelSelect()
{
    levelGraph_ = new LevelGraph();
    type_ = GS_LEVEL_SELECT;
    userInterface_ = nullptr;
    //eventHandler_ = new EHLevel();

    background_ = new Graphic();
    background_->loadTexture("assets/art/levelSelectBackground.png");
}

bool GSLevelSelect::init()
{
    LevelNode * node1 = new LevelNode();
    node1->setPosition(Point(200, 200));
    node1->setWidth(200);
    node1->setHeight(200);
    node1->setLevelFile(kMapTest24x18);
    Graphic * graphic1 = new Graphic();
    graphic1->setPosition(node1->position());
    graphic1->loadTexture("assets/art/levelNode.png");
    node1->setGraphic(graphic1);

    LevelNode * node2 = new LevelNode();
    node2->setPosition(Point(600, 200));
    node2->setWidth(200);
    node2->setHeight(200);
    node2->setLevelFile(kMapTest24x18);
    Graphic * graphic2 = new Graphic();
    graphic2->setPosition(node2->position());
    graphic2->loadTexture("assets/art/levelNode.png");
    node2->setGraphic(graphic2);

    node1->addAdjacent(node2);
    node2->addAdjacent(node1);

    levelGraph_->addNode(node1);
    levelGraph_->addNode(node2);

    return true;
}

bool GSLevelSelect::update(int deltaTicks)
{
    return true;
}

void GSLevelSelect::render()
{
    background_->render();
    levelGraph_->render();

}

void GSLevelSelect::end()
{
    delete levelGraph_;
    delete background_;
}


