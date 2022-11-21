#pragma once
#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/util/json_util.h>

namespace Thorup {

class JsonToProtobuf {
protected:
  google::protobuf::util::JsonOptions m_options;

public:
  JsonToProtobuf();

  bool convert_json_to_protobuf(const std::string &json_file_name,
                                const std::string &object_name,
                                google::protobuf::Message &proto_msg);
  bool convert_protobuf_to_json(const google::protobuf::Message &proto_msg,
                                std::string &json_string, std::string output_file_name);
};
} // namespace Thorup
