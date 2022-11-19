#include <iostream>
#include <fstream>

#include "JsonToProtobuf.h"
#include "linkbudget.pb.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;

using std::cout;
using std::endl;
using std::string;

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  cout << "********** JsonToProtobuf Example *********" << endl;
  cout << "Start json file to protobuf converstion" << endl;

  ptree root;
  string json_config_file_name {"example_config.json"};
  read_json(json_config_file_name, root);

  google::protobuf::util::JsonParseOptions options;

  // get data_link protobuf values from json
  auto data_link_ptree = root.get_child("DataLinks");
  //TODO: check if error

  std::ostringstream data_link_oss;
  write_json(data_link_oss, data_link_ptree);
  std::string data_link_string = data_link_oss.str();

  cout << "Contents of " << json_config_file_name << endl;
  cout << data_link_string << endl;

  LB::DataLinksList data_links_list_msg;
  LB::DataLinks *data_links_msg = data_links_list_msg.add_data_links_list();
  JsonStringToMessage(data_link_string, data_links_msg, options);

  cout << "data_links_msg after being read in from json file" << endl;
  cout << data_links_msg->ShortDebugString() << endl;

  cout << "Convert Protobuf msg to Json" << endl;
  auto data_links_msg2 = data_links_list_msg.add_data_links_list();
  data_links_msg2->set_node_ids("4");

  data_links_msg2->mutable_tx_ids()->set_link_ids("5");
  data_links_msg2->mutable_tx_ids()->set_channel_ids("6");
  data_links_msg2->mutable_tx_ids()->set_antenna_ids("7");

  data_links_msg2->mutable_par()->set_tx_power_dbm(20);
  data_links_msg2->mutable_par()->set_link_rate_bps(320000);
  data_links_msg2->mutable_par()->set_frequency_hz(425000000);
  data_links_msg2->mutable_radio_config()->set_power_backoff_db(3);
  data_links_msg2->mutable_radio_config()->set_noise_figure_db(4.5);

  cout << "New data_links_msg2 protobuf" << endl;
  cout << data_links_msg2->ShortDebugString() << endl;

  string data_link_json;
  Thorup::JsonToProtobuf proto_builder;
  proto_builder.convert_protobuf_to_json(data_links_list_msg, data_link_json, "output.json");

  cout << "start printing msg in list" << endl;
  for(auto link_msg : *data_links_list_msg.mutable_data_links_list()) {
    cout << link_msg.ShortDebugString() << endl;;
  }

  cout << "json string converted from protobuf list" << endl;
  cout << data_link_json << endl;
  
  cout << "data_links_list_msg.size(): " << data_links_list_msg.data_links_list_size() << endl;;
  cout << "********** end protobuf msg to Json test *********" << endl;

  return 0;
}