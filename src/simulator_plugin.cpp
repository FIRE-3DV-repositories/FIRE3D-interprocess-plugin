#include "simulator_plugin.h"
#include <glm/gtx/quaternion.hpp>
#include <boost/program_options.hpp>



//------------------------------------------------------------------------------
// DECLARED FUNCTIONS
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
namespace p_opt = boost::program_options;


afVulkanInterprocessPlugin::afVulkanInterprocessPlugin()
{

}

int afVulkanInterprocessPlugin::init(int argc, char **argv, const afWorldPtr a_afWorld)
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

    _changeBasis[0][0] = 1.0f;
    _changeBasis[1][2] = 1.0f;
    _changeBasis[2][1] = -1.0f;
    _changeBasis[3][3] = 1.0f;

    return 1;
}

void afVulkanInterprocessPlugin::graphicsUpdate(){
    // _transform = _interprocess->_map->at(*_name);
    // glm::mat4 trans = glm::make_mat4(_transform.array);
    // trans = glm::rotate(trans, glm::radians(0.1f), glm::vec3(0.0, 1.0, 0.0));
    // memcpy(_transform.array, glm::value_ptr(trans), sizeof(trans));
    // _interprocess->_map->at(*_name) = _transform;

    afBaseObjectMap *obj_map = _world->getRigidBodyMap();
    afBaseObjectMap::const_iterator it = obj_map->begin();
    for (pair<std::string, afBaseObjectPtr> kv : *obj_map) {
        if (_interprocess->_map->find(*_names[kv.first]) == _interprocess->_map->end()) {
            continue;    
        }
        // _rigid_bodies_map[kv.first] = dynamic_cast<afRigidBody *>(obj_map->at(kv.first));
        Transform transform; 
        float floatTrans[16];
        int index = 0;
        for (size_t i = 0; i < 4; i++) {
            for (size_t j = 0; j < 4; j++) {
                // if (j == 1) {
                //     floatTrans[i][j] = static_cast<float>(kv.second->getGlobalTransform().m[i][2]);

                // } else if (j == 2) {
                //     floatTrans[i][j] = static_cast<float>(kv.second->getGlobalTransform().m[i][1]);

                // } else {
                    floatTrans[index] = static_cast<float>(kv.second->getGlobalTransform().m[i][j]);
                    index++;

                // }
            }
        }
        glm::mat4 mat = glm::make_mat4(floatTrans);
        mat *= _changeBasis;


        memcpy(transform.array, glm::value_ptr(mat), sizeof(mat));
        _interprocess->_map->at(*_names[kv.first]) = transform;
    }
}

void afVulkanInterprocessPlugin::physicsUpdate(double dt)
{

}



afCameraPtr afVulkanInterprocessPlugin::findAndAppendCamera(string cam_name)
{

}



void afVulkanInterprocessPlugin::keyboardUpdate(GLFWwindow *a_window, int a_key, int a_scancode, int a_action, int a_mods) {

}


void afVulkanInterprocessPlugin::mouseBtnsUpdate(GLFWwindow *a_window, int a_button, int a_action, int a_modes){

}

void afVulkanInterprocessPlugin::mouseScrollUpdate(GLFWwindow *a_window, double x_pos, double y_pos){

}

void afVulkanInterprocessPlugin::reset()
{

}

bool afVulkanInterprocessPlugin::close()
{
    return true;
}