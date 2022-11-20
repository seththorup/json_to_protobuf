#include <fstream>
#include <iostream>

#include "JsonToProtobuf.h"
#include "linkbudget.pb.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;

using std::cout;
using std::endl;
using std::string;

int main() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  cout << "********** JsonToProtobuf Example *********" << endl;
  cout << "Start json file to protobuf converstion" << endl;

  // Json property tree object
  ptree json_file_ptree;

  // Two input values json file name and json child string
  // the child string maps to the protobuf
  // Todo pass in file and child string as argument
  string child_str{"data_links"};
  string json_config_file_name{"example_config.json"};

  if (read_json(json_config_file_name, json_file_ptree);
      json_file_ptree.empty()) {
    cout << "File not found" << endl;
    return 0;
  }

  auto data_link_list_ptree = json_file_ptree.get_child_optional(child_str);
  if (data_link_list_ptree.get_ptr() == nullptr) {
    cout << "Child not found" << endl;
    return 0;
  }

  // Pass ptree child as a ostream to write a json string
  // loop through the data_link_list_ptree for each entry
  LB::DataLinksList data_links_list_msg;
  LB::DataLinks *data_links_msg;
  for (auto ptree_pos = data_link_list_ptree->begin();
       ptree_pos != data_link_list_ptree->end(); ptree_pos++) {
    
    // data_links is an element in a DataLinkList
    data_links_msg = data_links_list_msg.add_data_links();

    std::ostringstream data_link_oss;
    write_json(data_link_oss, ptree_pos->second);
    auto data_link_string = data_link_oss.str();

    google::protobuf::util::JsonParseOptions options;
    JsonStringToMessage(data_link_string, data_links_msg, options);
  }
  cout << "Convert Protobuf msg to Json" << endl;
  data_links_msg = data_links_list_msg.add_data_links();
  data_links_msg->set_node_ids("4");

  data_links_msg->mutable_tx_ids()->set_link_ids("5");
  data_links_msg->mutable_tx_ids()->set_channel_ids("6");
  data_links_msg->mutable_tx_ids()->set_antenna_ids("7");

  data_links_msg->mutable_par()->set_tx_power_dbm(20);
  data_links_msg->mutable_par()->set_link_rate_bps(320000);
  data_links_msg->mutable_par()->set_frequency_hz(425000000);
  data_links_msg->mutable_radio_config()->set_power_backoff_db(3);
  data_links_msg->mutable_radio_config()->set_noise_figure_db(4.5);

  string data_link_json;
  Thorup::JsonToProtobuf proto_builder;
  proto_builder.convert_protobuf_to_json(data_links_list_msg, data_link_json,
                                         "output.json");

  cout << "start printing msg in list" << endl;
  for (auto link_msg : *data_links_list_msg.mutable_data_links()) {
    cout << link_msg.ShortDebugString() << endl;
  }

  cout << "json string converted from protobuf list" << endl;
  cout << data_link_json << endl;

  cout << "data_links_list_msg.size(): "
       << data_links_list_msg.data_links_size() << endl;
  cout << "********** end protobuf msg to Json test *********" << endl;

  return 0;
}