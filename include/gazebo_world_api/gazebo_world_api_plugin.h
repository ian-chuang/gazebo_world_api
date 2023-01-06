#ifndef GAZEBO_WORLD_API_PLUGIN_H
#define GAZEBO_WORLD_API_PLUGIN_H

#include <ros/ros.h>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/World.hh>

#include <gazebo_world_api/SpawnModels.h>
#include <gazebo_world_api/SpawnModelsRequest.h>
#include <gazebo_world_api/SpawnModelsResponse.h>

#include <gazebo_world_api/DeleteModels.h>
#include <gazebo_world_api/DeleteModelsRequest.h>
#include <gazebo_world_api/DeleteModelsResponse.h>

namespace gazebo
{

class GazeboWorldAPI : public WorldPlugin
{
public: 
	GazeboWorldAPI();

	virtual ~GazeboWorldAPI() override;

	void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) override;

private:

	bool requestDeleteModels(gazebo_world_api::DeleteModels::Request &req, gazebo_world_api::DeleteModels::Response &res);
	bool requestSpawnModels(gazebo_world_api::SpawnModels::Request &req, gazebo_world_api::SpawnModels::Response &res); 
	void URDF_to_SDF(std::string& model_xml);
	
private:
	//ros::NodeHandle node;
	std::string REQUEST_DELETE_MODELS_TOPIC;
	std::string REQUEST_SPAWN_MODELS_TOPIC;
	physics::WorldPtr world;

	ros::ServiceServer request_delete_models_srv;
	ros::ServiceServer request_spawn_models_srv;
};

}

#endif  // GAZEBO_WORLD_API_PLUGIN_H