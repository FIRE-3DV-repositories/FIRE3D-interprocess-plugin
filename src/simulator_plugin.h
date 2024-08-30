
#define GL_SILENCE_DEPRECATION
#include <afFramework.h>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/unordered_map.hpp>
#include <memory>
#include <functional>
#include <utility>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <chrono>
#include <unordered_map>

namespace bip = boost::interprocess;
typedef bip::allocator<char, bip::managed_shared_memory::segment_manager> CharAllocator;
typedef bip::basic_string<char, std::char_traits<char>, CharAllocator> ShmemString;
typedef ShmemString HashKeyType;
struct Transform {
    float array[16] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
};

typedef Transform HashMappedType;
typedef std::pair<const ShmemString, Transform> HashValueType;
typedef bip::allocator<HashValueType, bip::managed_shared_memory::segment_manager> HashMemAllocator;
typedef boost::unordered_map<HashKeyType, HashMappedType, boost::hash<HashKeyType>, std::equal_to<HashKeyType>, HashMemAllocator> HashMap;
class Interprocess {
    public:
        Interprocess(bip::managed_shared_memory& segment, bip::offset_ptr<HashMap>& map)
        : _segment(segment), _map(map) {}
        bip::managed_shared_memory& _segment;
        bip::offset_ptr<HashMap>& _map;
};

using namespace ambf;

class afVulkanInterprocessPlugin : public afSimulatorPlugin{
public:
    afVulkanInterprocessPlugin();
    virtual int init(int argc, char** argv, const afWorldPtr a_afWorld) override;
    virtual void keyboardUpdate(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods) override;
    virtual void mouseBtnsUpdate(GLFWwindow* a_window, int a_button, int a_action, int a_modes) override;
    virtual void mousePosUpdate(GLFWwindow* a_window, double x_pos, double y_pos) override {}
    virtual void mouseScrollUpdate(GLFWwindow* a_window, double x_pos, double y_pos) override;
    virtual void graphicsUpdate() override;
    virtual void physicsUpdate(double dt) override;
    virtual void reset() override;
    virtual bool close() override;

protected:
    void sliceVolume(int axisIdx, double delta);

    void makeVRWindowFullscreen(afCameraPtr vrCam, int monitor_number=-1);

    void updateButtons();

    void initializeLabels();

    afCameraPtr findAndAppendCamera(std::string cam_name);

private:
    std::shared_ptr<bip::managed_shared_memory> _segment;
    bip::offset_ptr<HashMap> _map;
    std::shared_ptr<Interprocess> _interprocess;
    std::unordered_map<std::string, std::shared_ptr<ShmemString>> _names;
    afWorldPtr _world;
    glm::mat4 _changeBasis{0.0f};
};


AF_REGISTER_SIMULATOR_PLUGIN(afVulkanInterprocessPlugin)