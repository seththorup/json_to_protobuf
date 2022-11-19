#include <iostream>
#include <fstream>


#include "JsonToProtobuf.h"
#include "linkbudget.pb.h"

#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree::json_parser;

using std::cout;
using std::endl;
using std::string;

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  LB::DataLinksList data_links_list_msg;

  cout << "********** Protobuf msg to Json test *********" << endl;
  LB::DataLinks *data_links_msg = data_links_list_msg.add_data_links_list();
  data_links_msg->set_node_ids("1,3-5,10");

  data_links_msg->mutable_tx_ids()->set_link_ids("1-2");
  data_links_msg->mutable_tx_ids()->set_channel_ids("1");
  data_links_msg->mutable_tx_ids()->set_antenna_ids("");

  data_links_msg->mutable_par()->set_tx_power_dbm(10);
  data_links_msg->mutable_par()->set_link_rate_bps(11500);
  data_links_msg->mutable_par()->set_frequency_hz(215000000);
  data_links_msg->mutable_radio_config()->set_power_backoff_db(3);

  cout << data_links_msg->ShortDebugString() << endl;

  string data_link_json;
  Thorup::JsonToProtobuf proto_builder;
  proto_builder.convert_protobuf_to_json(*data_links_msg, data_link_json, "test_lb.json");

  cout << "converted protobuf json string" << endl;
  cout << data_link_json << endl;
  

  cout << "********** end protobuf msg to Json test *********" << endl;

  return 0;
}

void message_to_json_test() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::string json_string;
  LB::DataLinksList data_links_list_msg;

  cout << "********** Message_to_json_test *********" << endl;

  LB::DataLinks *data_links_msg = data_links_list_msg.add_data_links_list();
  data_links_msg->set_node_ids("1,3-5,10");

  data_links_msg->mutable_tx_ids()->set_link_ids("1-2");
  data_links_msg->mutable_tx_ids()->set_channel_ids("1");
  data_links_msg->mutable_tx_ids()->set_antenna_ids("");

  data_links_msg->mutable_par()->set_tx_power_dbm(10);
  data_links_msg->mutable_par()->set_link_rate_bps(11500);
  data_links_msg->mutable_par()->set_frequency_hz(215000000);
  data_links_msg->mutable_radio_config()->set_power_backoff_db(3);

  cout << data_links_msg->ShortDebugString() << endl;

  // Create a json_string from sr.
  google::protobuf::util::JsonPrintOptions options;
  options.add_whitespace = true;
  options.always_print_primitive_fields = true;
  options.preserve_proto_field_names = true;
  MessageToJsonString(*data_links_msg, &json_string, options);

  // Print json_string.
  string json_file_name {"test_lb.json"}; 
  std::ofstream json_file_handler;
  json_file_handler.open(json_file_name, std::ofstream::out | std::ofstream::app);
  cout << "writing file: " << json_file_name << json_string << endl;
  json_file_handler.close();
  cout << endl;
}

// void json_to_message_test() {
//   GOOGLE_PROTOBUF_VERIFY_VERSION;
//   std::string json_string;
//   LB::DataLink data_link_msg;

//   cout << "********** json_to_message_test *********" << endl;

//   pt::ptree root;
//   pt::read_json("config.json", root);

//   google::protobuf::util::JsonParseOptions options2;

//   // get data_link protobuf values from json
//   auto data_link_ptree = root.get_child("DataLink");

//   std::ostringstream data_link_oss;
//   jp::write_json(data_link_oss, data_link_ptree);
//   std::string data_link_string = data_link_oss.str();
//   cout << data_link_string << endl;

//   JsonStringToMessage(data_link_string, &data_link_msg, options2);

//   auto temp_tx_power_dbm = data_link_msg.mutable_par()->tx_power_dbm();
//   data_link_msg.mutable_par()->set_tx_power_dbm(temp_tx_power_dbm + 3);
//   cout << data_link_msg.ShortDebugString() << endl;

//   cout << "node list: ";
//   uint32_t i = 0;
//   for (auto n : data_link_msg.node_ids()) {
//     if( data_link_msg.node_ids().size() > 0) {
//       if( data_link_msg.node_ids().at(i) == 0) {
//         cout << "0-" << data_link_msg.node_ids().at(n+1) << " ";
//       } else {
//         cout << n << " ";
//       }
//     }
//     i++;
//   }
//   cout << endl;
// }
