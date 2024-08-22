#include "simulator_plugin.h"
#include <boost/program_options.hpp>

using namespace std;


//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace p_opt = boost::program_options;


afVolmetricDrillingPlugin::afVolmetricDrillingPlugin()
{

}

int afVolmetricDrillingPlugin::init(int argc, char **argv, const afWorldPtr a_afWorld)
{
    std::cout << "Test simulation plugin" << std::endl;

    return 1;
}

void afVolmetricDrillingPlugin::graphicsUpdate(){

}

void afVolmetricDrillingPlugin::physicsUpdate(double dt)
{

}



afCameraPtr afVolmetricDrillingPlugin::findAndAppendCamera(string cam_name)
{

}



void afVolmetricDrillingPlugin::keyboardUpdate(GLFWwindow *a_window, int a_key, int a_scancode, int a_action, int a_mods) {

}


void afVolmetricDrillingPlugin::mouseBtnsUpdate(GLFWwindow *a_window, int a_button, int a_action, int a_modes){

}

void afVolmetricDrillingPlugin::mouseScrollUpdate(GLFWwindow *a_window, double x_pos, double y_pos){

}

void afVolmetricDrillingPlugin::reset()
{

}

bool afVolmetricDrillingPlugin::close()
{
    return true;
}