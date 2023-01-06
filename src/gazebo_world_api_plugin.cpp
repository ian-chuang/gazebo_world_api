#include <gazebo_world_api/gazebo_world_api_plugin.h>

#define DEFAULT_REQUEST_DELETE_MODELS_TOPIC "gazebo_world_api/delete_models"
#define DEFAULT_REQUEST_SPAWN_MODELS_TOPIC "gazebo_world_api/spawn_models"

using gazebo::GazeboWorldAPI;

GZ_REGISTER_WORLD_PLUGIN(GazeboWorldAPI)

GazeboWorldAPI::GazeboWorldAPI()
{
}

GazeboWorldAPI::~GazeboWorldAPI()
{
}

void GazeboWorldAPI::Load(physics::WorldPtr _world, sdf::ElementPtr _sdf){
    ros::NodeHandle node;
    
    node.param<std::string>("request_delete_models_service", REQUEST_DELETE_MODELS_TOPIC, DEFAULT_REQUEST_DELETE_MODELS_TOPIC);
    ROS_INFO("GazeboWorldAPI: Got request delete models topic name: <%s>", REQUEST_DELETE_MODELS_TOPIC.c_str());

    node.param<std::string>("request_spawn_models_service", REQUEST_SPAWN_MODELS_TOPIC, DEFAULT_REQUEST_SPAWN_MODELS_TOPIC);
    ROS_INFO("GazeboWorldAPI: Got request spawn models topic name: <%s>", REQUEST_SPAWN_MODELS_TOPIC.c_str());
    
    world=_world;   

    request_delete_models_srv = node.advertiseService(REQUEST_DELETE_MODELS_TOPIC, &GazeboWorldAPI::requestDeleteModels,this);
    request_spawn_models_srv = node.advertiseService(REQUEST_SPAWN_MODELS_TOPIC, &GazeboWorldAPI::requestSpawnModels,this);
}

bool GazeboWorldAPI::requestDeleteModels(gazebo_world_api::DeleteModels::Request &req, gazebo_world_api::DeleteModels::Response &res) {

    std::vector<std::string> model_names = req.model_names;

    for (unsigned int i = 0; i < model_names.size(); i++) {
        world->RemoveModel(model_names[i]);
    }

    ROS_INFO("GazeboWorldAPI: finished request ");
    return true;
}

bool GazeboWorldAPI::requestSpawnModels(gazebo_world_api::SpawnModels::Request &req, gazebo_world_api::SpawnModels::Response &res) {

  // std::vector<std::string> model_names = req.model_names;

  // std::string model_name = model_names[0];
  // physics::ModelPtr model = world->ModelByName(model_name);

  // sdf::ElementPtr = model->GetSDF();
  return false;
}


void GazeboWorldAPI::URDF_to_SDF(std::string& model_xml) {
  // {
  //   std::string open_bracket("<?");
  //   std::string close_bracket("?>");
  //   size_t pos1 = model_xml.find(open_bracket,0);
  //   size_t pos2 = model_xml.find(close_bracket,0);
  //   if (pos1 != std::string::npos && pos2 != std::string::npos)
  //     model_xml.replace(pos1,pos2-pos1+2,std::string(""));
  // }

  // // Remove comments from URDF
  // {
  //   std::string open_comment("<!--");
  //   std::string close_comment("-->");
  //   size_t pos1;
  //   while((pos1 = model_xml.find(open_comment,0)) != std::string::npos){
  //     size_t pos2 = model_xml.find(close_comment,0);
  //     if (pos2 != std::string::npos)
  //       model_xml.replace(pos1,pos2-pos1+3,std::string(""));
  //   }
  // }

  // // Now, replace package://xxx with the full path to the package
  // {
  //   std::string package_prefix("package://");
  //   size_t pos1 = model_xml.find(package_prefix,0);
  //   while (pos1 != std::string::npos)
  //   {
  //     size_t pos2 = model_xml.find("/", pos1+10);
  //     //ROS_DEBUG_NAMED("api_plugin", " pos %d %d",(int)pos1, (int)pos2);
  //     if (pos2 == std::string::npos || pos1 >= pos2)
  //     {
  //       ROS_ERROR_NAMED("api_plugin", "Malformed package name?");
  //       break;
  //     }

  //     std::string package_name = model_xml.substr(pos1+10,pos2-pos1-10);
  //     //ROS_DEBUG_NAMED("api_plugin", "package name [%s]", package_name.c_str());
  //     std::string package_path = ros::package::getPath(package_name);
  //     if (package_path.empty())
  //     {
  //       ROS_FATAL_NAMED("api_plugin", "Package[%s] does not have a path",package_name.c_str());
  //       // res.success = false;
  //       // res.status_message = "urdf reference package name does not exist: " + package_name;
  //       return false;
  //     }
  //     ROS_DEBUG_ONCE_NAMED("api_plugin", "Package name [%s] has path [%s]", package_name.c_str(), package_path.c_str());

  //     model_xml.replace(pos1,(pos2-pos1),package_path);
  //     pos1 = model_xml.find(package_prefix, pos1);
  //   }
  // }
}