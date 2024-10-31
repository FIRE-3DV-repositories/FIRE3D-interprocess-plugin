#include "simulator_plugin.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <boost/program_options.hpp>



//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace p_opt = boost::program_options;


afFIRE3DInterprocessPlugin::afVulkanInterprocessPlugin()
{

}

int afFIRE3DInterprocessPlugin::init(int argc, char **argv, const afWorldPtr a_afWorld)
{
    std::cout << "Test simulation plugin" << std::endl;

    _segment = std::make_shared<bip::managed_shared_memory>(
        boost::interprocess::open_or_create,
        "ambfInterprocess",
        65536
    );
    _map = _segment->find<HashMap>("HashMap").first;
    _interprocess = std::make_shared<Interprocess>(*_segment, _map);
    _world = a_afWorld;

    afBaseObjectMap *obj_map = _world->getRigidBodyMap();
    afBaseObjectMap::const_iterator it = obj_map->begin();
    for (pair<std::string, afBaseObjectPtr> kv : *obj_map) {
        std::cout << kv.first;
        std::string name = kv.first;
        if (kv.first.find("/ambf/env/BODY ") == 0) {
            name.erase(0, 15);
        }
        else if (kv.first.find("/ambf/env/") == 0 && kv.first.find("BODY ") != std::string::npos) {
            name.erase(kv.first.find("BODY "), 5);
        }
        std:: cout << " --> " << name << std::endl;
        _names.emplace(kv.first, std::make_shared<ShmemString>(name.c_str(), _segment->get_allocator<ShmemString>()));
    }
    _names.emplace("CameraBasis", std::make_shared<ShmemString>("CameraBasis", _segment->get_allocator<ShmemString>()));

    _changeBasis[0][0] = 1.0f;
    _changeBasis[1][2] = 1.0f;
    _changeBasis[2][1] = -1.0f;
    _changeBasis[3][3] = 1.0f;

    Transform cameraBasisTransform;
    glm::mat4 cameraBasis = _changeBasis;
    cameraBasis[1][2] *= -1.0f;
    cameraBasis[2][1] *= -1.0f;
    memcpy(cameraBasisTransform.array, glm::value_ptr(cameraBasis), sizeof(cameraBasis));
    _interprocess->_map->at(*_names["CameraBasis"]) = cameraBasisTransform;

    return 1;
}

void afFIRE3DInterprocessPlugin::graphicsUpdate(){
    afBaseObjectMap *obj_map = _world->getRigidBodyMap();
    afBaseObjectMap::const_iterator it = obj_map->begin();
    for (pair<std::string, afBaseObjectPtr> kv : *obj_map) {
        if (_interprocess->_map->find(*_names[kv.first]) == _interprocess->_map->end()) {
            continue;    
        }
        Transform transform; 
        glm::mat4 trans{1.0f};
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                trans[i][j] = static_cast<float>(kv.second->getGlobalTransform().m[i][j]);
            }
        }
        trans *= _changeBasis;

        memcpy(transform.array, glm::value_ptr(trans), sizeof(trans));
        _interprocess->_map->at(*_names[kv.first]) = transform;
    }
}

void afFIRE3DInterprocessPlugin::physicsUpdate(double dt)
{

}



afCameraPtr afFIRE3DInterprocessPlugin::findAndAppendCamera(string cam_name)
{

}



void afFIRE3DInterprocessPlugin::keyboardUpdate(GLFWwindow *a_window, int a_key, int a_scancode, int a_action, int a_mods) {

}


void afFIRE3DInterprocessPlugin::mouseBtnsUpdate(GLFWwindow *a_window, int a_button, int a_action, int a_modes){

}

void afFIRE3DInterprocessPlugin::mouseScrollUpdate(GLFWwindow *a_window, double x_pos, double y_pos){

}

void afFIRE3DInterprocessPlugin::reset()
{

}

bool afFIRE3DInterprocessPlugin::close()
{
    return true;
}
