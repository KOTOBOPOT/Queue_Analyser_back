#include "creator_chouser.h"

namespace QueueBot {
IBotHandler::Ptr CreatorChouser::create(nlohmann::json value) {
  return _creators.at(value.at("class_tag"))->create(value);
}

void CreatorChouser::operator+=(
    std::pair<std::string, IHandlerCreator::Ptr>&& value) {
  _creators[value.first] = value.second;
}
}  // namespace QueueBot