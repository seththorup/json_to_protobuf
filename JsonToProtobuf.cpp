#include <iostream>

#include "JsonToProtobuf.h"

#include <boost/json.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using google::protobuf::util::JsonParseOptions;
using std::cout;
using std::endl;
using std::string;

using namespace google::protobuf;
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;

namespace Thorup {

JsonToProtobuf::JsonToProtobuf() {
  m_options.add_whitespace = true;
  m_options.always_print_primitive_fields = true;
  m_options.preserve_proto_field_names = true;
}

bool JsonToProtobuf::convert_json_to_protobuf(const string &json_file_name,
                                              const string &object_name,
                                              Message &proto_msg) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  bool status{true};

  ptree root;
  read_json(json_file_name, root);

  JsonParseOptions options;

  // get data_link protobuf values from json
  auto data_link_ptree = root.get_child(object_name);

  std::ostringstream data_link_oss;
  write_json(data_link_oss, data_link_ptree);
  string json_string = data_link_oss.str();

  JsonStringToMessage(json_string, &proto_msg, options);

  return status;
}

bool JsonToProtobuf::convert_protobuf_to_json(const Message &proto_msg,
                                              string &json_string,
                                              string output_file_name = "") {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  bool status{true};

  // Create a json_string from sr.
  MessageToJsonString(proto_msg, &json_string, m_options);

  if (output_file_name != "") {
    std::ofstream json_file_handler;
    json_file_handler.open(output_file_name,
                           std::ofstream::out | std::ofstream::trunc);
    json_file_handler << json_string;
    cout << "writing file: " << output_file_name << endl;

    json_file_handler.close();
  }

  return status;
}


} // namespace Thorup