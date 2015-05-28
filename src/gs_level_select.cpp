
#include "gs_level_select.h"
#include "level_graph.h"
#include "level_node.h"
#include "assets.h"
#include "gfx/graphic.h"



GSLevelSelect::GSLevelSelect()
{
    level_graph_ = new LevelGraph();
    type_ = GS_LEVEL_SELECT;
    user_interface_ = nullptr;
    //event_handler_ = new EHLevel();

    background_ = new Graphic();
    background_->load_texture("assets/art/level_select_background.png");
}

bool GSLevelSelect::init()
{
    LevelNode * node1 = new LevelNode();
    node1->set_position(Point(200, 200));
    node1->set_width(50);
    node1->set_height(50);
    node1->set_level_file(kMapTest24x18);

    LevelNode * node2 = new LevelNode();
    node2->set_position(Point(400, 200));
    node2->set_width(50);
    node2->set_height(50);
    node2->set_level_file(kMapTest24x18);

    node1->add_adjacent(node2);
    node2->add_adjacent(node1);

    level_graph_->add_node(node1);
    level_graph_->add_node(node2);

    return true;
}

bool GSLevelSelect::update(int delta_ticks)
{
    return true;
}

void GSLevelSelect::render()
{
    background_->render();
    level_graph_->render();

}

void GSLevelSelect::end()
{
    delete level_graph_;
    delete background_;
}


