#ifndef OPCUASERVER_H
#define OPCUASERVER_H

#include<string>

#include <opc/ua/server/addons/services_registry.h>
#include <opc/common/addons_core/config_file.h>
#include <opc/common/application.h>
#include <opc/ua/computer.h>
#include <opc/ua/node.h>


namespace OpcUa
{
  class OPCUAServer
  {
    public:
      OPCUAServer(); 
      void SetEndpoint(const std::string endpoint){this->endpoint = endpoint;}
      void SetURI(const std::string uri){this->uri = uri;}
      void SetServerName(const std::string name){this->name = name;}
      void AddAddressSpace(const std::string path) {xml_address_spaces.push_back(path);}

      void Start();
      void Stop();
      //Node GetNode(std::vector<QualifiedName> browsepath); //Do we need that? or should we use rootnode anyway?
      //Node GetNode(std::vector<std::string> browsepath);
      Node GetRootNode();
      Node GetObjectsNode();
      Node GetNode(NodeID nodeid) {return Node(server, nodeid);}
      void SetConfigFile(const std::string path);
      Node GetNodeFromPath(const std::vector<QualifiedName>& path) {return GetRootNode().GetChildNode(path);}
      Node GetNodeFromPath(const std::vector<std::string>& path) {return GetRootNode().GetChildNode(path);}

    private:

      Common::ModulesConfiguration const GetConfig();

      OpcUa::Application::UniquePtr application;
      OpcUa::Server::ServicesRegistryAddon::SharedPtr registry; //Why do I need to keep a pointer to the registry? 
      std::vector<Common::AddonInformation> infos; //why do I need to keep a pointer? otherwise I get coredump
      OpcUa::Remote::Computer::SharedPtr server;
      std::vector<std::string> xml_address_spaces;
      std::string config_path = "";
      std::string endpoint = "opc.tcp://localhost:4841"; //This is the expected address of an OPC-UA server on a machine
      std::string uri = "opcua.treww.org";
      std::string name = "Open Source OPC-UA Server";
      std::string security_mode = "none"; //should be correct class
      
  };

}

#endif
